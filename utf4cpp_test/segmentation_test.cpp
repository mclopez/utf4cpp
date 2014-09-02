/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */



#include "segmentation_test.h"

#include "util.h"
#include "test.h"
#include "test_data.h"
#include <utf4cpp/unicpp.h>
#include <utf4cpp/segmentation.h>

//#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iterator>

namespace test
{

	using namespace unicpp;
	

struct SegmentationTest1	{
	static void exec()	{
		SegmentationTest1 t; t();
	}
	void operator()()	{
		typedef char32_t T;
		// tilde: 0x0303
//		char32_t b1[]  = {0x0061, 0x0308, 0x0303, 0x0323, 0x032D, 0x0000};
//		char32_t b2[]  = {0x0065, 0x0063, 0x0327, 0x0066, 0x0000};
		char32_t b1[]  = {0xAC00, 0x0308, 0x0E40, 0x0000}; //÷ AC00 × 0308 ÷ 0E40 ÷	
//		char32_t b2[]  = {0x0000}; //÷ AC00 × 0308 ÷ 0E40 ÷	
		char32_t b2[]  = {0xAC00, 0x0308, 0x0903, 0x0000};//÷ AC00 × 0308 × 0903 ÷

		std::basic_string<T> input1(b1);
		std::basic_string<T> input(b2);
		input += input1;
		//std::basic_string<T> input = create_container<std::basic_string<T>>();
		
//		auto const_begin = make_const_iterator(input.begin());
//		auto const_end = make_const_iterator(input.end());

		//unicpp::grapheme_iterator<unicpp::const_iterator<std::basic_string<T>::iterator> > gr_begin(const_begin); 
		//grapheme_range<const_iterator< std::basic_string<T>::iterator > > gr(const_begin, const_end);
/*		v3::segmentation_range<const_iterator< std::basic_string<T>::iterator >, v3::GraphemeSplitter<std::basic_string<T>::iterator> > gr(const_begin, const_end);
 
		//auto it1=gr.begin()
		int count =0;
		for(auto it=gr.begin();it!=gr.end();++it)	{
			cout << "*it: " <<std::hex <<  *it.current() << endl;
			count++;
		}
		cout << "count: " << count << endl;
*/
//		BOOST_CHECK(*it==*it_ref);
	}
};

/*
template<typename T> 
struct SegmentationTest2	{
	static void exec()	{
		SegmentationTest2<T> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		auto const_begin = make_const_iterator(input.begin());
		auto const_end = make_const_iterator(input.end());

		//unicpp::grapheme_iterator<unicpp::const_iterator<std::basic_string<T>::iterator> > gr_begin(const_begin); 
		segmentation_range<const_iterator< typename std::basic_string<T>::iterator > > gr(const_begin, const_end);
 
		//auto it1=gr.begin()
		int count =0;
		for(auto it=gr.begin();it!=gr.end();++it)	{
			count++;
		}
		cout << "count: " << count << endl;
//		BOOST_CHECK(*it==*it_ref);
	}
};
*/

	
int32_t to_int(string s)	{
	stringstream ss;
	ss << s;
	int32_t i;
	ss >> hex;
	ss >> i;
	return i;
}	

string to_str(int32_t i)	{
	stringstream ss;
	ss << hex << uppercase << setw(4) << i;
	string s;
	ss >> s;
	while (s.size()<4)	{
		s = "0" + s;
	}
	return s;
}	

template<typename T> 
struct GraphemeSegmentationTest	{
	static void exec()	{
		GraphemeSegmentationTest<T> t; t();
	}
	
