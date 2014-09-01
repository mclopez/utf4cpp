/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "info_parser.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;




GraphemeBreakInfoParser::GraphemeBreakInfoParser(const std::string& file)
:file(file)
{
}

GraphemeBreakInfoParser::~GraphemeBreakInfoParser()
{
}

size_t GraphemeBreakInfoParser::get_value(char32_t cp)	{
	for(auto it=properties.begin();it!=properties.end();++it)	{
		if (it->begin<=cp && cp<=it->end)	{
			return it->value;
		}
	}
	//return values.get("Other");
	return 0;
}

const std::string GraphemeBreakInfoParser::get_str_value(char32_t cp){
	for(auto it=properties.begin();it!=properties.end();++it)	{
		if (it->begin<=cp && cp<=it->end)	{
			return values.get_value(it->value); 
		}
	}
	return "Other";
}


void GraphemeBreakInfoParser::parse()	{
	ifstream fs(file);
	values.insert("Other");// per estar segur de que  hi es
	string line;
	while (getline(fs, line))	{
//		cout << line << endl;
		if (!line.empty()&&line[0]=='#')	{
			continue;
		}
		
		vector<string> tokens = split(line, "#");
		if (!tokens.empty())	{
			string info = tokens[0];
//			cout << "tokens[0]: "<< tokens[0] << endl;
			vector<string> tokens2 = split(tokens[0], ";");
			if (tokens2.size()>1 && !tokens2[0].empty())	{
				string value = trim(tokens2[1]);
				string range = trim(tokens2[0]);				
				vector<string> codepoints = split(range, "..");
				string cp1 = codepoints[0];
				string cp2 = codepoints[0];
				if (codepoints.size()>1)	{
					cp2 = codepoints[1];
				}
				RangePropertyValue p;
				p.begin = to_codepoint(cp1);
				p.end = to_codepoint(cp2);
/*				if (p.end==-1)	{
					cout << " p.end==-1 for " << cp2 << endl; 
					p.end = p.begin;
				}
				p.value = values.insert(value);
				if (p.begin!=-1)	{
					properties.push_back(p);
				}*/
				p.value = values.insert(value);
				properties.push_back(p);
				
			}
			
		}
					
	}
	sort(properties.begin(), properties.end());
	
}

std::vector<std::string> GraphemeBreakInfoParser::enum_values()	{
	std::vector<std::string> values_aux;
	for(size_t i=0;i<values.size();++i)	{
		values_aux.push_back(values.get_value(i));
	}	
	return values_aux;
}


void GraphemeBreakCommonGenerator::generate_common(ofstream& output)	{
//	ofstream output("../../GraphemeBreak1/GraphemeCommon_Auto.h");
	if (output.is_open())	{
		
		if (graphemeBreakInfoParser.values.size()<(2^8))	{
			output << "enum class PropertyValue : unsigned char {" << endl; 
		} else if(graphemeBreakInfoParser.values.size()<(2^16)){
			output << "enum class PropertyValue : unsigned short {" << endl; 
		}
//		output << "\tOther, " << endl;
//		output << "enum PropertyValue {";
		for(auto it=graphemeBreakInfoParser.values.begin();
				it!=graphemeBreakInfoParser.values.end();++it)	{
			if (it!=graphemeBreakInfoParser.values.begin())	{
				output << ", " << endl;
			}
			output << '\t' << *it;
		}	
		output << endl << "};" << endl;
		output << endl;		
		
		output << "inline" << endl;
		output << "std::ostream& operator <<(std::ostream& os, PropertyValue v)	{" << endl;
		output << " switch(v)	{" << endl;
		for(auto it=graphemeBreakInfoParser.values.begin();
			it!=graphemeBreakInfoParser.values.end();++it)	{
			output << "		case PropertyValue::" << *it << ": os << \"" << *it << "\"; break;" << endl;
		}		
		output << "		default:" << endl;
		output << "			os << \"unknown\";" << endl;
		output << "	}" << endl;
		output << "	return os;" << endl;
		
		output << "}" << endl;
		output << endl;
	
		
		
	}	
}


