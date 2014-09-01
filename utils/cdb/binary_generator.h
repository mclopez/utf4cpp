/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef GRAPHEMEBREAKBINARYGENERATOR_H
#define GRAPHEMEBREAKBINARYGENERATOR_H

#include "info_parser.h"

class GraphemeBreakBinaryGenerator {

	//MySet<std::string>& values;
	//std::vector<RangePropertyValue>& properties;
	GraphemeBreakInfoParser& graphemeBreakInfoParser;
	
public:
	GraphemeBreakBinaryGenerator(GraphemeBreakInfoParser& graphemeBreakInfoParser);
	~GraphemeBreakBinaryGenerator();

	void generate_binary(const std::string& filename, const std::string& _namespace);

};

#endif // GRAPHEMEBREAKBINARYGENERATOR_H
