/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef TEST1_H
#define TEST1_H

#include <boost/test/unit_test.hpp>

namespace test
{

void test1();
	
class InputOutputTest {

public:
	InputOutputTest();
	~InputOutputTest();

static boost::unit_test::test_suite* test_suite();

};

}

#endif // TEST1_H
