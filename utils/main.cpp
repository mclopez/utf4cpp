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



#include "cdb/util.h"
#include "cdb/info_parser.h"
#include "cdb/binary_generator.h"
#include "cdb/table_generator.h"

#include "dfautil.h"
#include "dfautil_v6_3_0.h"

//#include "reg_exp_test.h"
#include <reg_exp.h>
#include <reg_exp_impl.h>


using namespace std;

const std::string CDB_OUTPUT_DIR = "utf4cpp/cdb/";

const std::string CDB_INPUT_DIR  = "unicode/Segmentation/props/6.3.0/";


void create_grapheme_break_files(){
	using namespace std;
	cout << "Character Database Tool create_grapheme_break_files\n";
	GraphemeBreakInfoParser parser(CDB_INPUT_DIR + "/GraphemeBreakProperty.txt");
	parser.parse();
//	GraphemeBreakCommonGenerator cg(parser);
//	cg.generate_common();
	GraphemeBreakBinaryGenerator bg(parser);
	bg.generate_binary(CDB_OUTPUT_DIR + "/grapheme_break_binary_auto", "unicpp/cdb/graphemebreak/binary");

	GraphemeBreakTableGenerator tg(parser);
	tg.generate_table_2n(8, 13, 
		CDB_OUTPUT_DIR + "/grapheme_break_table_2levels_auto", 
		"unicpp/cdb/graphemebreak/table_2levels");
	tg.generate_table_3n(7, 7,  
		CDB_OUTPUT_DIR + "/grapheme_break_table_3levels_auto", 
		"unicpp/cdb/graphemebreak/table_3levels");

//	test_table();

	return ;
}


void create_word_break_files(){
	using namespace std;
	cout << "Character Database Tool\n";
	GraphemeBreakInfoParser parser(CDB_INPUT_DIR + "/WordBreakProperty.txt");
	parser.parse();
//	GraphemeBreakCommonGenerator cg(parser);
//	cg.generate_common();
	GraphemeBreakBinaryGenerator bg(parser);
	bg.generate_binary(CDB_OUTPUT_DIR + "/word_break_binary_auto", "unicpp/cdb/wordbreak/binary");
	
	GraphemeBreakTableGenerator tg(parser);
	tg.generate_table_2n(8, 13, 
		CDB_OUTPUT_DIR + "/word_break_table_2levels_auto", 
		"unicpp/cdb/wordbreak/table_2levels");
	tg.generate_table_3n(7, 7,  
		CDB_OUTPUT_DIR + "/word_break_table_3levels_auto", 
		"unicpp/cdb/wordbreak/table_3levels");
		 
//	test_table();

	return ;
}


void create_sentence_break_files(){
	using namespace std;
	cout << "Character Database Tool\n";
	GraphemeBreakInfoParser parser(CDB_INPUT_DIR + "SentenceBreakProperty.txt");
	parser.parse();
//	GraphemeBreakCommonGenerator cg(parser);
//	cg.generate_common();
	GraphemeBreakBinaryGenerator bg(parser);
	bg.generate_binary(CDB_OUTPUT_DIR + "/sentence_break_binary_auto", "unicpp/cdb/sentencebreak/binary");
	
	GraphemeBreakTableGenerator tg(parser);
	tg.generate_table_2n(8, 13, 
		CDB_OUTPUT_DIR + "/sentence_break_table_2levels_auto", 
		"unicpp/cdb/sentencebreak/table_2levels");
	tg.generate_table_3n(7, 7,  
		CDB_OUTPUT_DIR + "/sentence_break_table_3levels_auto", 
		"unicpp/cdb/sentencebreak/table_3levels");

//	test_table();

	return ;
}

enum etable {OP, CL, CP, QU, GL, NS, EX, SY, IS, PR, PO, NU, AL, HL, ID, IN, HY, BA, BB, B2, ZW, CM, WJ, H2, H3, JL, JV, JT};
/*
bool operator(PropertyValue v1, etable v2)	{
	return false;
}
*/
#define TEST(VAL) if (v==std::string(#VAL)){ return VAL;} 

