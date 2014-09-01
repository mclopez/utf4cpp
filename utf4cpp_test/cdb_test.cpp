/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <iostream>
#include <boost/test/unit_test.hpp>

#include "cdb_test.h"

#include <utf4cpp/unicpp.h>
//#include <utf4cpp/segmentation.h>
#include <utf4cpp/cdb/grapheme_break.h>
#include <utf4cpp/cdb/grapheme_break_binary_auto.h>
#include <utf4cpp/cdb/grapheme_break_binary_auto_impl.h>
#include <utf4cpp/cdb/grapheme_break_table_2levels_auto.h>
#include <utf4cpp/cdb/grapheme_break_table_2levels_auto_impl.h>
#include <utf4cpp/cdb/grapheme_break_table_3levels_auto.h>
#include <utf4cpp/cdb/grapheme_break_table_3levels_auto_impl.h>

#include "test.h"

//#include "util.h"


namespace test {

cdb_test::cdb_test()
{
}

cdb_test::~cdb_test()
{
}

void cdb_test::cdb_values_test()	{

	using namespace unicpp::cdb::graphemebreak;

	for(char32_t cp=0;cp<=0x10ffff;++cp)	{
		int32_t v1 = (int32_t )binary::get_value(cp); 
		int32_t v2 = (int32_t )table_2levels::get_value(cp);
		//if (cp==100) v2 = 100; 
		BOOST_CHECK_MESSAGE( v1==v2, "for codepoint " << hex << "0x" << cp << dec << " got " << v1 << " and " <<  v2 );

		int32_t v3 = (int32_t)table_3levels::get_value(cp);
		BOOST_CHECK_MESSAGE( v1==v3, "for codepoint " << hex << "0x" << cp << dec << " got " << v1 << " and " <<  v3 );
	}
}


void cdb_test::performance_test()	{ 
	std::cout << "PerformanceTest::exec() (cdb_test.cpp)" << std::endl;

	
	using namespace unicpp::cdb::graphemebreak;

 
 
	chrono::high_resolution_clock clock;
	chrono::high_resolution_clock::time_point t1 = clock.now();
	for(char32_t cp=0;cp<=0x10ffff;++cp)	{
		binary::get_value(cp);
	}
	chrono::high_resolution_clock::time_point  t2 = clock.now();
	cout << "PerformanceTest::exec() GraphemeBinary::get_value binary " <<  t2.time_since_epoch().count()-t1.time_since_epoch().count() << " secs " << endl;

	chrono::high_resolution_clock::time_point t3 = clock.now();
	for(char32_t cp=0;cp<=0x10ffff;++cp)	{
		table_2levels::get_value(cp);
	}
	chrono::high_resolution_clock::time_point  t4 = clock.now();
	cout << "PerformanceTest::exec() GraphemeTable::get_value table 2 levels " <<  t4.time_since_epoch().count()-t3.time_since_epoch().count() << " secs " <<endl;

	chrono::high_resolution_clock::time_point t5 = clock.now();
	for(char32_t cp=0;cp<=0x10ffff;++cp)	{
		table_3levels::get_value(cp);
	}
	chrono::high_resolution_clock::time_point  t6 = clock.now();
	cout << "PerformanceTest::exec() GraphemeTable2::get_value table 3 levels " <<  t6.time_since_epoch().count()-t5.time_since_epoch().count() << " secs " <<endl;

	//return 0;
	
}
	


boost::unit_test::test_suite* cdb_test::test_suite()	{
	boost::unit_test::test_suite* test = BOOST_TEST_SUITE("cdb_test.cpp");

	test->add( BOOST_TEST_CASE(cdb_test::cdb_values_test)); 
	//test->add( BOOST_TEST_CASE(cdb_test::performance_test)); 
	//reg_function<PerformanceTest>(test, &PerformanceTest::exec);	
	
	return test;
}


} // namespace
