/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <memory>

#include <reg_exp.h>
#include <reg_exp_impl.h>


#include "dfautil_v6_3_0.h"


namespace v6_3_0 {

	using namespace std;
	
const std::string DFA_OUTPUT_DIR = "utf4cpp/dfa/";
	
void create_grapheme_break_dfa()	{
	cout << "create_grapheme_break_dfa() v6_3_0 \n";
	std::vector<std::string> tokens = {	
			"Other",
//			"Prepend"
			"CR", 
			"LF", 
			"Control", 
			"Extend", 
			"Regional_Indicator", 
			"SpacingMark", 
			"L", 
			"V", 
			"T", 
			"LV", 
			"LVT"
	};
	
/*
( CR LF )
| ( Prepend*
    ( L+ | (L* ( ( V | LV ) V* | LVT ) T*) | T+ | [^ Control CR LF ] )
    ( Extend | SpacingMark )*
   )
| .
*/

/*	std::string s = "(CR.LF)"		\
					"|(Prepend*."	\
					"(L+|(L*.((V|LV).(V*)|LVT).T*)|T+|(Other|SpacingMark|Prepend|Extend|LVT|LV|L|V|T))"  \
					".(Extend|SpacingMark)*" \
					")"
					"|(Other|SpacingMark|Prepend|Control|Extend|LVT|CR|LF|LV|L|V|T)"
	;
*/

/*
 * ( CRLF| Prepend*( RI-sequence  | Hangul-Syllable  | !Control )  ( Grapheme_Extend  | SpacingMark )* | . )

 * CRLF 	:= CR LF
 * RI-Sequence 	:= Regional_Indicator+
 * Hangul-Syllable 	:= L* V+ T*
	| L* LV V* T*
	| L* LVT T*
	| L+
	| T+
 * */

	string CRLF = "(CR.LF)";
	string RI_sequence = "(Regional_Indicator+)";
	string Hangul_syllable = "((L*.V+.T*)|(L*.LV.V*.T*)|(L*.LVT.T*|L+|T+))";
 	string any =			"(Other|CR|LF|Control|Extend|Regional_Indicator|SpacingMark|L|V|T|LV|LVT)";
 	string not_control_CR_LF	=	"(Other|Extend|Regional_Indicator|SpacingMark|L|V|T|LV|LVT)";
	
	stringstream ss;
	ss << "(" << CRLF << "|((" << RI_sequence << "|" << Hangul_syllable << "|" << not_control_CR_LF << ").(Extend|SpacingMark)*)|" << any << ")";
	
	RegExpWithTokens<char> reg_exp(tokens, 'a');
	//reg_exp.evaluate(exp.str());
	reg_exp.evaluate(ss.str());
	
	ofstream output(DFA_OUTPUT_DIR + "/grapheme_break_dfa.h");
	
	if (output.is_open())	{
		output << endl;

		output << "\n /*"<< endl;
		to_str<char>(output, reg_exp.dfa(), tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, reg_exp.dfa(), "grapheme_dfa");


		Nfa<char> nfa = nfa_reverse(to_nfa(reg_exp.dfa()));
//		std::cout << "test6 nfa2:\n" << nfa2 << std::endl;

		output << endl;
		Dfa<char> dfa2 = normalize(minimize(to_dfa(nfa)));

		output << "\n /*"<< endl;
		to_str<char>(output, dfa2, tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, dfa2, "grapheme_backwards_dfa");
	
	
	}
	
}
	
void create_word_break_dfa()	{
	using namespace std;
	
	cout << "create_word_break_dfa()\n";
		vector<string> tokens = {	
			"Other", 
			"Double_Quote", 
			"Single_Quote", 
			"Hebrew_Letter", 
			"CR", 
			"LF", 
			"Newline", 
			"Extend", 
			"Regional_Indicator", 
			"Format", 
			"Katakana", 
			"ALetter", 
			"MidLetter", 
			"MidNum", 
			"MidNumLet", 
			"Numeric", 
			"ExtendNumLet"
		};		

/*
WB1. 	sot 	÷ 	
WB2. 		÷ 	eot
 * 
Do not break within CRLF.
WB3. 	CR 	× 	LF

Otherwise break before and after Newlines (including CR and LF)
WB3a. 	(Newline | CR | LF) 	÷ 	 
WB3b. 	  	÷ 	(Newline | CR | LF)

Ignore Format and Extend characters, except when they appear at the beginning of a region of text.
(See Section 6.2, Replacing Ignore Rules.)
WB4. 	X (Extend | Format)* 	→ 	X

Do not break between most letters.
WB5. 	(ALetter | Hebrew_Letter) 	× 	(ALetter | Hebrew_Letter)

Do not break letters across certain punctuation.
WB6. 	(ALetter | Hebrew_Letter) 	× 	(MidLetter | MidNumLet | Single_Quote) (ALetter | Hebrew_Letter)
WB7. 	(ALetter | Hebrew_Letter) (MidLetter | MidNumLet | Single_Quote) 	× 	(ALetter | Hebrew_Letter)
WB7a. 	Hebrew_Letter 	× 	Single_Quote
WB7b. 	Hebrew_Letter 	× 	Double_Quote Hebrew_Letter
WB7c. 	Hebrew_Letter Double_Quote 	× 	Hebrew_Letter

Do not break within sequences of digits, or digits adjacent to letters (“3a”, or “A3”).
WB8. 	Numeric 	× 	Numeric
WB9. 	(ALetter | Hebrew_Letter) 	× 	Numeric
WB10. 	Numeric 	× 	(ALetter | Hebrew_Letter)

Do not break within sequences, such as “3.2” or “3,456.789”.
WB11. 	Numeric (MidNum | MidNumLet | Single_Quote) 	× 	Numeric
WB12. 	Numeric 	× 	(MidNum | MidNumLet | Single_Quote) Numeric

Do not break between Katakana.
WB13. 	Katakana 	× 	Katakana

Do not break from extenders.
WB13a. 	(ALetter | Hebrew_Letter | Numeric | Katakana | ExtendNumLet) 	× 	ExtendNumLet
WB13b. 	ExtendNumLet 	× 	(ALetter | Hebrew_Letter | Numeric | Katakana)

Do not break between regional indicator symbols.
WB13c. 	Regional_Indicator 	× 	Regional_Indicator

Otherwise, break everywhere (including around ideographs).
WB14. 	Any 	÷ 	Any
 * */

// begin regular exp

	string CRLF = "(CR.LF)";

	string Other_EF 		= "(Other.(Extend|Format)*)"; 
	string ALetter_EF 		= "(ALetter.(Extend|Format)*)"; 
	string Numeric_EF 		= "(Numeric.(Extend|Format)*)";
	string Katakana_EF  	= "(Katakana.(Extend|Format)*)";
	string ExtendNumLet_EF	= "(ExtendNumLet.(Extend|Format)*)";
	string MidLetter_EF		= "(MidLetter.(Extend|Format)*)";
	string MidNumLet_EF		= "(MidNumLet.(Extend|Format)*)";
	string MidNum_EF 		= "(MidNum.(Extend|Format)*)";

	string Hebrew_Letter_EF	= "(Hebrew_Letter.(Extend|Format)*)";
	string Single_Quote_EF	= "(Single_Quote.(Extend|Format)*)";
	string Double_Quote_EF	= "(Double_Quote.(Extend|Format)*)";
	
	string Regional_Indicator_EF = "(Regional_Indicator.(Extend|Format)*)";

	string Format_EF	= "(Format.(Extend|Format)*)";
	string Extend_EF	= "(Extend.(Extend|Format)*)";

	string any = "(" + Other_EF + "|" + ALetter_EF + "|" + Numeric_EF + "|" + Katakana_EF 
		+ "|" + ExtendNumLet_EF + "|" + MidLetter_EF + "|" + MidNumLet_EF + "|" + MidNum_EF 
		+ "|" + Hebrew_Letter_EF + "|" + Single_Quote_EF + "|" + Double_Quote_EF 
		+ "|" + Regional_Indicator_EF
		+ "|" + Format_EF + "|" + Extend_EF
		+ "|CR|LF|Newline"   
		+ ")";



//Hebrew_Letter 	× 	Single_Quote
//	WB7b. 	Hebrew_Letter 	× 	Double_Quote Hebrew_Letter
//	WB7c. 	Hebrew_Letter Double_Quote 	× 	Hebrew_Letter


	string Hebrew_Letter_seq = "((" + Hebrew_Letter_EF + "|" + Hebrew_Letter_EF + "." + Double_Quote_EF + "." + Hebrew_Letter_EF + ")+)";

	//WB7a. 	Hebrew_Letter 	× 	Single_Quote
	string Hebrew_Letter_Single_Quote = "((" + Hebrew_Letter_EF + "." + Single_Quote_EF + ")*)";

	string Letter	= "((ALetter|" + Hebrew_Letter_seq + ").(Extend|Format)*)"; 	
	
	string MidLetter_MidNumLet_Single_Quote_EF = "((MidLetter|MidNumLet|Single_Quote).(Extend|Format)*)";
//	string MidNum_MidNumLet_EF = "((MidNum|MidNumLet).(Extend|Format)*)";
	
	string MidNum_MidNumLet_Single_Quote_EF = "((MidNum|MidNumLet|Single_Quote).(Extend|Format)*)";
	
	//WB5 WB6
	string Letter_punct = "(" + Letter + "." + MidLetter_MidNumLet_Single_Quote_EF + "." + Letter + ")";

	string Numeric_seq = "((" + Numeric_EF +	"|(" + Numeric_EF + "." + MidNum_MidNumLet_Single_Quote_EF + "." + Numeric_EF + "))+)"; 
	string ExtendNumLet_Numeric_seq = "(" + ExtendNumLet_EF + "." + Numeric_seq + ")";

	
	string Letter_Numeric = "((" + Letter  + "|" + Letter + "." + Numeric_seq + "|" + Numeric_seq + ")+)";

	string Letter_seq = "((" + Letter +  "|" + Letter_Numeric + "|" + Letter_punct + ")+)";
	

	string Letter_seq2 = "((" + Letter_seq + "|" + Letter_seq + "." + ExtendNumLet_EF + ")+)";

	string ExtendNumLet_Letter_seq = "(" + ExtendNumLet_EF + "+." + Letter_seq2 + ")";
	
	string RI_sequence = "(" + Regional_Indicator_EF + "+)";
	
	
	
//	string katakana_seq = "(" + Katakana_EF + "+)";
	string katakana_seq = "((" + Katakana_EF + "|" + Katakana_EF + "." + ExtendNumLet_EF + ")+)";
	string ExtendNumLet_katakana_seq = "(" + ExtendNumLet_EF + "+." + katakana_seq + ")";
	
	string ExtendNumLet_seq = "(" + ExtendNumLet_EF + "+)";
// end regular exp

		
		RegExpWithTokens<char> reg_exp(tokens, 'a');
		//reg_exp.evaluate(exp.str());
	stringstream ss;
	ss	
		<< "(" 
		<< CRLF 
		<< "|" << RI_sequence 
		<< "|" << any 
		<< "|" << Letter_seq2
		<< "|" << ExtendNumLet_Letter_seq
		<< "|" << Numeric_seq
		<< "|" << Hebrew_Letter_Single_Quote
		<< "|" << ExtendNumLet_Numeric_seq
		<< "|" << katakana_seq
		<< "|" << ExtendNumLet_katakana_seq
		<< "|" << ExtendNumLet_seq
		
		//<< "|" << Hebrew_Letter_seq
		//<< "|" << Hebrew_Letter_Single_Quote
		//<< "|" << "((ALetter|(Hebrew_Letter_seq)).(Extend|Format)*)"
		
		<< ")";

		reg_exp.evaluate(ss.str());
	
	ofstream output(DFA_OUTPUT_DIR + "/word_break_dfa.h");
	
	if (output.is_open())	{
		output << endl;

		output << "\n /*"<< endl;
		to_str<char>(output, reg_exp.dfa(), tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, reg_exp.dfa(), "word_dfa");


		Nfa<char> nfa = nfa_reverse(to_nfa(reg_exp.dfa()));
//		std::cout << "test6 nfa2:\n" << nfa2 << std::endl;

		output << endl;
		Dfa<char> dfa2 = normalize(minimize(to_dfa(nfa)));

		output << "\n /*"<< endl;
		to_str<char>(output, dfa2, tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, dfa2, "word_backwards_dfa");
	
	
	}
	
	
}


void create_sentence_break_dfa()	{
	cout << "create_sentence_break_dfa()\n";

		std::vector<std::string> tokens = {	
				"Other", 
				"CR", 
				"LF", 
				"Extend", 
				"Sep", 
				"Format", 
				"Sp", 
				"Lower", 
				"Upper", 
				"OLetter", 
				"Numeric", 
				"ATerm", 
				"STerm", 
				"Close", 
				"SContinue"
		};		


/*
SB1. 	sot 	÷ 	
SB2. 		÷ 	eot
SB3. 	CR 	× 	LF
SB4. 	Sep | CR | LF 	÷ 	 
SB5. 	X (Extend | Format)* 	→ 	X
SB6. 	ATerm 	× 	Numeric
SB7. 	Upper ATerm 	× 	Upper
SB8. 	ATerm Close* Sp* 	× 	( ¬(OLetter | Upper | Lower | Sep | CR | LF | STerm | ATerm) )* Lower
SB8a. 	( STerm | ATerm ) Close* Sp*	× 	(SContinue | STerm | ATerm)
SB9. 	( STerm | ATerm ) Close*		× 	( Close | Sp | Sep | CR | LF )
SB10. 	( STerm | ATerm ) Close* Sp*	× 	( Sp | Sep | CR | LF )
SB11. 	( STerm | ATerm ) Close* Sp* ( Sep | CR | LF )? 	÷ 	 
SB12. 	Any 	× 	Any
*/

// begin regular exp v2
	std::string Any = "((Other|CR|LF|Extend|Sep|Format|Sp|Lower|Upper|OLetter|Numeric|ATerm|STerm|Close|SContinue).(Extend|Format)*)";

	std::string Any_Not_Sep_CR_LF = "((Other|Extend|Format|Sp|Lower|Upper|OLetter|Numeric|Close|SContinue).(Extend|Format)*)";
	std::string Any_Not_ATerm_STerm = "((Other|CR|LF|Extend|Sep|Format|Sp|Lower|Upper|OLetter|Numeric|Close|SContinue).(Extend|Format)*)";

	std::string Any_Not_Sep_CR_LF_EF = "((Other|Extend|Format|Sp|Lower|Upper|OLetter|Numeric|ATerm|STerm|Close|SContinue).(Extend|Format)*)";

	std::string Extend_Format = "((Extend|Format)*)";
	std::string Other_EF	= "(Other.(Extend|Format)*)";
	std::string Sp_EF		= "(Sp.(Extend|Format)*)";
	std::string Lower_EF	= "(Lower.(Extend|Format)*)";
	std::string Upper_EF	= "(Upper.(Extend|Format)*)";
	std::string OLetter_EF	= "(OLetter.(Extend|Format)*)";
	std::string Numeric_EF	= "(Numeric.(Extend|Format)*)";
	std::string ATerm_EF	= "(ATerm.(Extend|Format)*)";
	std::string STerm_EF	= "(STerm.(Extend|Format)*)";
	std::string Close_EF	= "(Close.(Extend|Format)*)";
	std::string SContinue_EF = "(SContinue.(Extend|Format)*)";
	std::string Not_OLetter__ATerm = "((Other|Extend|Format|Sp|Numeric|Close|SContinue).(Extend|Format)*)";

	
	std::string STerm_ATerm_EF = "((STerm|ATerm).(Extend|Format)*)"; 
	std::string SContinue_STerm_ATerm_EF = "((SContinue|STerm|ATerm).(Extend|Format)*)"; 
	
	std::string ATerm_Numeric_EF   = "(ATerm.(Extend|Format)*.Numeric.(Extend|Format)*)";
	std::string Upper_ATerm_Upper =  "((Upper.(Extend|Format)*.ATerm.(Extend|Format)*)+.Upper.(Extend|Format)*)";
	
	std::string Close_SP_EF = "(" + Close_EF + "*." + Sp_EF + "*)";
	
	std::string sb8   = "(" + ATerm_EF       + "." + Close_SP_EF + "." + Not_OLetter__ATerm + "*." + Lower_EF + ")";
	std::string sb8_a = "(" + STerm_ATerm_EF + "." + Close_SP_EF + ".(SContinue|STerm|ATerm)." + Extend_Format + ")";
	
	// remove Close Sp from sb9...
	std::string sb9 =  "(" + STerm_ATerm_EF + "." + Close_EF + "*.(Close|Sp|Sep|CR|LF)." + Extend_Format + ")";
	
	std::string sb11_a = "(" + STerm_ATerm_EF + "." + Close_SP_EF + ")"; //
	std::string sb11_b = "(" + sb11_a + ".(Sep|CR|LF))"; //
	
	std::string todo = "((" + Any_Not_Sep_CR_LF + "|" + ATerm_Numeric_EF + "|" + Upper_ATerm_Upper + "|" + sb8 + "|" + sb8_a /*+ "|" + sb9*/ + ")*)";
	
	std::stringstream ss;

	ss << "(";
	ss << todo ;
	ss << "|(" << todo << "." << sb11_a + ")";
	ss << "|(" << todo << "." << sb11_b + ")";
	ss << "|(" << todo << ".(Sep|CR|LF))";
	ss << "|(CR.LF)";
	ss << ")";


// end regular exp

		
		RegExpWithTokens<char> reg_exp(tokens, 'a');
		//reg_exp.evaluate(exp.str());
		reg_exp.evaluate(ss.str());


	ofstream output(DFA_OUTPUT_DIR + "/sentence_break_dfa.h");
	
	if (output.is_open())	{
		output << endl;

		output << "\n /*"<< endl;
		to_str<char>(output, reg_exp.dfa(), tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, reg_exp.dfa(), "sentence_dfa");


		Nfa<char> nfa = nfa_reverse(to_nfa(reg_exp.dfa()));
//		std::cout << "test6 nfa2:\n" << nfa2 << std::endl;

		output << endl;
//		Dfa<char> dfa2 = normalize(minimize(to_dfa(nfa)));
		Dfa<char> dfa2 = to_dfa(nfa);

		output << "\n /*"<< endl;
		to_str<char>(output, dfa2, tokens, 'a');
		output << "*/\n"<< endl;

		to_cpp(output, dfa2, "sentence_backwards_dfa");
	
	
	}

	
}

} // namespace v6_3_0

