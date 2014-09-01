/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "table_generator.h"
#include "info_parser.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename Type, typename Index, typename Getter> 
void create_table(
	const Getter& input, 
	int n1_bits, Index begin, Index end, 
	std::vector<std::vector<Type>>& n1_blocks, 
	std::vector<size_t>& n2_block )	;



			
		
GraphemeBreakTableGenerator::GraphemeBreakTableGenerator(
	GraphemeBreakInfoParser& graphemeBreakInfoParser)
:graphemeBreakInfoParser(graphemeBreakInfoParser)
{
}

GraphemeBreakTableGenerator::~GraphemeBreakTableGenerator()
{
}



void GraphemeBreakTableGenerator::generate_table_2n(int n1_bits, int n2_bits,
		const std::string& _filename, 
		const std::string& _namespace)	{
	size_t n1_block_size = 1<<n1_bits;
	size_t n2_block_size = 1<<n2_bits;
//	cout << "GraphemeBreakTableGenerator::generate_table_2n n1_block_size: " <<  n1_block_size << " n2_block_size: " <<  n2_block_size << endl;
	vector<Block<size_t>> n1_blocks;
//	vector<Block<char>> n2_blocks;
	size_t n1_index=0;
	size_t n2_index=0;
	Block<size_t> n1_block(n1_block_size);
	Block<size_t> n2_block(n2_block_size);
	char32_t cp_count = min(0x10ffff, (int)(n1_block_size * n2_block_size));
//	cout << "Util::do_table2() cp_count: " << hex <<  cp_count << dec << endl;
	
	for(char32_t cp=0;cp<=cp_count;++cp)	{
		if (cp%100000==0)	{
//			std::cout << "cp = " << cp << " cp_count: " << cp_count << std::endl;
		}
//	for(char32_t cp=0;cp<30;++cp)	{
		if (!cp==0 && cp%n1_block_size==0)	{
			auto it = find(n1_blocks.begin(),n1_blocks.end(), n1_block);
			if (it==n1_blocks.end())	{
				n1_blocks.push_back(n1_block);
				n2_block[n2_index] = n1_blocks.size()-1;
			}else	{
				n2_block[n2_index] = it-n1_blocks.begin();
			}
			++n2_index;
			n1_index=0;
		}
		n1_block[n1_index] = graphemeBreakInfoParser.get_value(cp);
		++n1_index;
	}
//	if (n1_index>0) // last one
	{
		auto it = find(n1_blocks.begin(),n1_blocks.end(), n1_block);
		if (it==n1_blocks.end())	{
			n1_blocks.push_back(n1_block);
//				cout << "anadir bloque: " <<  n1_blocks.size() << endl;
			n2_block[n2_index] = n1_blocks.size()-1;
		}else	{
			n2_block[n2_index] = it-n1_blocks.begin();
		}
		++n2_index;
		
	}
//PropertyValue get_value(char32_t cp);
//	cout << "n1_blocks.size(): " <<  n1_blocks.size() << " mem:" << n1_blocks.size()*n1_block_size << endl;
/*	cout << "n2_index: " 
		<<  n2_index  << " n2_block.size:" << n2_block.size 
		<<  " Total: " << n1_blocks.size()*n1_block_size + n2_index << endl;
*/
	do_files_2n(n1_bits, n1_blocks,	n2_block, n2_index, _filename, _namespace);
	
}

