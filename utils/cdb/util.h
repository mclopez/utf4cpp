/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef GRAPHEMEBREAKUTIL_H
#define GRAPHEMEBREAKUTIL_H

#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

template <class T>
class MySet	{
	typedef std::vector<T> List;
	List values;
public:
	~MySet()	{
//		for(auto it=values.begin();it!=values.end();++it)	{
//			delete *it;
//		}
	}
	
/*	size_t get(const T& v)	{
		for(auto it=values.begin();it!=values.end();++it)	{
			if (**it==v)	{
				return (*it);
			}
		}
		return insert("Other");
	}
*/
		
	 size_t get_index(const T& v)	{
		for(size_t i=0;i!=values.size();++i)	{
			if (values[i]==v)	{
				return i;
			}
		}
		return insert("Other");
	}
	const T& get_value(size_t i)	{
		return values[i];
	}

	size_t insert(const T& v)	{
		for(size_t i=0;i!=values.size();++i)	{
			if (values[i]==v)	{
				return i;
			}
		}
//		std::string* s = new std::string(v);
		values.push_back(v);
		return values.size()-1;
	}
	
	size_t size()	{
		return values.size();
	}
	typename List::iterator begin()	{
		return values.begin();
	}
	typename List::iterator end()	{
		return values.end();
	}
//	values() { return values;}
};


struct RangePropertyValue	{
	char32_t begin;
	char32_t end;
	size_t value;
};

inline
bool operator<(const RangePropertyValue& p1, const RangePropertyValue& p2)	{
	return p1.begin < p2.begin;
}

inline
bool operator==(const RangePropertyValue& p1, const RangePropertyValue& p2)	{
		return p1.begin <= p2.begin && p1.end >= p2.begin && p1.end >= p2.end;
}


inline
char32_t to_codepoint(const std::string& str)	{
	int ch;
	std::stringstream ss(str);
	ss >> std::hex >> ch;
	return ch;
}


template<typename T>
struct Block	{
	
	Block(size_t size):size(size),buffer(new T[size]){
	}
	Block(const Block& b):size(b.size),buffer(new T[size]){
		for(size_t i=0;i<size;i++)	{
			buffer[i]=b.buffer[i];
		}
	}
	void operator=(const Block& b)	{
		size = b.size;
		buffer.reset(new T[size]);
		for(size_t i=0;i<min(size, b.size);++i)	{
			buffer[i]=b.buffer[i];
		}
		
	}	

	T& operator[](size_t p)	{
		return buffer[p];
	}
	
	size_t size;
	std::unique_ptr<T[]> buffer;
	
};

template<typename T>
bool operator==(const Block<T>& x, const Block<T>& y)	{
	if (x.size!=y.size)	{
		return false;
	}else	{
		for(size_t i=0;i<x.size;++i)	{
			if (x.buffer[i] != y.buffer[i])	{
				return false;
			}
		}
		return true;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Block<T>& b)	{
	for(size_t i=0;i< b.size;i++)	{
		const T v = b.buffer[i];
		os << v  << " ";
		if (i%16==0)	{
			os << std::endl;
		}
	}
	os << std::endl;
	return os;
}

/*
class GraphemeBreakUtil {

	
public:
	
	void parse();
	void generate_common();
	void generate_binary();
	void generate_table(int n1_bits, int n2_bits);
	void do_files(std::vector<Block<const std::string*>>& n1_blocks,	Block<char>& n2_block, size_t n2_length);

	void generate_table2(int n1_bits, int n2_bits);
	
	const std::string* get_value(char32_t cp);
};
*/

std::string extract_file_name(std::string filename);
std::string get_namespace_begin(std::string _namespace);
std::string get_namespace_end(std::string _namespace);
std::string get_guard(std::string _namespace);

std::string trim(const std::string& s);
std::vector<std::string> split(const std::string& in, const std::string& delim);

template <typename String>
void split(const String& in, typename String::value_type delim, std::vector<String>& result);


#endif // GRAPHEMEBREAKUTIL_H
