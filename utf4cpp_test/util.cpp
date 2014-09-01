/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "util.h"

#include <string>
#include <vector>

namespace test	{
	
std::string trim(const std::string& s)	{
	std::string r;
	for(std::string::const_iterator it = s.begin();it!=s.end();it++)	{
		if (!std::isspace(*it))	{
			r.push_back(*it);
		}
	}
	return r;
}

std::string rpad(const std::string& s)	{
	std::string r;
	int count=0;
	for(std::string::const_reverse_iterator it = s.rbegin();it!=s.rend();it++)	{
		if (std::isspace(*it))	{
			count++;
		}else 	{
			break;
		}
	}
//	cout << s << "' count: "<< count << endl;
	return s.substr(0, s.size()-count);
}

std::vector<std::string> split(const std::string& in, const std::string& delim)	{
	std::string::const_iterator it = in.begin();
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


}
