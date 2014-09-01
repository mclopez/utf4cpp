/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef REGEXPTEST_H
#define REGEXPTEST_H

class RegExpTest {

	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void test6();
	void word_segmentation_test();
	void sentence_segmentation_test();
public:
	RegExpTest();
	~RegExpTest();
	void operator()();
};

#endif // REGEXPTEST_H