	void init()	{
		ifstream fs("unicode/Segmentation/test/GraphemeBreakTest.txt");
		string line;
		bool error = false;
		int line_num =0;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			++line_num;
			
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				string generated = generate_token(original);
				if (original!=generated)	{
					cout << "in line :  '" <<std::dec<< line_num << "'" << endl;
					cout << "ERROR:" << endl;
					cout << "original:  '" << original  << "'" << endl;
					cout << "generated: '" << generated << "'" << endl;
					
					error = true;
					break;
					
				}
				//cout << "original:  '" << original  << "'" << endl;
				//cout << "generated: '" << generated << "'" << endl;
			}
		}
		if (error)	{
		} else 	{
			cout << "OK :  lines: " << line_num << endl;
			
		}
//		BOOST_CHECK(!error);		
	}
	
	static u32string extract_string(const string& original)	{
//		cout << "GraphemeSegmentationTest<T>::extract_string() " << original;
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
//		cout << "GraphemeSegmentationTest<T>::extract_string() end" << endl;
//		cout << result << endl;
		return result;
	}
	
	string generate_token(string original)	{
		using namespace unicpp;
		
		//cout << "GraphemeSegmentationTest<T>::generate_token() original: " << original << endl;
		u32string test = extract_string(original);
		//cout << "GraphemeSegmentationTest<T>::generate_token() test: " << test  << endl;
		
		string result("÷");		
		
		// copy from u32string to the target basic_string<T>
		basic_stringbuf<T> sb;
		auto sbi = streambuf_inserter(&sb);
		copy(make_const_iterator(test.begin()), make_const_iterator(test.end()), sbi);
		basic_string<T> test2 = sb.str();
		
		// iterate throght the graphemes 
		auto const_begin = make_const_iterator(test2.begin());
		auto const_end   = make_const_iterator(test2.end());
//		grapheme_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);

//marcos		
		typedef typename std::basic_string<T>::iterator _iterator;
		v3::segmentation_range<const_iterator< _iterator >, v3::GraphemeTokenizer > gr(const_begin, const_end);
		
		auto it_r1 = gr.begin();
		auto it_r2 = it_r1;
		++it_r2;
		
		while (it_r1!=gr.end())	{
			//cout << hex << setw(4) << "*it_r1: " << *it_r1.current() << " *it_r2: " << *it_r2.current() << endl;
			if (it_r1!=it_r2)	{
				/*cout << "if " <<  hex << setw(4) 
					<< " *it_r1:  "  << *it_r1.current() 
					<< " *it_r2: " << *it_r2.current() << endl;*/
				string result2;
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux++)	{
					//result.push_back();
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				result.append(result2);
				result.append(" ÷");
				it_r1= it_r2;
				++it_r2;
			}
		}
		return result;
	}
	
	void operator()()	{
		init();		
	}
};



template<typename T> 
struct WordSegmentationTest	{
	static void exec()	{
		WordSegmentationTest<T> t; t();
	}
	
	void init()	{
		cout << "WordSegmentationTest::init()" << endl; 
		ifstream fs("unicode/Segmentation/test/WordBreakTest.txt");
		string line;
		int num_line=0;
		bool error = false;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			num_line++;
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				//cout << " ******'" << endl;
				//cout << " target :  '" << original  << "'" << endl;
				//cout << " ******'" << endl;
				u32string text = generate_u32string(original);
				
				string generated = generate_token(text);
				//cout << " generated :  '" << generated << "' line: " << std::dec << num_line << endl;
				
				if (original!=generated)	{
					//cout << "original:  '" << original  << "'" << endl;
					cout << "error:  "  << original << "!=  generated: '" << generated << "' in line: " << std::dec << num_line << endl;
					error = true;
					break;
				}else	{
				//cout << " *** OK *** " << endl;
					
				}
					//cout << "original:  '" << original  << "'" << endl;
					//cout << "generated: '" << generated << "'" << endl;
			}
		}
		if (error)	{
			
		}else	{
			cout << "WordSegmentationTest " << sizeof(T) << " OK lines:" << std::dec <<  num_line << endl;
		}
		//BOOST_CHECK(!error);		
	}
	
	u32string generate_u32string(const string& original)	{
//		cout << "WordSegmentationTest<T>::generate_u32string() " << original << endl; 
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
		return result;
	}

	string generate_token(u32string test)	{
//		cout << "WordSegmentationTest<T>::generate_token() "  << endl; 
		using namespace unicpp;
		string result("÷");		
		basic_string<T> test2;
		convert(test, test2);		
		// iterate throght the graphemes 
		auto const_begin = make_const_iterator(test2.begin());
		auto const_end   = make_const_iterator(test2.end());

//		word_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);
		typedef typename std::basic_string<T>::iterator _iterator;
		v3::segmentation_range<const_iterator< _iterator>, v3::WordTokenizer> gr(const_begin, const_end);

		auto it_r1 = gr.begin();
		auto it_r2 = it_r1;
		++it_r2;
		
		while (it_r1!=gr.end())	{
			if (it_r1!=it_r2)	{
				string result2;
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux++)	{
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				result.append(result2);
				result.append(" ÷");
				it_r1= it_r2;
				//if (it_r2!=gr.end())
					++it_r2;
			}else	{
				cout << "WordSegmentationTest<T>::generate_token() error: no change!" << endl; 
				break;
			}
				
		}

//		cout << "WordSegmentationTest<T>::generate_token() end" << endl; 
		return result;
	}
	
	void operator()()	{
		init();		
		//cout << "generate_token: " <<   generate_token("÷ 0001 × 0308 ÷ 0001 ÷") << endl;;
	}
};

