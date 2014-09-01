/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "util.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <string>

using namespace std;

std::string extract_file_name(std::string filename)	{
	size_t pos = filename.rfind('/');
	if (pos!=std::string::npos)	{
		return filename.substr(pos+1);
	} else	{
		return filename;
	}
}

std::string get_namespace_begin(std::string _namespace)	{
	stringstream result;
	vector<string> tokens;
	split(_namespace, '/', tokens);
	for(auto it=tokens.begin();it!=tokens.end();++it)	{
		result<<"namespace " << *it << " { ";
		
	}
	return result.str();
}
std::string get_namespace_end(std::string _namespace)	{
	stringstream result;
	vector<string> tokens;
	split(_namespace, '/', tokens);
	for(auto it=tokens.begin();it!=tokens.end();++it)	{
		result<< " } ";
		
	}
	result<< "// namespace " ;
	for(auto it=tokens.begin();it!=tokens.end();++it)	{
		result<< "::" << *it ;
		
	}
	return result.str();	
}
std::string get_guard(std::string _namespace)	{
	string result;
	for(auto it=_namespace.begin();it!=_namespace.end();it++)	{
		if (*it=='/')	{
			result.push_back('_');
		}else	{
			result.push_back(std::toupper(*it));
		}
	}
	return result;
}


std::string trim(const std::string& s)	{
	std::string r;
	for(std::string::const_iterator it = s.begin();it!=s.end();it++)	{
		if (!std::isspace(*it))	{
			r.push_back(*it);
		}
	}
	return r;
}

std::vector<std::string> split(const std::string& in, const std::string& delim)	{
//	std::string::const_iterator it = in.begin();
	std::vector<std::string> result;
	size_t paux = 0;
	while (paux!=std::string::npos)	{
		size_t paux2 = in.find(delim, paux);
		if (paux2!=std::string::npos)	{
			std::string s = in.substr(paux, paux2);
			if (!s.empty())	{
				result.push_back(s);				
			}
		}else	{
			std::string s = in.substr(paux, paux2);
			if (!s.empty())	{
				result.push_back(s);				
			}
			break;
		}
		paux = paux2 + delim.size();
	}
	return result;
}

template <typename String>
void split(const String& in, typename String::value_type delim, std::vector<String>& result)	{
	basic_stringstream<typename String::value_type>  ss(in);
	while(ss)	{
		String s;
		std::getline(ss, s, delim);
		if (!s.empty())	{
			result.push_back(s);
		}
	}
}

//string Other("Other");











