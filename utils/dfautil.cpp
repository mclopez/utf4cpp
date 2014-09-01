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

#include "dfautil.h"



namespace v6_0_0 {

/*
	std::string s = "(CR.LF)"		\
					"|(Prepend*."	\
					"(L+|(L*.((V|LV).(V*)|LVT).T*)|T+|(Other|SpacingMark|Prepend|Extend|LVT|LV|L|V|T))"  \
					".(Extend|SpacingMark)*" \
					")"
					"|(Other|SpacingMark|Prepend|Control|Extend|LVT|CR|LF|LV|L|V|T)"
	;
*/	
	
using namespace ::std;	

const std::string DFA_OUTPUT_DIR = "../unicpp/dfa/";


void create_word_break_dfa()	{
	std::cout << "create_word_break_dfa()\n";
		std::vector<std::string> tokens = {	
			"Other", 
			"CR", 
			"LF", 
			"Newline", 
			"Extend", 
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

Do not break within CRLF.
WB3. 	CR 	× 	LF

Otherwise break before and after Newlines (including CR and LF)
WB3a. 	(Newline | CR | LF) 	÷ 	 
WB3b. 	  	÷ 	(Newline | CR | LF)

Ignore Format and Extend characters, except when they appear at the beginning of a region of text.
(See Section 6.2, Replacing Ignore Rules.)
WB4. 	X (Extend | Format)* 	→ 	X

Do not break between most letters.
WB5. 	ALetter 	× 	ALetter

Do not break letters across certain punctuation.
WB6. 	ALetter 	× 	(MidLetter | MidNumLet) ALetter
WB7. 	ALetter (MidLetter | MidNumLet) 	× 	ALetter

Do not break within sequences of digits, or digits adjacent to letters (“3a”, or “A3”).
WB8. 	Numeric 	× 	Numeric
WB9. 	ALetter 	× 	Numeric
WB10. 	Numeric 	× 	ALetter

Do not break within sequences, such as “3.2” or “3,456.789”.
WB11. 	Numeric (MidNum | MidNumLet) 	× 	Numeric
WB12. 	Numeric 	× 	(MidNum | MidNumLet) Numeric

Do not break between Katakana.
WB13. 	Katakana 	× 	Katakana

Do not break from extenders.
WB13a. 	(ALetter | Numeric | Katakana | ExtendNumLet) 	× 	ExtendNumLet
WB13b. 	ExtendNumLet 	× 	(ALetter | Numeric | Katakana)

Otherwise, break everywhere (including around ideographs).
WB14. 	Any 	÷ 	Any
*/

// begin regular exp

	std::string Other_EF 		= "(Other.(Extend|Format)*)"; 
	std::string ALetter_EF 		= "(ALetter.(Extend|Format)*)"; 
	std::string Numeric_EF 		= "(Numeric.(Extend|Format)*)";
	std::string Katakana_EF  	= "(Katakana.(Extend|Format)*)";
	std::string ExtendNumLet_EF = "(ExtendNumLet.(Extend|Format)*)";
	std::string MidLetter_EF	= "(MidLetter.(Extend|Format)*)";
	std::string MidNumLet_EF	= "(MidNumLet.(Extend|Format)*)";
	std::string MidNum_EF 		= "(MidNum.(Extend|Format)*)";
	std::string MidLetter_MidNumLet_EF = "((MidLetter|MidNumLet).(Extend|Format)*)";
	std::string MidNum_MidNumLet_EF = "((MidNum|MidNumLet).(Extend|Format)*)";
	
//	std::string ALetter			= 	"(" + ALetter_EF + "+|(" + ALetter_EF + "+." + MidLetter_MidNumLet_EF + "." + ALetter_EF + "+))";
	std::string ALetter			= 	"((" + ALetter_EF + "|(" + ALetter_EF + "." + MidLetter_MidNumLet_EF + "." + ALetter_EF + "))+)";
	std::string Numeric			= 	"((" + Numeric_EF + "|(" + Numeric_EF + "+." + MidNum_MidNumLet_EF    + "." + Numeric_EF + "+))+)";
//	std::string Numeric			= 	"(" + Numeric_EF + "+|(" + Numeric_EF + "+." + MidNum_MidNumLet_EF + "." + Numeric_EF + "+))";

	std::string ALetter_Numeric =   	"((" + ALetter + "|" + Numeric + ")+)";

	//std::string Katakana = 			"((" + Katakana_EF + "+|" + ExtendNumLet_EF + "*)*)";
	//std::string Katakana = 				"(" + Katakana_EF + "+)";
	std::string Katakana_ExtendNumLet = "((" + Katakana_EF + "+|" + Katakana_EF + "+." + ExtendNumLet_EF + "+|" + ExtendNumLet_EF + "+." + Katakana_EF + "+)+)";
	std::string ALetter_Numeric_ExtendNumLet = "((" + ALetter_Numeric + "+|" + ALetter_Numeric + "+." + ExtendNumLet_EF + "+|" + ExtendNumLet_EF + "+." + ALetter_Numeric + "+)+)";

	std::string ExtendNumLet = "(" + ExtendNumLet_EF + "+)";

	std::string ALetter_Numeric_Katakana_1 =   "(" + ALetter_Numeric + "+." + ExtendNumLet_EF + "+." + Katakana_ExtendNumLet + "+)";
	std::string ALetter_Numeric_Katakana_2 =   "(" + Katakana_ExtendNumLet + "+." + ExtendNumLet_EF + "+." + ALetter_Numeric + "+)";

	std::stringstream ss;
//	ss << "("+ Other_EF + "|CR|LF|Newline|Extend|Format|Katakana|ALetter|" + MidLetter_EF + "|MidNum|" + MidNumLet_EF + "|Numeric|ExtendNumLet)";
	ss << "((Other|Extend|Format|Katakana|ALetter|MidLetter|MidNum|MidNumLet|Numeric|ExtendNumLet).(Extend|Format)*)";
	ss << "|(CR|LF|Newline)";
	ss << "|(CR.LF)";
	ss << "|((Extend|Format)*)";
	ss << "|" << ALetter_Numeric;
	ss << "|" << ALetter_Numeric_ExtendNumLet ;
	ss << "|" << Katakana_ExtendNumLet;
	ss << "|" << ALetter_Numeric_Katakana_1;
	ss << "|" << ALetter_Numeric_Katakana_2;
	ss << "|" << ExtendNumLet;
	ss << "|" << ALetter;
	
// end regular exp

		
		RegExpWithTokens<char> reg_exp(tokens, 'a');
		//reg_exp.evaluate(exp.str());
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

} // namespace v6_0_0 