template<typename Tokenizer>
struct TokenizerTraits;

template<>
struct TokenizerTraits<unicpp::v3::GraphemeTokenizer>	{
	constexpr static const char* test_file = "unicode/Segmentation/test/6.3.0/GraphemeBreakTest.txt";
};

template<>
struct TokenizerTraits<unicpp::v3::WordTokenizer>	{
	constexpr static const char* test_file = "unicode/Segmentation/test/6.3.0/WordBreakTest.txt";
};

template<>
struct TokenizerTraits<unicpp::v3::SentenceTokenizer>	{
	constexpr static const char* test_file = "unicode/Segmentation/test/6.3.0/SentenceBreakTest.txt";
};

/*
template<>
struct TokenizerTraits<unicpp::v3::LineTokenizer>	{
	constexpr static const char* test_file = "unicode/Segmentation/test/LineBreakTest.txt";
};
*/

/*

template<typename CharT, typename Tokenizer> 
struct GenericSegmentationTest	{
	static void exec()	{
		GenericSegmentationTest<CharT, Tokenizer> t; t();
	}
	
	void init()	{
		cout << "init()" << endl; 
		ifstream fs(TokenizerTraits<Tokenizer>::test_file);
		string line;
		int num_line=0;
		bool error = false;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			num_line++;
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				cout << " ******'" << endl;
				cout << " target :  '" << original  << "' " << " line: " << std::dec << num_line << endl;
				cout << " ******'" << endl;
				error = !process_string(original);
				if (error)	{
					cout << "error in line :  "  << std::dec << num_line <<  endl;
					break;
					
				}
			}

		}
		//BOOST_CHECK(!error);		
	}
	
	void init2()	{
//		std::string original = "÷ 0028 × 0022 × 0047 × 006F × 002E × 0022 × 0029 × 0020 ÷ 0028 × 0048 × 0065 × 0020 × 0064 × 0069 × 0064 × 002E × 0029 ÷";
//		std::string original = "÷ 002E × 0022 × 0029 × 0020 ÷ 0028 ÷";
//		std::string original = "÷ 002E × 0061 ÷";
//		std::string original = "÷ 002E × 0308 ÷ 0001 ÷";
		std::string original = "÷ 002E × 0001 ÷";
		bool error = !process_string(original);
		if (error)	{
			cout << "ERROR" <<  endl;
		}		
	}
	
	bool process_string(const std::string& original)	{
		cout << " original :  '" << original << endl;
		u32string text = generate_u32string(original);
		
		string generated = generate_token(text);
		cout << " generated :  '" << generated  << endl;
		
		if (original!=generated)	{
			//cout << "original:  '" << original  << "'" << endl;
			cout << "Error:\n"
				"xxx original:  "<< original << "\ngenerated: " << generated << endl;
//			error = true;
//			break;
			return false;
		}else	{
			cout << " *** OK *** " << endl;
			
		}
		//cout << "original:  '" << original  << "'" << endl;
		//cout << "generated: '" << generated << "'" << endl;
		return true;
	}
	
	u32string generate_u32string(const string& original)	{
//		cout << "WordSegmentationTest<T>::generate_u32string() " << original << endl; 
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
		return result;
	}

	string generate_token(u32string test)	{
//		cout << "WordSegmentationTest<T>::generate_token() "  << endl; 
		using namespace unicpp;
		string result("÷");		
//		string result("×");		
		basic_string<CharT> test2;
		convert(test, test2);		
		// iterate the graphemes 
		auto const_begin = make_const_iterator(test2.begin());
		auto const_end   = make_const_iterator(test2.end());

//		word_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);
		typedef typename std::basic_string<CharT>::iterator _iterator;
		v3::segmentation_range<const_iterator< _iterator>, Tokenizer> gr(const_begin, const_end);

		auto it_r1 = gr.begin();
		auto it_r2 = it_r1;
		++it_r2;
		
		while (it_r1!=gr.end())	{
			if (it_r1!=it_r2)	{
				string result2;
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux++)	{
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				result.append(result2);
				result.append(" ÷");
				it_r1= it_r2;
				//if (it_r2!=gr.end())
					++it_r2;
			}else	{
				cout << "GenericSegmentationTest<T>::generate_token() error: no change!" << endl; 
				break;
			}
				
		}

//		cout << "WordSegmentationTest<T>::generate_token() end" << endl; 
		return result;
	}
	
	void operator()()	{
		//init();		
		init2();		
	}
};

*/

