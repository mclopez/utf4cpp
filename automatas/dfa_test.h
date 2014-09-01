
/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef DFATEST_H
#define DFATEST_H

class DfaTest {

public:
	DfaTest();
	~DfaTest();
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	
	void operator()();
};

#endif // DFATEST_H
