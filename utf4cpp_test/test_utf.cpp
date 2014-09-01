/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "test_utf.h"

#include <iterator>
#include <iostream>
#include <iomanip>

#include <vector>


#include <boost/test/unit_test.hpp>

#include "util.h"

#include <utf4cpp/unicpp.h>
#include "test_data.h"


namespace test
{

	using namespace std;



/*
void insert_test() 	{
//return;
	cout << "\ninsert_test \n";

	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;


	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	

	string s8test; 
	auto s8_inserter = unicpp::inserter(s8test, s8test.end());
	copy(it1, it2, s8_inserter);
	
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	
	BOOST_CHECK( s8==s8test);

	u16string s16test; 
	auto s16_inserter = unicpp::inserter(s16test, s16test.end());
	copy(it1, it2, s16_inserter);
	
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16test", s16test);
	
	BOOST_CHECK( s16==s16test);

}


void  standard_string_back_insert ()	{
//return;
	Object obj;
	cout << "p1" << endl;
	*obj=obj;
	cout << "p2" << endl;
	*obj++=obj;
	cout << "p3" << endl;
	*++obj=obj;
	cout << "p4" << endl;
	obj++;
	cout << "p5" << endl;
	*obj++=++obj;

	cout << "\nstandard_string_back_insert \n";
	string s8test; 
	auto it = inserter(s8test, s8test.end());
	for(char i=0;i<100;i++)	{
		*it=i;
	}
	//unicpp::iterator<string::iterator> s8_it(s8.back_inbegin());
	
}



void insert_test2() 	{
//return;
	cout << "\ninsert_test2\n";

	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;
	
	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	
	string s8test; 
	auto s8_inserter = unicpp::inserter(s8test, s8test.end());
	copy(it1, it2, s8_inserter);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	BOOST_CHECK( s8==s8test );

	u16string s16test; 
	auto s16_inserter = unicpp::inserter(s16test, s16test.end());
	copy(it1, it2, s16_inserter);
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16test", s16test);
	BOOST_CHECK( s16==s16test );
}



void insert_test3()	{
//return;
	cout << "\ninsert_test3 \n";

	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	const char32_t value = s32[1];
	
	u32string s32_test = s32;
	u32string::iterator it32 = std::find(s32_test.begin(), s32_test.end(), value);
	if (it32!=s32_test.end())	{
		auto ii = inserter(s32_test, it32);
		copy(s32.begin(), s32.end(), ii);
	}
	unicpp::to_hex("s32", s32);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s32_test", s32_test);

	string s8_test = s8;
	auto it8_begin = unicpp::make_const_iterator(s8_test.begin());
//	cout << "*it8_begin: " << *it8_begin << "\n";
	
	auto it8_end   = unicpp::make_const_iterator(s8_test.end());
	
	auto it8 = std::find(it8_begin, it8_end, value);
	if (it8!=it8_end)	{
		cout << "\ninsert_test3 encontrado " << value << "\n";
		auto ii = unicpp::inserter(s8_test, it8.base());
		copy(unicpp::make_const_iterator(s8.begin()), unicpp::make_const_iterator(s8.end()), ii);
	} else	{
		cout << "\ninsert_test3 no encontrado " << value << "\n";		
	}
	
	unicpp::to_hex("s8test", s8_test);
	
	BOOST_CHECK( unicpp::compare(
		unicpp::make_const_iterator(s8_test.begin()),
		unicpp::make_const_iterator(s8_test.end()), 
		s32_test.begin(), s32_test.end()) );

}


void back_insert_test()	{
//return;
	cout << "\nback_insert_test \n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	
	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	
	

	string s8test; 
	auto s8_inserter = unicpp::back_inserter(s8test);
	copy(it1, it2, s8_inserter);
	
	
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	
	BOOST_CHECK( s8==s8test );

	u16string s16test; 
	auto s16_inserter = unicpp::back_inserter(s16test);
	copy(it1, it2, s16_inserter);
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16test", s16test);
	
	BOOST_CHECK( s16==s16test );
}

void front_insert_test()	{
//return;
	cout << "\nfront_insert_test \n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	
	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	
	list<char32_t> s32_inv;
	copy(it1, it2, front_inserter(s32_inv));
	string s8_inv;
	copy(s32_inv.begin(), s32_inv.end(), unicpp::back_inserter(s8_inv));
	u16string s16_inv;
	copy(s32_inv.begin(), s32_inv.end(), unicpp::back_inserter(s16_inv));

	list<char> s8test; 
	auto s8_inserter = unicpp::front_inserter(s8test);
	copy(it1, it2, s8_inserter);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8_inv", s8_inv);
	unicpp::to_hex("s8test", s8test);
	
	BOOST_CHECK( unicpp::compare(s8_inv, s8test) );

	list<char16_t> s16test; 
	auto s16_inserter = unicpp::front_inserter(s16test);
	copy(it1, it2, s16_inserter);
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16_inv", s16_inv);
	unicpp::to_hex("s16test", s16test);
	
	BOOST_CHECK( unicpp::compare(s16_inv, s16test) );
}


void back_insert_test2()	{
//return;
	cout << "\nback_insert_test2 \n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	
	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	
	

	string s8test; 
	auto s8_inserter = unicpp::back_inserter(s8test);
	copy(it1, it2, s8_inserter);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	
	BOOST_CHECK( s8==s8test );

	u16string s16test; 
	auto s16_inserter = unicpp::back_inserter(s16test);
	copy(it1, it2, s16_inserter);
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16test", s16test);
	
	BOOST_CHECK( s16==s16test );
}


void test7()	{
//return;
	cout << "\ntest7 \n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;


	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());

	string s8test;//(20, 'a'); 
	auto s8_inserter = unicpp::inserter(s8test, s8test.begin());
	copy(it1, it2, s8_inserter);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	BOOST_CHECK( s8==s8test );
	
	
}

void istream_test()	{
//return;
	cout << "\nistream_test\n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	string xxx = s8;
	basic_istringstream<char> x;
	istringstream is8(xxx); //,  ios_base::in|ios_base::binary);
//	istream_iterator<char> si_begin(is8);
//	istream_iterator<char> si_end;
	
	{
//	using namespace unicpp::v1;

//	auto is8_it1 = unicpp::make_istream_iterator(is8);
//	auto is8_it2 = unicpp::make_istream_iterator<char>();
	unicpp::input_iterator<std::istream_iterator<char>> is8_it1(is8); 
	unicpp::input_iterator<std::istream_iterator<char>> is8_it2; 
//	unicpp::istream_cp_iterator<char> is8_it1(is8);
//	unicpp::istream_cp_iterator<char>is8_it2;


//	std::cout << "0x" << setfill('0') << setw(6) << hex << (0xffffff&(*is8_it1)) << ' ' << endl;
//	++is8_it1;
	//std::cout << "0x" << setfill('0') << setw(6) << hex << (0xffffff&(*is8_it1)) << ' ' << endl;
//	return 	;
	
	for(auto it =is8_it1; it!=is8_it2; ++it )	{
		//cout << *it << endl;
		//is8.clear();
		std::cout << "0x" << setfill('0') << setw(6) << hex << (0xffffff&(*it)) << ' ' << endl;
	}

	}
	std::cout << "end" << endl;
	return;

	
	string s8test; 
//	s8test.reserve(100);
	auto s8_inserter = unicpp::back_inserter(s8test);
//	copy(is8_it1, is8_it2, s8_inserter);
	unicpp::to_hex("s8", s8);
	unicpp::to_hex("s8test", s8test);
	
	BOOST_CHECK( s8==s8test );

	cout << "s16.size(): " << s16.size() << '\n';
	
	basic_istringstream<wchar_t> is16(ws16);
	istream_iterator<wchar_t, wchar_t> si16_begin(is16);
//	return;
	istream_iterator<wchar_t, wchar_t> si16_end;
*/	
/*	auto is16_it1 = unicpp::make_istream_iterator(si16_begin);
	auto is16_it2 = unicpp::make_istream_iterator(si16_end);

	
	wstring s16test; 
//	s8test.reserve(100);
	auto s16_inserter = unicpp::back_inserter(s16test);
	copy(is16_it1, is16_it2, s16_inserter);
	unicpp::to_hex("s16", s16);
	unicpp::to_hex("s16test", s16test);
	
	BOOST_CHECK( ws16==s16test );
*/

/*
}


*/

void ostream_test( )	{
//return;
	cout << "\nostream_test\n";
	const u32string s32 = TestData::get().s32;
	const u16string s16 = TestData::get().s16;
//	const wstring ws16 = TestData::get().ws16;
	const string s8 = TestData::get().s8;

	
	string sout;
	ostringstream osout(sout);
	ostream_iterator< ostringstream::char_type  > osi(osout);
	
//	std::insert_iterator it;
	
	auto it1 = unicpp::make_const_iterator(s32.begin());
	auto it2 = unicpp::make_const_iterator(s32.end());
	
	string s8test; 
//	ostream_iterator<char> 	x;
	ostringstream os8test(s8test);
	auto s8_inserter = unicpp::stream_inserter(os8test);
	//unicpp::output_iterator<ostream_iterator<char>, char> s8_inserter(os8test);
	
	
	copy(it1, it2, s8_inserter);
	
	//os8test.flush();
	s8test = os8test.str();

	to_hex("s8", s8);
	to_hex("s8test", s8test);
	BOOST_CHECK( s8==s8test );

	cout << "sizeof(wchar_t): " << sizeof(wchar_t) << endl;
	cout << "sizeof(char16_t):" << sizeof(char16_t) << endl;
	u16string s16test; 
	
	basic_ostringstream<char16_t> os16test(s16test);
	
//	auto s16_inserter = unicpp::stream_inserter(os16test);
//	std::ostream_iterator<char16_t, char16_t> oit16 = std::ostream_iterator<char16_t, char16_t>(os16test);
//	unicpp::output_iterator<std::ostream_iterator<char16_t, char16_t>, char16_t> 	s16_inserter(os16test);
	auto s16_inserter = unicpp::stream_inserter(os16test);
	
	
	
//	char32_t i = 1;
//	*s16_ins = 	i;
	
	copy(it1, it2, s16_inserter);
	
	os16test.flush();
	s16test = os16test.str();
	
	to_hex("s16", s16);
	to_hex("s16test", s16test);
	BOOST_CHECK( s16==s16test );
	
}



boost::unit_test::test_suite* TestUtf::test_suite()	{
	//boost::unit_test::test_suite* test = new boost::unit_test::test_suite( "test suite" );
	boost::unit_test::test_suite* test = BOOST_TEST_SUITE("test suite");
/*	test->add( BOOST_TEST_CASE( &insert_test) );
	test->add( BOOST_TEST_CASE( &insert_test2));
	test->add( BOOST_TEST_CASE( &insert_test3));
	test->add( BOOST_TEST_CASE( &back_insert_test));
	test->add( BOOST_TEST_CASE( &front_insert_test));
	test->add( BOOST_TEST_CASE( &back_insert_test2));
	test->add( BOOST_TEST_CASE( &test7));*/
//	test->add( BOOST_TEST_CASE( &istream_test));
	test->add( BOOST_TEST_CASE( &ostream_test));
	
	return test;
}




}