template<typename T , typename Tokenizer> 
struct GenericSegmentationTest	{
	static void exec()	{
		go();
	}
	
	static void go()	{
		cout << "GenericSegmentationTest::init() eo" << endl;
		ifstream fs(TokenizerTraits<Tokenizer>::test_file);
		string line;
		bool error = false;
		int line_num =0;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			cout << "line_num:" << line_num << endl;
			++line_num;
			
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				string generated = generate_token(original);
/*				if (original!=generated)	{
					cout << "in line :  '" <<std::dec<< line_num << "'" << endl;
					cout << "ERROR:" << endl;
					cout << "original:  '" << original  << "'" << endl;
					cout << "generated: '" << generated << "'" << endl;
					
					error = true;
					break;
					
				}*/
				BOOST_CHECK_MESSAGE(original==generated, "line: '" << std::dec << line_num \
					<< "'\n original: " << original \
					<< "\n generated: '" << generated << "'" );
				if (original!=generated)	{
					break;
				}
					
				//cout << "original:  '" << original  << "'" << endl;
				//cout << "generated: '" << generated << "'" << endl;
			}
		}
		if (error)	{
		} else 	{
			cout << "OK :  lines: " << line_num << endl;
			
		}
//		BOOST_CHECK(!error);		
	}
	
	static u32string extract_string(const string& original)	{
//		cout << "GraphemeSegmentationTest<T>::extract_string() " << original;
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
//		cout << "GraphemeSegmentationTest<T>::extract_string() end" << endl;
//		cout << result << endl;
		return result;
	}
	
	static string generate_token(string original)	{
		using namespace unicpp;
		
		cout << "GraphemeSegmentationTest<T>::generate_token() original: " << original << endl;
		u32string test = extract_string(original);
//		cout << "GraphemeSegmentationTest<T>::generate_token() test: " << test  << endl;
		
		string result("÷");		
		
		// copy from u32string to the target basic_string<T>
		basic_stringbuf<T> sb;
		auto sbi = streambuf_inserter(&sb);
		copy(make_const_iterator(test.begin()), make_const_iterator(test.end()), sbi);
		basic_string<T> test2 = sb.str();
		
		// iterate throght the graphemes 
		auto const_begin = make_const_iterator(test2.begin());
		auto const_end   = make_const_iterator(test2.end());
//		grapheme_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);

//marcos		
		typedef typename std::basic_string<T>::iterator _iterator;
		v3::segmentation_range<const_iterator< _iterator >, Tokenizer > gr(const_begin, const_end);
		
		auto it_r1 = gr.begin();
		auto it_r2 = it_r1;
		++it_r2;
		
		while (it_r1!=gr.end())	{
			//cout << hex << setw(4) << "*it_r1: " << *it_r1.current() << " *it_r2: " << *it_r2.current() << endl;
			if (it_r1!=it_r2)	{
				/*cout << "if " <<  hex << setw(4) 
					<< " *it_r1:  "  << *it_r1.current() 
					<< " *it_r2: " << *it_r2.current() << endl;*/
				string result2;
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux++)	{
					//result.push_back();
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				result.append(result2);
				result.append(" ÷");
			}
			it_r1= it_r2;
			++it_r2;
			if (it_r1==it_r2)	{
				cout << "ERROR: it_r1==it_r2" << endl;
				break;
			}
		}
		return result;
	}
	
};