void GraphemeBreakTableGenerator::do_files_2n(int n1_bits, std::vector<Block<size_t>>& n1_blocks,	
	Block<size_t>& n2_block, 	size_t n2_length,
		const std::string& _filename, 
		const std::string& _namespace) {
	//ofstream output("../../GraphemeBreak1/GraphemeTable_Auto.h");
	//cout << "file: " << _filename << endl;
	ofstream output(_filename+".h");
	
	GraphemeBreakCommonGenerator common(graphemeBreakInfoParser);
	if (output.is_open())	{
		output << "#ifndef " << get_guard(_namespace) << "_H" << endl;
		output << "#define " << get_guard(_namespace) << "_H" << endl;
		output << endl;

		output << "#include <string> "<< endl;
		output << "#include <ostream> "<< endl;
		
		output << endl;
		output << get_namespace_begin(_namespace) << endl;
		output << endl;
		
		common.generate_common(output);
		
		output << endl;
			
		output << "PropertyValue get_value(char32_t cp);"<< endl;
		output << endl;
	
		output << get_namespace_end(_namespace) << endl;
		output << "#endif" << endl;

		output.close();
		
		
//		output.open("../../GraphemeBreak1/GraphemeTable_Auto.cpp");
		output.open(_filename + "_impl.h");
		output << endl;
		output << "#include \"" << extract_file_name(_filename) <<".h\"" << endl;
		output << endl;
		output << get_namespace_begin(_namespace) << endl;
		output << endl;
	
		output << "// Size: n1_blocks*size(n1_blocks) + size(n2_block):" ;
		output << n1_blocks.size()*n1_blocks[0].size + n2_length << endl;

		output << endl;
		
		output <<"\tunsigned char n2_values[] {"<< endl;

		for(size_t i=0;i<n2_length;++i)	{
			if (i!=0)	{
				output << ", ";
			}
			if (i%8==0)	{
				output << endl << "\t\t"; 
			}
			output << (0xff&n2_block.buffer[i]);
		}
		
		output <<"\t};\n";
		output << endl;
		
		output << "typedef PropertyValue PV;" << endl;
		output << endl;

		output <<"\tPropertyValue n1_values[][" << n1_blocks[0].size << "] {"<< endl;
		//typedef vector<Block<GraphemeBinary::PropertyValue>> _Block;
		for(auto block=n1_blocks.begin();block!=n1_blocks.end();++block)	{
			if (block!=n1_blocks.begin())	{
				output << ", " << endl;
			}
			output << "\t\t{" << endl << "\t\t\t";
			for(size_t i = 0; i< block->size;++i)	{
				if (i!=0)	{
					output << ", ";
					if (i%8==0)	{
						output << endl;
						output << "\t\t\t";
					}
				}
				//const string* s = block->buffer[i];
				const string& s = graphemeBreakInfoParser.values.get_value(block->buffer[i]);
				
				output << "PV::" << s;
			}
			output << endl << "\t\t}";			
		}
		output << "\t};" << endl;
		output << endl;
		output << endl;
	
		output << "PV get_value(char32_t cp)	{"<< endl;
//		output << "	int n1 = cp & 0xff;"<< endl;
//		output << "	int n2 = cp>>8;"<< endl;
		int n1_mask=1;
		for(int i=1;i<n1_bits;i++)	{
			n1_mask <<= 1;
			n1_mask |= 1;
		}
		int n2_mask=1;
		for(size_t i=1;i<sizeof(size_t)-n1_bits;i++)	{
			n2_mask <<= 1;
			n2_mask |= 1;
		}
		output << "\tint n1 = cp & 0x" << hex << n1_mask << dec << ";"<< endl;
		output << "\tint n2 = (cp>>" << n1_bits << ") & " << n2_mask << ";"<< endl;
//		output << "\tint n3 = cp>>(" << n1_bits+n2_bits << ");"<< endl;


		output << " 	return n1_values[n2_values[n2]][n1];"<< endl;
		output << "}"<< endl;
		output << endl;
	
		output << get_namespace_end(_namespace) << endl;

	} else	{
		cout << "error opening file" << endl;
	}

}