int str_to_etable(const std::string& v)	{
	TEST(OP);
	TEST(CL); 
	TEST(CP);
	TEST(QU);
	TEST(GL); 
	TEST(NS);
	TEST(EX); 
	TEST(SY); 
	TEST(IS); 
	TEST(PR); 
	TEST(PO); 
	TEST(NU); 
	TEST(AL); 
	TEST(HL); 
	TEST(ID); 
	TEST(IN); 
	TEST(HY); 
	TEST(BA); 
	TEST(BB); 
	TEST(B2); 
	TEST(ZW); 
	TEST(CM); 
	TEST(WJ); 
	TEST(H2); 
	TEST(H3); 
	TEST(JL); 
	TEST(JV); 
	TEST(JT);
	return -1;
}

char table[][28] ={ 	
//	 	OP 	CL 	CP 	QU 	GL 	NS 	EX 	SY 	IS 	PR 	PO 	NU 	AL 	HL 	ID 	IN 	HY 	BA 	BB 	B2 	ZW 	CM 	WJ 	H2 	H3 	JL 	JV 	JT
/*OP*/ 	{'^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '^', '@', '^', '^', '^', '^', '^', '^'},
/*CL*/ 	{'_', '^', '^', '%', '%', '^', '^', '^', '^', '%', '%', '_', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*CP*/ 	{'_', '^', '^', '%', '%', '^', '^', '^', '^', '%', '%', '%', '%', '%', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*QU*/ 	{'^', '^', '^', '%', '%', '%', '^', '^', '^', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '^', '#', '^', '%', '%', '%', '%', '%'},
/*GL*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '^', '#', '^', '%', '%', '%', '%', '%'},
/*NS*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '_', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*EX*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '_', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*SY*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*IS*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*PR*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '%', '_', '%', '%', '_', '_', '^', '#', '^', '%', '%', '%', '%', '%'},
/*PO*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*NU*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '%', '%', '%', '%', '%', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*AL*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*HL*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*ID*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*IN*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*HY*/ 	{'_', '^', '^', '%', '_', '%', '^', '^', '^', '_', '_', '%', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*BA*/ 	{'_', '^', '^', '%', '_', '%', '^', '^', '^', '_', '_', '_', '_', '_', '_', '_', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*BB*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '^', '#', '^', '%', '%', '%', '%', '%'},
/*B2*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '_', '_', '_', '_', '_', '%', '%', '_', '^', '^', '#', '^', '_', '_', '_', '_', '_'},
/*ZW*/ 	{'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '^', '_', '_', '_', '_', '_', '_', '_'},
/*CM*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '_', '_', '%', '%', '%', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '_'},
/*WJ*/ 	{'%', '^', '^', '%', '%', '%', '^', '^', '^', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '%', '^', '#', '^', '%', '%', '%', '%', '%'},
/*H2*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '%', '%'},
/*H3*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '%'},
/*JL*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '%', '%', '%', '%', '_'},
/*JV*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '%', '%'},
/*JT*/ 	{'_', '^', '^', '%', '%', '%', '^', '^', '^', '_', '%', '_', '_', '_', '_', '%', '%', '%', '_', '_', '^', '#', '^', '_', '_', '_', '_', '%'}

};


void create_line_break_files(){
	using namespace std;
	cout << "Character Database Tool\n";
	GraphemeBreakInfoParser parser(CDB_INPUT_DIR + "/LineBreak.txt");
	parser.parse();
	GraphemeBreakBinaryGenerator bg(parser);
	bg.generate_binary(CDB_OUTPUT_DIR + "/line_break_binary_auto", "unicpp/cdb/linebreak/binary");

	//9-12 ->? kb
	//8-13 ->33792 kb
	//7-14 ->31616 kb
	//6-15 ->35456 kb
	GraphemeBreakTableGenerator tg(parser);
	tg.generate_table_2n(7, 14, 
		CDB_OUTPUT_DIR + "/line_break_table_2levels_auto", 
		"unicpp/cdb/linebreak/table_2levels");


	ofstream output(CDB_OUTPUT_DIR + "/line_break_table_data.h");
	if (output.is_open())	{
//		output << "#define  \n";
		output << "namespace unicpp { namespace cdb { namespace linebreak { \n\n";
		output << "enum oportunity_break {Prohibited, Indirect, ProhibitedCM, IndirectCM, Direct, Undefined};\n\n" << std::endl;
		std::vector<std::string> values = parser.enum_values();
		output << "oportunity_break pair_table[][" << values.size() << "] = {" << std::endl;
		for(size_t i=0;i<values.size();++i)	{
			output << "{";
			for(size_t j=0;j<values.size();++j)	{
				int v1 = str_to_etable(values[i]);
				int v2 = str_to_etable(values[j]);
				char c = '!';
				if (v1>=0 && v2>=0)	{
					c = table[v1][v2];
				}
				//std::cout << v1 << ", " << v2 << std::endl;
				switch(c)	{
					case '^': 
						output << "Prohibited, ";
						break;
					case '%':	
						output << "Indirect, ";
						break;
					case '@':	
						output << "ProhibitedCM, ";
						break;
					case '#':	
						output << "IndirectCM, ";
						break;
					case '_':	
						output << "Direct, ";
						break;						
					default:
						output << "Undefined, ";
				}
			}
			output << "}," << std::endl;
		}
		output << "};" << std::endl;
		output << " } } }//namespace " << std::endl;
		
	}

/*	tg.generate_table_3n(7, 7,  
		"../../GraphemeBreak1/line_break_table_3levels_auto", 
		"unicpp/cdb/linebreak/table_3levels");
*/

	return ;
}



int invalid(char* program)	{
	cout << "Invalid option\n "
		<< "usage: " << program << " [OPTION]\n " 
		<< "-gb creates files for grapheme break character database\n "
		<< "-wb creates files for word break character database\n "
		<< "-sb creates files for sentence break character database\n "
		<< "-lb creates files for line break character database\n "
		<< "-gdfa creates files for grapheme break dfa\n "
		<< "-wdfa creates files for word break dfa\n "
		<< "-sdfa creates files for sentence break dfa\n "
		<< endl;
		return -1;	
}	

int main(int argc, char **argv)
{
//	create_grapheme_break_files();
//	create_word_break_files();
//	create_sentence_break_files();
//	create_line_break_files();

//v6_3_0::create_grapheme_break_dfa();			
//v6_3_0::create_word_break_dfa();			

//return 0;

//	using namespace v6_0_0;
	using namespace v6_3_0;
	
	if (argc == 2)	{
		cout << "option '" << argv[1] << "'" << endl;
		std::string option(argv[1]);
		if (option == "-gb")	{
			create_grapheme_break_files();
		}else if (option == "-wb")	{
			create_word_break_files();			
		}else if (option == "-sb")	{
			create_sentence_break_files();			
		}else if (option == "-lb")	{
			create_line_break_files();			
		}else if (option == "-gdfa")	{
			create_grapheme_break_dfa();			
		}else if (option == "-wdfa")	{
			create_word_break_dfa();			
		}else if (option == "-sdfa")	{
			create_sentence_break_dfa();
		}else if (option == "-all"){
			create_grapheme_break_files();
			create_word_break_files();			
			create_sentence_break_files();			
			create_line_break_files();			
			// dfas
			return 0;
			create_grapheme_break_dfa();			
			create_word_break_dfa();			
			create_sentence_break_dfa();			
		}else {
			return invalid(argv[0]);
		}
	}else {
		return invalid(argv[0]);
	}
	
}