template<typename T , typename Tokenizer> 
struct GenericSegmentationTest2	{
	static void exec()	{
		go();
	}
	
	static void go()	{
		cout << "GenericSegmentationTest::init() eo" << endl;
		ifstream fs(TokenizerTraits<Tokenizer>::test_file);
		string line;
		bool error = false;
		int line_num =0;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			//cout << "line_num:" << line_num << endl;
			++line_num;
			
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				string generated = generate_token(original);

				BOOST_CHECK_MESSAGE(original==generated, "line: '" << std::dec << line_num \
					<< "'\n original: " << original \
					<< "\n generated: '" << generated << "'" );
				if (original!=generated)	{
					break;
				}
					
				//cout << "original:  '" << original  << "'" << endl;
				//cout << "generated: '" << generated << "'" << endl;
			}
		}
		if (error)	{
		} else 	{
			cout << "OK :  lines: " << line_num << endl;
			
		}
//		BOOST_CHECK(!error);		
	}
	
	static u32string extract_string(const string& original)	{
//		cout << "GraphemeSegmentationTest<T>::extract_string() " << original;
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
//		cout << "GraphemeSegmentationTest<T>::extract_string() end" << endl;
//		cout << result << endl;
		return result;
	}
	
	static string generate_token(string original)	{
		using namespace unicpp;
		
//		cout << "GraphemeSegmentationTest<T>::generate_token() original: " << original << endl;
		u32string test = extract_string(original);
//		cout << "GraphemeSegmentationTest<T>::generate_token() test: " << test  << endl;
		
		string result("÷");		
		
		// copy from u32string to the target basic_string<T>
		basic_stringbuf<T> sb;
		auto sbi = streambuf_inserter(&sb);
		copy(make_const_iterator(test.begin()), make_const_iterator(test.end()), sbi);
		basic_string<T> test2 = sb.str();
		
		// iterate throght the graphemes 
//		auto const_begin = make_const_iterator(test2.begin());
		auto const_end   = make_const_iterator(test2.end());
//		grapheme_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);

//		typedef typename std::basic_string<T>::iterator _iterator;
		
		auto it_r1 = make_const_iterator(test2.begin());
		auto it_r2 = it_r1;
		Tokenizer tokenizer;
		tokenizer.next(it_r2, const_end);
		
		while (it_r1!=const_end && it_r1!=it_r2)	{
			//cout << hex << setw(4) << "*it_r1: " << *it_r1.current() << " *it_r2: " << *it_r2.current() << endl;
			if (it_r1!=it_r2)	{
				/*cout << "if " <<  hex << setw(4) 
					<< " *it_r1:  "  << *it_r1.current() 
					<< " *it_r2: " << *it_r2.current() << endl;*/
				string result2;
				for(auto it_aux = it_r1; it_aux!=it_r2; it_aux++)	{
					//result.push_back();
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				result.append(result2);
				result.append(" ÷");
			}
			it_r1 = it_r2;
			tokenizer.next(it_r2, const_end);
//			BOOST_CHECK(it_r1!=it_r2);
			
			if (it_r1==it_r2 && it_r1!=const_end)	{
				cout << "ERROR: it_r1==it_r2" << endl;
				throw "ERROR";
				break;
			}
		}
		return result;
	}
	
};


template<typename CharT, typename Tokenizer> 
struct GenericBackwardsSegmentationTest	{
	static void exec()	{
		GenericBackwardsSegmentationTest<CharT, Tokenizer> t; t();
	}
	
