/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef GRAPHEMEBREAKINFOPARSER_H
#define GRAPHEMEBREAKINFOPARSER_H

#include <iostream>
#include <fstream>

#include "util.h"
 
class GraphemeBreakInfoParser {


	std::string file;
public:
	GraphemeBreakInfoParser(const std::string& file);
	~GraphemeBreakInfoParser();

	MySet<std::string> values;
//	std::set<std::string> values;
	std::vector<RangePropertyValue> properties;
	size_t get_value(char32_t cp);
	const std::string get_str_value(char32_t cp);

	void parse();
	std::vector<std::string> enum_values();
};


class GraphemeBreakCommonGenerator{
	GraphemeBreakInfoParser& graphemeBreakInfoParser;
public:	

	GraphemeBreakCommonGenerator(GraphemeBreakInfoParser& graphemeBreakInfoParser)
	:graphemeBreakInfoParser(graphemeBreakInfoParser)
	{
	}
	void generate_common(std::ofstream& output);
};


#endif // GRAPHEMEBREAKINFOPARSER_H
