/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "binary_generator.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

GraphemeBreakBinaryGenerator::GraphemeBreakBinaryGenerator(
		GraphemeBreakInfoParser& graphemeBreakInfoParser)
		:graphemeBreakInfoParser(graphemeBreakInfoParser)
{
}

GraphemeBreakBinaryGenerator::~GraphemeBreakBinaryGenerator()
{
}



void GraphemeBreakBinaryGenerator::generate_binary(
	const std::string& filename, 
	const std::string& _namespace)
{
	cout << "Generating -> " << filename << endl;
	//ofstream output("../../GraphemeBreak1/GraphemeBinary_Auto.h");
	ofstream output(filename + ".h");
	if (output.is_open())	{
		output << "#ifndef " << get_guard(_namespace) << "_H" << endl;
		output << "#define " << get_guard(_namespace) << "_H" << endl;
		
		output << "#include <string>" << endl;
		output << "#include <ostream>" << endl;
		output << endl;
		output << get_namespace_begin(_namespace) << endl;
		output << endl;

		GraphemeBreakCommonGenerator common(graphemeBreakInfoParser);
		common.generate_common(output);

		output << "struct RangePropertyValue	{" << endl;
		output << "\tchar32_t begin;" << endl;
		output << "\tchar32_t end;" << endl;
		output << "\tPropertyValue value;" << endl;
		output << "};" << endl;
		output << endl;
	
		output << "inline" << endl;
		output << "bool operator<(const RangePropertyValue& p1, const RangePropertyValue& p2)	{" << endl;
//		output << "		return p1.begin < p2.begin;" << endl;
		output << "		return p1.end < p2.end;" << endl;
		output << "}" << endl;
		output << endl;
/*
		output << "inline" << endl;
		output << "bool operator==(const RangePropertyValue& p1, const RangePropertyValue& p2)	{" << endl;
		output << "		return p1.begin <= p2.begin && p1.end >= p2.begin && p1.end >= p2.end;" << endl;
		output << "}" << endl;
		output << endl;
*/		
		
//		output << "const RangePropertyValue values[];"<< endl;
		output << "PropertyValue get_value(char32_t cp);"<< endl;
		output << endl;

		output << get_namespace_end(_namespace) << endl;
		output << "#endif" << endl;
		
		output.close();
		
		
//		output.open("../../GraphemeBreak1/GraphemeBinary_Auto.cpp");
		output.open(filename + "_impl.h");
		output << endl;
		output << "#include \"" << extract_file_name(filename) <<".h\"" << endl;
		output << "#include <algorithm>"<< endl;
		output << endl;

		output << get_namespace_begin(_namespace)  << endl;
		output << endl;

		output << "const int values_size = " << graphemeBreakInfoParser.properties.size() << ";" << endl;		
		output << endl;
		output << "typedef PropertyValue PV;" <<endl;
		output << endl;
		
		output << "const RangePropertyValue values[] = {"<< endl;		
		output << hex;
		for(auto it=graphemeBreakInfoParser.properties.begin();
				it!=graphemeBreakInfoParser.properties.end();++it)	{
			if (it!=graphemeBreakInfoParser.properties.begin())	{
				output << ", " << endl;
			}
			
			//output << "\t{0x" << it->begin << ", 0x" << it->end << ", PV::" << it->value << " }   "; //(tokens.size()>1?tokens[1]:"") << endl;			
			output << "\t{0x" << it->begin << ", 0x" << it->end << ", PV::" << graphemeBreakInfoParser.values.get_value(it->value) << " }   "; 
		 	
		}
		output << "};"<< endl;
		output <<  endl;
		
		output << "PV get_value(char32_t cp)	{"<< endl;
		output << "\tconst RangePropertyValue* end = values + values_size;"<< endl;
		output << "\tRangePropertyValue v;"<< endl;
		output << "\tv.begin = cp;"<< endl;
		output << "\tv.end = cp;"<< endl;
//		output << "\tconst RangePropertyValue* it = std::find(values, end, v);"<< endl;
//		output << "\tif (it!=end)	{"<< endl;
		output << "\tconst RangePropertyValue* it = std::lower_bound(values, end, v);"<< endl;
		output << "\tif (it!=end && v.begin>= it->begin && v.end<=it->end)	{"<< endl;
/*
	const RangePropertyValue* it = std::lower_bound(values, end, v);	
	//if (it!=end)	{
	if(it!=end && v.begin>= it->begin && v.end<=it->end){
*/
		
		output << "\t\treturn it->value;"<< endl;
		output << "\t}"<< endl;
		output << "\treturn PV::Other;"<< endl;
		
		output << "}"<< endl;
		output << endl;
		output << get_namespace_end(_namespace) << endl;
		
	} else	{
		cout << "error opening file: " << filename  << endl;
	}
	
}