	void init()	{
		//cout << "init()" << endl; 
		ifstream fs(TokenizerTraits<Tokenizer>::test_file);
		string line;
		int num_line=0;
		bool error = false;
		while (std::getline(fs, line))	{
			//cout << line << endl;
			num_line++;
			if (!line.empty()&&line[0]=='#')	{
				continue;
			}
			vector<string> tokens = split(line, "#");
			if (!tokens.empty())	{
				string original = rpad(tokens[0]);
				//cout << " ******'" << endl;
				//cout << " target :  '" << original  << "' " << " line: " << std::dec << num_line << endl;
				//cout << " ******'" << endl;
				error = !process_string(original);
				if (error)	{
					cout << "error in line :  "  << std::dec << num_line <<  endl;
					break;
					
				}
/*				
				u32string text = generate_u32string(original);
				string generated = generate_token(text);
				cout << " generated :  '" << generated << "' line: " << std::dec << num_line << endl;
				
				if (original!=generated)	{
					//cout << "original:  '" << original  << "'" << endl;
					cout << "error:  "  << original << "!=  generated: '" << generated << "' in line: " << std::dec << num_line << endl;
					error = true;
					break;
				}else	{
					cout << " *** OK *** " << endl;
					
				}
				//cout << "original:  '" << original  << "'" << endl;
				//cout << "generated: '" << generated << "'" << endl;
*/
			}

		}
		if (error)	{
		} else 	{
			cout << "OK :  lines: " << num_line << endl;
			
		}
		//BOOST_CHECK(!error);		
	}
	
	
	bool process_string(const std::string& original)	{
		u32string text = generate_u32string(original);
		
		string generated = generate_token(text);
		//cout << " generated :  '" << generated  << endl;
		
		if (original!=generated)	{
			//cout << "original:  '" << original  << "'" << endl;
			cout << "Error:\n"
				"original:  "<< original << "\ngenerated: " << generated << endl;
//			error = true;
//			break;
			return false;
		}else	{
//			cout << " *** OK *** " << endl;
			
		}
		//cout << "original:  '" << original  << "'" << endl;
		//cout << "generated: '" << generated << "'" << endl;
		return true;
	}
	
	u32string generate_u32string(const string& original)	{
//		cout << "WordSegmentationTest<T>::generate_u32string() " << original << endl; 
		stringstream ss(original);
		string scodepoint;
		u32string result;
		while(ss)	{
			ss >> scodepoint;
			//cout << scodepoint << endl;
			if (scodepoint!="×" && scodepoint!="÷")	{
				result.push_back(to_int(scodepoint));
			}
		}		
		return result;
	}

	void init2()	{
//		std::string original = "÷ 0028 × 0022 × 0047 × 006F × 002E × 0022 × 0029 × 0020 ÷ 0028 × 0048 × 0065 × 0020 × 0064 × 0069 × 0064 × 002E × 0029 ÷";
//		std::string original = "÷ 002E × 0022 × 0029 × 0020 ÷ 0028 ÷";
//		std::string original = "÷ 002E × 0061 ÷";

//		÷ 002E × 0308 ÷ 0001 ÷	#  ÷ [0.2] FULL STOP (ATerm) × [5.0] COMBINING DIAERESIS (Extend_FE) ÷ [11.0] <START OF HEADING> (Other) ÷ [0.3]
		std::string original = "÷ 002E × 0308 ÷ 0001 ÷";
		
//		std::string original = "÷ 002E × 0308 ÷";
		bool error = !process_string(original);
		if (error)	{
			cout << "ERROR" <<  endl;
		}		
	}