void GraphemeBreakTableGenerator::do_files_3n(
	std::vector<vector<size_t>>& n1_blocks,	int n1_bits,
	std::vector<std::vector<size_t>>& n2_blocks,	int n2_bits, 
	std::vector<size_t>& n3_block,	int n3_bits,
		const std::string& _filename, 
		const std::string& _namespace) {
		
//	ofstream output("../../GraphemeBreak1/GraphemeTable2_Auto.h");
	ofstream output(_filename+".h");
	if (output.is_open())	{
		output << "#ifndef " << get_guard(_namespace) << "_H" << endl;
		output << "#define " << get_guard(_namespace) << "_H" << endl;
		
//		output << "#include \"GraphemeCommon_Auto.h\"" << endl;
		output << "#include <string> "<< endl;
		output << "#include <ostream> "<< endl;
		output << endl;
		
		output << get_namespace_begin(_namespace) << endl;
		output << endl;

		
		GraphemeBreakCommonGenerator common(graphemeBreakInfoParser);
		common.generate_common(output);
		output << endl;
			
		output << "PropertyValue get_value(char32_t cp);"<< endl;
		output << endl;
	
		output << get_namespace_end(_namespace) << endl;
		output << "#endif" << endl;

		output.close();
		
		
//		output.open("../../GraphemeBreak1/GraphemeTable2_Auto.cpp");
		output.open(_filename + "_impl.h");
		output << endl;
		
		
		
		output << "#include \"" << extract_file_name(_filename) << ".h\"" << endl;
		output << endl;
		output << get_namespace_begin(_namespace) << endl;
		output << endl;

		output << "// Size: n1_blocks*size(n1_blocks) + n2_block*size(n2_block) + (n3_block):" ;
		output << n1_blocks.size()*n1_blocks[0].size() + n2_blocks.size()*n2_blocks[0].size() + n3_block.size()<< endl;

		if (n3_block.size()>0)	{
			output <<"\tunsigned char n3_values[] {"<< endl;
			for(size_t i=0;i<n3_block.size();++i)	{
				if (i!=0)	{
					output << ", ";
				}
				if (i%8==0)	{
					output << endl << "\t\t"; 
				}
				output << (0xff&n3_block[i]);
			}
		}
		output <<"\t};\n";
		output << endl;

		output <<"\tunsigned char n2_values[][" << n2_blocks[0].size() << "] {"<< endl;
		for(auto block=n2_blocks.begin();block!=n2_blocks.end();++block)	{
			if (block!=n2_blocks.begin())	{
				output << ", " << endl;
			}
			output << "\t\t{" << endl << "\t\t\t";
			for(size_t i=0;i<block->size();++i)	{
				if (i!=0)	{
					output << ", ";
				}
				if (i%8==0)	{
					output << endl << "\t\t"; 
				}
				output << (0xff&(*block)[i]);
			}		
			output <<"\t}";
			output << endl;
		}
		output <<"\t};\n";
		output << endl;
		
		output << "typedef PropertyValue PV;" << endl;
		output << endl;

		output <<"\tPropertyValue n1_values[][" << n1_blocks[0].size() << "] {"<< endl;
		//typedef vector<Block<GraphemeBinary::PropertyValue>> _Block;
		for(auto block=n1_blocks.begin();block!=n1_blocks.end();++block)	{
			if (block!=n1_blocks.begin())	{
				output << ", " << endl;
			}
			output << "\t\t{" << endl << "\t\t\t";
			for(size_t i = 0; i< block->size();++i)	{
				if (i!=0)	{
					output << ", ";
					if (i%8==0)	{
						output << endl;
						output << "\t\t\t";
					}
				}
				//const string* s = (*block)[i];
				const string s = graphemeBreakInfoParser.values.get_value((*block)[i]);
				output << "PV::" << s;
			}
			output << endl << "\t\t}";			
		}
		output << "\t};" << endl;
		output << endl;
		output << endl;
	
		output << "PV get_value(char32_t cp)	{"<< endl;
		int n1_mask=1;
		for(int i=1;i<n1_bits;i++)	{
			n1_mask <<= 1;
			n1_mask |= 1;
		}
		int n2_mask=1;
		for(int i=1;i<n2_bits;i++)	{
			n2_mask <<= 1;
			n2_mask |= 1;
		}
		output << "\tint n1 = cp & 0x" << hex << n1_mask << dec << ";"<< endl;
		output << "\tint n2 = (cp>>" << n1_bits << ") & " << n2_mask << ";"<< endl;
		output << "\tint n3 = cp>>(" << n1_bits+n2_bits << ");"<< endl;
		output << "\treturn n1_values[n2_values[n3_values[n3]][n2]][n1];"<< endl;			

		
		
		output << "}"<< endl;
		
		
		output << endl;
	
		output << get_namespace_end(_namespace) << endl;

	} else	{
		cout << "error opening file" << endl;
	}

}


