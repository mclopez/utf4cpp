/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


//bash LD_LIBRARY_PATH=../Unicode4Cpp/Debug:$LD_LIBRARY_PATH  ./$(ProjectName)

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
//#define BOOST_TEST_MAIN

#include <ios>
#include <boost/test/execution_monitor.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/framework.hpp>
#include <boost/test/unit_test_log.hpp>
#include <iostream>

#include <locale>
//#include <codecvt.h>

#include "test_utf.h"
#include "input_output_test.h"
#include "const_iterator_test.h"
#include "segmentation_test.h"
#include "cdb_test.h"
#include "utf4cpp/traits.h"

using boost::unit_test::test_suite;
using namespace std;

bool unit_test_func_all()	{
	cout << "unit_test_func_all \n";
	boost::unit_test::test_suite* test = new boost::unit_test::test_suite( "test suite" ); 

	test->add(test::cdb_test::test_suite());

	//test->add(test::TestUtf::test_suite());
	test->add(test::InputOutputTest::test_suite());
	test->add(test::ConstIteratorTest::test_suite());
//	test->add(test::iconv::test_suite());
	test->add(test::SegmentationTest::test_suite());

    ::boost::unit_test::framework::master_test_suite().add( test );
	return true;
}

bool unit_test_func_temp()	{
	cout << "unit_test_func_temp \n";
	boost::unit_test::test_suite* test = new boost::unit_test::test_suite( "temp test suite" ); 

	test->add(test::SegmentationTest::test_suite());

    ::boost::unit_test::framework::master_test_suite().add( test );
	return true;
}

/*
test_suite* my_init_unit_test_func( int, char* [] )	{
	cout << "my_init_unit_test_func 2\n";
	
}
*/
/*
struct Date {
	void extract(tm& tm_){
		tm_.tm_yday = 1;
		tm_.tm_year = 1900;
	}
};

template <class charT, class traits>
basic_ostream<charT,traits>& operator<< (basic_ostream<charT,traits>& s, Date d) {
	typename basic_ostream<charT,traits>::sentry cerberos(s);
	if (cerberos) {
		ios_base::iostate err = ios_base::goodbit;
		//ios_base iob;
		tm tmbuf; 
		d.extract(tmbuf);
		std::ostreambuf_iterator<char, std::char_traits<char> > it1(s);
		std::ostreambuf_iterator<char, std::char_traits<char> > it2();
		locale loc;
	//	use_facet< time_put<charT, ostreambuf_iterator<charT,traits>  > >(s.getloc()).put(s,s,s.fill(), err, &tmbuf,’x’);
		//const std::locale::facet& f 
		const time_put<charT, ostreambuf_iterator<charT, traits> >& f   = 
			use_facet< time_put<charT, ostreambuf_iterator<charT, traits> > >(s.getloc()) ;
		
		f.put(it1, s, 'j', //s.fill(), 
			//err, 
			&tmbuf,'x', 'y');
 		s.setstate(err);
		// might throw
	}
	return s;
}
*/


void do_table()	{
	cout << "static const int[] table={";
	
	for(int i=0;i<256;i++)	{
		if (i%16==0)
		{
			cout << endl;
		}
		cout <<  unicpp::utf_iterator_char_traits<char>::size((char)i);
//		cout <<  "-" << hex << (0xff&i);
		cout << ", " ;
	}
	cout << "};" << endl;;
}

int
main( int argc , char ** args)
{ 
/*	::boost::unit_test::unit_test_log.set_threshold_level(
			//boost::unit_test::log_level::log_all_errors
			//boost::unit_test::log_level::log_successful_tests
			//boost::unit_test::log_level::log_messages
			
			boost::unit_test::log_level::invalid_log_level        
//			boost::unit_test::log_level::log_successful_tests
//			boost::unit_test::log_level::log_test_units          
//			boost::unit_test::log_level::log_messages            
//			boost::unit_test::log_level::log_warnings            
//			boost::unit_test::log_level::log_all_errors           
//			boost::unit_test::log_level::log_cpp_exception_errors 
//			boost::unit_test::log_level::log_system_errors        
//			boost::unit_test::log_level::log_fatal_errors         
//			boost::unit_test::log_level::log_nothing              
			);
*/
//	::boost::unit_test::framework::init(&unit_test_func_all, argc, args);
	::boost::unit_test::framework::init(&unit_test_func_temp, argc, args);
	::boost::unit_test::framework::run();

//	test::SegmentationTest t;
//	test::RegExpTest t;
    return 0;
}