	string generate_token(u32string test)	{
//		cout << "WordSegmentationTest<T>::generate_token() "  << endl; 
		using namespace unicpp;
		string result("÷");		
//		string result("×");		
		basic_string<CharT> test2;
		convert(test, test2);		
		// iterate throght the graphemes 
		auto const_begin = --make_const_iterator(test2.begin());
		auto const_end   = --make_const_iterator(test2.end());

//		word_range<const_iterator< typename basic_string<T>::iterator > > gr(const_begin, const_end);
		typedef typename std::basic_string<CharT>::iterator _iterator;
		v3::segmentation_range<const_iterator< _iterator>, Tokenizer> gr(const_begin, const_end);

		auto const_aux = --make_const_iterator(test2.end());
		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *const_aux '" << std::hex <<  *const_aux << "'" << endl; 
		Tokenizer t;
		t.prior(const_aux, const_begin);
		if (const_aux!=const_begin){
			cout << "***GenericBackwardsSegmentationTest<T>::generate_token() const_aux!=const_begin " << endl; 
			cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *const_aux '" << std::hex <<  *const_aux << "'" << endl; 
		}
		if (const_aux!=const_begin){
			t.prior(const_aux, const_begin);
		}
		if (const_aux!=const_begin){
			cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *const_aux '" << std::hex <<  *const_aux << "'" << endl; 
		}
		return "" ;
		if (const_aux!=const_begin)

		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() end test "<< endl; 

		auto begin = gr.begin();
		auto it_r1 = gr.end();
		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *it_r1 '" << std::hex <<  *it_r1.current() << "'" << endl; 
		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *it_r1 '" << std::hex <<  *it_r1.current() << "'" << endl; 
		auto it_r2 = it_r1;
		--it_r2;
		--begin;
		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *it_r1 '" << *it_r1.current() << "'" << endl; 
		cout << "***GenericBackwardsSegmentationTest<T>::generate_token() *it_r2 '" << *it_r2.current() << "'" << endl; 
		while (it_r2!=begin)	{
			//cout << "***GenericBackwardsSegmentationTest<T>::generate_token() while '" << *it_r1.current() << "'" << endl; 
			cout << "***GenericBackwardsSegmentationTest<T>::generate_token() while *it_r1 '" << *it_r1.current() << "'" << endl; 
			cout << "***GenericBackwardsSegmentationTest<T>::generate_token() while *it_r2 '" << *it_r2.current() << "'" << endl; 
			if (it_r1!=it_r2)	{
				string result2;
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux--)	{
					if (!result2.empty())	{
						//result2.append(" ×");
						result2 = "× " + result2;
					}	
					result2 = to_str(*it_aux) + " " + result2;
				}
				result = "÷ " + result2 + result;
				it_r1 = it_r2;
				--it_r2;
			}else	{
				cout << "GenericBackwardsSegmentationTest<T>::generate_token() error: no change!" << endl; 
				break;
			}
				
		}

//		cout << "WordSegmentationTest<T>::generate_token() end" << endl; 
		return result;
	}
	



	void operator()()	{
		//init();		
		init2();		
	}
};

/*
struct SegmentationTest5	{
	static void exec()	{
		SegmentationTest5 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		//typedef char32_t T;
		typedef char T;
		// tilde: 0x0303
		string input = "o que non chora non mama";
//		string input = "\x1\x1";
		auto const_begin = make_const_iterator(input.begin());
		auto const_end = make_const_iterator(input.end());

		//unicpp::grapheme_iterator<unicpp::const_iterator<std::basic_string<T>::iterator> > gr_begin(const_begin); 
		word_range<const_iterator< std::basic_string<T>::iterator > > gr(const_begin, const_end);
 
		//auto it1=gr.begin()
		int count =0;
//		unicpp::const_iterator<basic_string<char>::iterator> aux = gr.begin().current();
		auto it = gr.begin();
		auto aux = it;
		++it;
		while(it!=gr.end())	{
			count++;
			std::basic_string<T> t(aux.current().base(), it.current().base());
			cout << "word: '" << t << "'"<< endl;
			aux = it;
			it++;
		}
		std::basic_string<T> t(aux.current().base(), it.current().base());
		cout << "word: " << t << endl;
		cout << "count: " << count << endl;
//		BOOST_CHECK(*it==*it_ref);
	}
};
*/
/*
template<typename C1, typename C2> 
void convert(const C1& c1, C2& c2)	{
	using namespace unicpp;
	copy(make_const_iterator(c1.begin()), make_const_iterator(c1.end()), unicpp::back_inserter(c2));	
};
*/

