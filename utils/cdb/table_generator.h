/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef GRAPHEMEBREAKTABLEGENERATOR_H
#define GRAPHEMEBREAKTABLEGENERATOR_H

#include "info_parser.h"

class GraphemeBreakTableGenerator {


	GraphemeBreakInfoParser& graphemeBreakInfoParser;
public:
	GraphemeBreakTableGenerator(
			GraphemeBreakInfoParser& graphemeBreakInfoParser);
	~GraphemeBreakTableGenerator();

	void generate_cobmmon();
	void generate_table_2n(int n1_bits, int n2_bits,
		const std::string& _filename, 
		const std::string& _namespace) ;
	void do_files_2n(
		int n1_bits, 
		std::vector<Block<size_t>>& n1_blocks,	
		Block<size_t>& n2_block, size_t n2_length,
		const std::string& _filename, 
		const std::string& _namespace);
	
	
	void generate_table_3n(int n1_bits, int n2_bits,
		const std::string& _filename, 
		const std::string& _namespace);
	void do_files_3n(
		std::vector<std::vector<size_t>>& n1_blocks, int n1_bits,	
		std::vector<std::vector<size_t>>& n2_blocks, int n2_bits,
		std::vector<size_t>& n3_block, int n3_bits,
		const std::string& _filename, 
		const std::string& _namespace) ;

/*	std::vector<std::string> enum_values()	{
//			return graphemeBreakInfoParser.values().values;
	}
*/
	const GraphemeBreakInfoParser& parser() { return graphemeBreakInfoParser;}
};

#endif // GRAPHEMEBREAKTABLEGENERATOR_H
