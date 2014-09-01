/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "common_generator.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;
/*
GraphemeBreakCommonGenerator::GraphemeBreakCommonGenerator(GraphemeBreakInfoParser& graphemeBreakInfoParser)
:graphemeBreakInfoParser(graphemeBreakInfoParser)
{
}

GraphemeBreakCommonGenerator::~GraphemeBreakCommonGenerator()
{
}

void GraphemeBreakCommonGenerator::generate_common()	{
	ofstream output("../../GraphemeBreak1/GraphemeCommon_Auto.h");
	if (output.is_open())	{
		output << "#ifndef GRAPHEME_COMMON_AUTO_H" << endl;
		output << "#define GRAPHEME_COMMON_AUTO_H" << endl;
		
		output << "#include <string>" << endl;
		output << endl;
		output << "namespace Common { " << endl;

		if (graphemeBreakInfoParser.values.size()<2^8)	{
			output << "enum class PropertyValue : unsigned char {" << endl; 
		} else if(graphemeBreakInfoParser.values.size()<2^16){
			output << "enum class PropertyValue : unsigned short {" << endl; 
		}
		output << "\tOther, " << endl;
//		output << "enum PropertyValue {";
		for(auto it=graphemeBreakInfoParser.values.begin();
				it!=graphemeBreakInfoParser.values.end();++it)	{
			if (it!=graphemeBreakInfoParser.values.begin())	{
				output << ", " << endl;
			}
			output << '\t' << **it;
		}	
		output << endl << "};" << endl;
		output << endl;		
		
		output << "inline" << endl;
		output << "std::string to_string(PropertyValue v)	{" << endl;
		output << " switch(v)	{" << endl;
		for(auto it=graphemeBreakInfoParser.values.begin();
			it!=graphemeBreakInfoParser.values.end();++it)	{
			output << "		case PropertyValue::" << **it << ": return \"" << **it << "\"; " << endl;
		}		
		output << "		default:" << endl;
		output << "			return \"default\";" << endl;
		output << "	}" << endl;
		output << "}" << endl;
		output << endl;
	
		
		output << "} // namespace Common" << endl;
		output << "#endif // GRAPHEME_COMMON_AUTO_H" << endl;

		output.close();
		
		output.open("../../GraphemeBreak1/GraphemeCommon_Auto.cpp");
		output << "#include \"GraphemeCommon_Auto.h\"" << endl;
		
	}	
}

*/
