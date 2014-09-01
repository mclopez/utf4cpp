/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef TESTUTF_H
#define TESTUTF_H

#include <string>
#include <boost/test/unit_test.hpp>

namespace test
{
//bool insert_test();
//void standard_string_back_insert();	
void istream_test();
	
class TestUtf {

	
public:

static boost::unit_test::test_suite* test_suite();


};


}

#endif // TESTUTF_H
