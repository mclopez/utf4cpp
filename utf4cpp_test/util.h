/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

namespace test	{
using namespace std;
	
template <typename Iterator>
void to_hex(const char* var, Iterator begin, Iterator end)	{
	using namespace std;
	if (var)	{
		std::cout << var << " : \n" ;	
	}
	unsigned int mask = 0x0;
	for(size_t i=0;i<sizeof(typename std::iterator_traits<Iterator>::value_type); i++)	{
		mask <<= 8;
		mask |= 0xff;
	}
	for(auto it=begin; it!=end; ++it)	{
		std::cout << "0x" << setfill('0') << setw(sizeof(typename std::iterator_traits<Iterator>::value_type)*2) << hex << (mask&(*it)) << ' ';
	}	
	cout << endl;
}
inline
void to_hex(const char* var, const std::u16string& s)	{
	to_hex(var, s.begin(), s.end());
}

inline
void to_hex(const char* var, const std::wstring& s)	{
	to_hex(var, s.begin(), s.end());
}
	
inline
void to_hex(const char* var, const std::string& s)	{
	to_hex(var, s.begin(), s.end());
}	

template<typename Container>
inline
void to_hex(const char* var, const Container& s)	{
	to_hex(var, s.begin(), s.end());
}

/*
template <typename String1, typename String2>
inline String2 convert(const String1& s1){
	String2 tmp;
	auto uii = unicpp::inserter(tmp, tmp.begin());
	auto it1 = unicpp::make_const_iterator(s1.begin());
	auto it2 = unicpp::make_const_iterator(s1.end());
	copy( it1, it2, uii);
	//std::distance(it1, it2);
	return tmp;
}
*/

/*template <typename String1>
inline void convert(const String1& s1, String1& s2){
	s2 = s1;
}*/


template <typename It1, typename It2>	
bool compare(It1 b1, It1 e1, It2 b2, It2 e2){
	int count = 0;
	while(b1!=e1 && b2!=e2)	{
		++count;
		if(*b1!=*b2)	{
			std::cout << "compare count: "<< count << " " << std::hex << (0xffff&(*b1)) << "   " << std::hex << (0xffff&(*b2)) << std::endl;
			return false;
		}	
		++b1;	
		++b2;	
		//cont++;
	}	
	//std::cout << "compare 3 \n";
	return b2==e2;	
}

template <typename C1, typename C2>	
bool compare(const C1& c1, const C2& c2){
	if (c1.size()!=c2.size())	{
		//std::cout << "compare 0 \n";
		return false;		
	}
	auto it1 = c1.begin();	
	auto it2 = c2.begin();	
	//int cont=0;
	while(it1!=c1.end())	{
		if(*it1!=*it2)	{
			//std::cout << "compare : " << cont << ' ' << std::hex << *it1 << ' ' << std::hex << *it2 << std::endl;
			return false;
		}	
		++it1;	
		++it2;	
		//cont++;
	}	
	//std::cout << "compare 3 \n";
	return true;
}
	

std::string trim(const std::string& s);
std::string rpad(const std::string& s);

std::vector<std::string> split(const std::string& in, const std::string& delim);

	
} //namespace test

#endif // TEST_UTIL_H