template <typename Type>
void log(string& message, std::vector<std::vector<Type>>& n1_blocks)	
{
	cout << message << endl;
	for(auto it1=n1_blocks.begin(); it1!=n1_blocks.end();++it1)	{
		cout << "{" ;
		for(auto it2=it1->begin(); it2!=it1->end();++it2)	{
			cout << *it2 << ','; 
		}
		cout << "} " << endl;
	}	
}

void log(const string& message, std::vector<size_t>& n2_block )	{
	cout << message << endl;
	cout << "{" ;
	for(auto it1=n2_block.begin(); it1!=n2_block.end();++it1)	{
		cout << *it1 << ','; 
	}
	cout << "} " << endl;
	
}

struct PropGetter{
	GraphemeBreakInfoParser& parser;
	PropGetter(GraphemeBreakInfoParser& parser)
	:parser(parser)
	{
	}
/*	const string operator[](char32_t cp) const	{
		return parser.get_str_value(cp);
	}*/	
	size_t operator[](char32_t cp) const	{
		return parser.get_value(cp);
	}	
};

void GraphemeBreakTableGenerator::generate_table_3n(int n1_bits, int n2_bits,
		const std::string& _filename, 
		const std::string& _namespace)	{
//	vector<char> input(values, values+20);
//	vector<char> input(values, values+20);
//	std::vector<RangePropertyValue>& input = graphemeBreakInfoParser.properties;
	PropGetter input(graphemeBreakInfoParser);
	vector<vector<size_t>> n1_blocks;
	vector<size_t> n2_block;	
	vector<vector<size_t>> n2_blocks;	
	vector<size_t> n3_block;	
	
	create_table(input, n1_bits, 0, 0x10ffff+1, n1_blocks, n2_block);
	string s1("n1_blocks");
	//log(s1, n1_blocks);
	//log("n2_block", n2_block);

	create_table<size_t, size_t, vector<size_t>>(n2_block, n2_bits, 0, n2_block.size(), n2_blocks, n3_block);
	string s2("n2_blocks");
	//log(s2, n2_blocks);
	//log("n3_block", n3_block);
	
	do_files_3n(n1_blocks, n1_bits, n2_blocks, n2_bits, n3_block, 0, _filename, _namespace);
	
}


template <typename Type, typename Index, typename Getter> 
void create_table(
	const Getter& input, 
	int n1_bits, Index begin, Index end, 
	std::vector<std::vector<Type>>& n1_blocks, 
	std::vector<size_t>& n2_block )	
{		
	size_t n1_block_size = 1<<n1_bits;
//	vector<Block<char>> n2_blocks;
	size_t n1_index=0;
	size_t n2_index=0;
	std::vector<Type> n1_block;
	
	
	for(Index cp=begin;cp<end;++cp)	{
//	for(char32_t cp=0;cp<30;++cp)	{
		if (!cp==0 && cp%n1_block_size==0)	{
			auto it = find(n1_blocks.begin(),n1_blocks.end(), n1_block);
			if (it==n1_blocks.end())	{
				n1_blocks.push_back(n1_block);
//				n2_block[n2_index] = n1_blocks.size()-1;
				n2_block.push_back(n1_blocks.size()-1);
			}else	{
//				n2_block[n2_index] = it-n1_blocks.begin();
				n2_block.push_back(it-n1_blocks.begin());
			}
			n1_block.clear();
			++n2_index;
			n1_index=0;
		}
//		n1_block[n1_index] = input[cp];
		n1_block.push_back(input[cp]);
		++n1_index;
	}
//	if (n1_index>0) // last one
	{
		auto it = find(n1_blocks.begin(),n1_blocks.end(), n1_block);
		if (it==n1_blocks.end())	{
			n1_blocks.push_back(n1_block);
			//n2_block[n2_index] = n1_blocks.size()-1;
			n2_block.push_back(n1_blocks.size()-1);
		}else	{
			//n2_block[n2_index] = it-n1_blocks.begin();
			n2_block.push_back(it-n1_blocks.begin());
		}
		++n2_index;
	}	
}