/*
template <typename CharT> 
struct SegmentationTest6	{
	
	static void exec()	{
		SegmentationTest6<CharT> t; t();
	}
	
	void operator()()	{
		using namespace unicpp;
		using namespace cdb::wordbreak;
		//typedef char T;
		//u16string input = u"\x0001\u0308\x0001";
		//u32string _input = U"\x0001\u0308\x0061\x2060";
		//u32string _input = U"\x000D\x0308\x0031\x002E\x2060"; // ÷ 000D ÷ 0308 ÷ 0031 ÷ 002E × 2060 ÷
		//u32string _input = U"\x3031\x3031"; // ÷ 3031 × 3031 ÷
		u32string _input = U"\x0001\x0308\x0031\x002E\x2060"; // ÷ 0001 × 0308 ÷ 0031 ÷ 002E × 2060 ÷		
		//input+=input;
		basic_string<CharT> input;
		convert(_input, input);
		
		auto const_begin = make_const_iterator(input.begin());
		auto const_end = make_const_iterator(input.end());
		typedef typename std::basic_string< CharT >::iterator str_it;
		
		word_range<const_iterator< str_it > > gr(const_begin, const_end);

//		cout << "WordSegmentationTest<T>::generate_token() 3" << endl; 
		
		auto it_r1 = gr.begin();
//		cout << "generate_token() 3b" << endl; 
		auto it_r2 = it_r1;
//		cout << "generate_token() 3c" << endl; 
		++it_r2;
//		cout << "generate_token() 3d" << endl; 

		
		
		while (it_r1!=gr.end())	{
			//cout << hex << setw(4) << "*it_r1: " << *it_r1.current() << " *it_r2: " << *it_r2.current() << endl;
//			cout << "generate_token() 4" << endl; 

			cout << "SegmentationTest6" << endl; 
			
			if (it_r1!=it_r2)	{
				cout << "SegmentationTest6 while 1" << endl; 
				string result2;
				cout << "SegmentationTest6 while 2" << endl; 
				for(auto it_aux = it_r1.current(); it_aux!=it_r2.current(); it_aux++)	{
					//result.push_back();
					if (!result2.empty())	{
						result2.append(" ×");
					}	
					result2.append(" ");
					result2.append(to_str(*it_aux));
				}
				cout << "SegmentationTest6 while 3 " << result2 << endl; 
				it_r1= it_r2;
				++it_r2;
			}
		}
		cout << "SegmentationTest6  end " <<  endl; 
		
	}
};
*/

boost::unit_test::test_suite* SegmentationTest::test_suite()	{
	cout << "SegmentationTest::test_suite() " << endl; 

	boost::unit_test::test_suite* test = BOOST_TEST_SUITE("segmentation_test.cpp");
//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, SegmentationTest1>::reg(test);
//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, SegmentationTest1>::reg(test);
	
//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, SegmentationTest1>::reg(test);
//	reg_function<SegmentationTest1>(test, &SegmentationTest1::exec);	
//	reg_function<SegmentationTest2>(test, &SegmentationTest2::exec);	

//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, GraphemeSegmentationTest> ::reg(test);
//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, WordSegmentationTest> ::reg(test);
	//reg_function<WordSegmentationTest<char32_t>>(test, &WordSegmentationTest<char32_t>::exec);	

//	reg_function<SegmentationTest5>(test, &SegmentationTest5::exec);	
//	reg_function<SegmentationTest5>(test, &SegmentationTest6::exec);	


	//GenericSegmentationTest<char, unicpp::v3::GraphemeTokenizer> t1; t1();
	
	reg_function<GenericSegmentationTest2<char, unicpp::v3::GraphemeTokenizer>>(test, &GenericSegmentationTest2<char, unicpp::v3::GraphemeTokenizer>::exec);	
	reg_function<GenericSegmentationTest2<char, unicpp::v3::WordTokenizer>>(test, &GenericSegmentationTest2<char, unicpp::v3::WordTokenizer>::exec);	
	reg_function<GenericSegmentationTest2<char, unicpp::v3::SentenceTokenizer>>(test, &GenericSegmentationTest2<char, unicpp::v3::SentenceTokenizer>::exec);	

	return test;
}


SegmentationTest::SegmentationTest()
{

//	SegmentationTest1 t1; t1();
//	GraphemeSegmentationTest<char> t; t();

//	GenericSegmentationTest<char, unicpp::v3::GraphemeTokenizer> t1; t1();
//	GenericSegmentationTest<char, unicpp::v3::WordTokenizer> t2; t2();
//	GenericSegmentationTest<char, unicpp::v3::SentenceTokenizer> t3; t3();
//	GenericSegmentationTest<char, unicpp::v3::LineTokenizer> t4; t4();

//	GenericBackwardsSegmentationTest<char, unicpp::v3::GraphemeTokenizer> t5; t5();
//	GenericBackwardsSegmentationTest<char, unicpp::v3::WordTokenizer> t6; t6();
//	GenericBackwardsSegmentationTest<char, unicpp::v3::SentenceTokenizer> t7; t7();

//	WordSegmentationTest<char> t; t();
	//WordSegmentationTest<char16_t> t; t();
	//WordSegmentationTest<char32_t> t; t();
	//SegmentationTest5 t2; t2(); 
	//SegmentationTest6<char> t3; t3(); 
	//SegmentationTest6<char32_t> t3; t3(); 

}

SegmentationTest::~SegmentationTest()
{
}

}
