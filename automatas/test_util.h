/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef TESTUTIL_H
#define TESTUTIL_H

#include <cassert>

#define CHECK( DFA, STR, RESULT) \
	assert((check(DFA, STR)== RESULT));
	//std::cout << #DFA << ' ' << STR << ' ' << std:: boolalpha  << ( (check(DFA, STR)== RESULT)?"ok":"ko") << std::endl;	

class TestUtil {

public:
	TestUtil();
	~TestUtil();

};

#endif // TESTUTIL_H
