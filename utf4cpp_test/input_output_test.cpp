/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "input_output_test.h"


#include "util.h"
#include "test.h"
#include "test_data.h"
#include <utf4cpp/unicpp.h>

//#include <iostream>


#include <exception>
#include <iostream>
#include <iterator>

namespace test
{

InputOutputTest::InputOutputTest(){

}

InputOutputTest::~InputOutputTest()
{
}




template <typename Temp, typename T1>
struct TemplateTypeInfo1	{
	
};

template<typename T> struct TypeInfoAux	;

/*template<template T0< typename > > struct TypeInfoAux< T0 >	{ 
//	static const std::string name(){return "<" + TypeInfo<T1>::name() + ">";}
};*/

template<typename T> 
struct StreamInputTest	{
	static void exec()	{
		StreamInputTest<T> t; t();
	}
	void operator()()	{
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		std::basic_istringstream<T> ssinput(input);

		std::istream_iterator<T,T> ssin_it(ssinput);
//		std::istream_iterator<T,T> ssin_it_e;

//		unicpp::input_iterator<std::istream_iterator<T,T>> ii(ssin_it);
//		unicpp::input_iterator<std::istream_iterator<T,T>> ii_end(ssin_it_e);
//		unicpp::input_iterator<std::istream_iterator<T,T>> ii_end(std::istream_iterator<T,T>());
		auto ii = unicpp::make_input_iterator(ssin_it);
		auto ii_end = unicpp::make_input_iterator<std::istream_iterator<T,T>>();
		
		std::basic_string<T> output;
		std::copy(ii, ii_end, unicpp::back_inserter(output));
		BOOST_CHECK(input==output);
/*
			if (input!=output)	
			{
				unicpp::to_hex("input", input);
				unicpp::to_hex("output", output);
				std::cout << "\nERROR "<<  std::endl; 
				return;
			}
*/
	}
};

template<typename T> 
struct StreamBufInputTest	{
	static void exec()	{
		StreamBufInputTest<T> t; t();
	}
	void operator()()	{
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		std::basic_stringbuf<T> sb(input);

		std::istreambuf_iterator<T> ssin_it(&sb);
//		std::istream_iterator<T,T> ssin_it_e;

//		unicpp::input_iterator<std::istream_iterator<T,T>> ii(ssin_it);
//		unicpp::input_iterator<std::istream_iterator<T,T>> ii_end(ssin_it_e);
//		unicpp::input_iterator<std::istream_iterator<T,T>> ii_end(std::istream_iterator<T,T>());
		auto ii = unicpp::make_input_iterator(ssin_it);
		auto ii_end = unicpp::make_input_iterator<std::istreambuf_iterator<T>>();
		
		std::basic_string<T> output;
		std::copy(ii, ii_end, unicpp::back_inserter(output));
		BOOST_CHECK(input==output);
	}
};


template<typename T> 
struct Insert	{

	static void exec()	{
		Insert<T> t; 
		t();
	}
	void operator()()	{
		std::u32string ref = create_container<std::u32string, char32_t>();
		char32_t value = ref[5];
		auto it_ref_f = std::find(ref.begin(),ref.end(), value);
		if (it_ref_f ==ref.end())	{
			std::cout << "\nERROR (1) cant find " << value <<  std::endl; 
			return;						
		}
		auto it_ins_ref = std::inserter(ref, it_ref_f);
		std::copy(ref.begin(), ref.end(), it_ins_ref);
		
		// doing the same with T
		typedef std::basic_string<T> Cont;
		Cont input(Data<T>::get(), Data<T>::size());
		auto it1 = unicpp::make_const_iterator(input.begin());
		auto it2 = unicpp::make_const_iterator(input.end());
	
		Cont output = input;
		
		auto b = unicpp::make_const_iterator(output.begin());
		auto e = unicpp::make_const_iterator(output.end());
		auto it_f = std::find(b, e, value);
		if (it_f == e)	{
			std::cout << "\nERROR cant find " << value <<  std::endl; 
			return;			
		}
		auto it_ins = unicpp::inserter(output, it_f.base()); 
		std::copy(it1, it2, it_ins);

		// check with reference
		auto ref_b = ref.begin();
		auto ref_e = ref.end();
		auto output_b = unicpp::make_const_iterator(output.begin());
		auto output_e = unicpp::make_const_iterator(output.end());
	
		BOOST_CHECK(compare(ref_b, ref_e, output_b, output_e));
		if (!compare(ref_b, ref_e, output_b, output_e))	
		{
			to_hex("ref", ref_b, ref_e);
			to_hex("output", output_b, output_e);
			std::cout << "\nERROR "<<  std::endl; 
			return;
		}

	}
};


template<typename T1, typename T2> 
struct BackInsertTest	{

	static void exec()	{
		BackInsertTest<T1, T2> t; t();
	}
	
	void operator()()	{
//		std::cout << "BackInsertTest<" << Data<T1>::name()<< ", " << Data<T2>::name() << ">()"; 
	
		typedef std::basic_string<T1> Cont1;
		typedef std::basic_string<T2> Cont2;
		Cont1 input(Data<T1>::get(), Data<T1>::size());

		auto it1 = unicpp::make_const_iterator(input.begin());
		auto it2 = unicpp::make_const_iterator(input.end());

		Cont2 output; 
		//std::back_insert_iterator<T2> it(output);

		//typedef unicpp::output_iterator<std::back_insert_iterator<T2>, typename T2::value_type > output_iter;
		//output_iter inserter(it);
		auto it_ins = unicpp::back_inserter(output);
		copy(it1, it2, it_ins);
		
//		unicpp::to_hex("input", input);
//		unicpp::to_hex("output", output);
		
		BOOST_CHECK(compare(create_container<std::basic_string<T2>>(),output));
//		BOOST_CHECK( Data<T2>::get()==output);
/*		if (!(unicpp::compare(Data<std::basic_string<T2>>::get(),output)))	{
			unicpp::to_hex("Data<T2>::get()", Data<std::basic_string<T2>>::get());
			unicpp::to_hex("output", output);
			std::cout << "\nERROR "<<  std::endl; 
			return;
		}*/
//		std::cout << " ok"<<  std::endl; 

	}
};


template<typename T1, typename T2> 
struct FrontInsertTest	{
	
	static void exec()	{
		FrontInsertTest<T1, T2> t; t();
	}
	void operator()()	{
		std::basic_string<T1> input(Data<T1>::get(),Data<T1>::size());
		auto it1 = unicpp::make_const_iterator(input.begin());
		auto it2 = unicpp::make_const_iterator(input.end());

		typedef std::list<T2> Cont;
		Cont output; 
		auto it_ins = unicpp::front_inserter(output);
		copy(it1, it2, it_ins);		
		BOOST_CHECK(compare(create_container_inv<std::basic_string<T2>>(), output));
	}
};


template<typename T1, typename T2> 
struct StreamBufTest	{
	
	static void exec()	{
		StreamBufTest<T1, T2> t; t();
	}
	void operator()()	{
	
		std::basic_string<T1> input(Data<T1>::get(), Data<T1>::size());
		auto it1 = unicpp::make_const_iterator(input.begin());
		auto it2 = unicpp::make_const_iterator(input.end());


		std::basic_string<T2> aux;
		std::basic_stringbuf<T2> sb(aux);
		
		auto it_ins = unicpp::streambuf_inserter(&sb);
		
		copy(it1, it2, it_ins);
//		size_t output_length = 0;
		std::basic_string<T2> sout = sb.str();
		BOOST_CHECK(compare(create_container<std::basic_string<T2>>(),sout));
/*		if (!unicpp::compare(Data<T2>::get(),sout))
		{
			unicpp::to_hex("Data<T2>::get()",	Data<T2>::get());
			
			unicpp::to_hex("output", sout);
			std::cout << "ERROR "<<  std::endl; 
			return;
		}*/
	}
};


template<typename T1, typename T2> 
struct StreamTest	{
	
	static void exec()	{
		StreamTest<T1, T2> t; t();
	}
	void operator()()	{
	
		std::basic_string<T1> input = create_container<std::basic_string<T1>>();
		auto it1 = unicpp::make_const_iterator(input.begin());
		auto it2 = unicpp::make_const_iterator(input.end());



		std::basic_string<T2> aux;
		std::basic_stringstream<T2> sb(aux);
		auto it_ins = unicpp::stream_inserter(sb);
		
		copy(it1, it2, it_ins);
//		size_t output_length = 0;
		std::basic_string<T2> sout = sb.str();
		BOOST_CHECK(compare(create_container<std::basic_string<T2>>(),sout));
/*		if (!unicpp::compare(Data<T2>::get(),sout))
		{
			unicpp::to_hex("Data<T2>::get()",	Data<T2>::get());
			
			unicpp::to_hex("output", sout);
			std::cout << "ERROR "<<  std::endl; 
			return;
		}*/

	}
};



template<typename T1, typename T2> 
struct RowInsertTest	{
	
	static void exec()	{
		RowInsertTest<T1, T2> t; t();
	}
	void operator()()	{
		const T1* input = Data<T1>::get();
		size_t input_length = Data<T1>::size();
		
		auto it1 = unicpp::make_const_iterator(input);
		auto it2 = unicpp::make_const_iterator(input+ input_length);

		T2* output = new T2[input_length*4]; 
		for(T2* it = output;it!=output+input_length*4;++it )	{
			*it=0;
		}

		auto it_ins = unicpp::inserter(output);
		copy(it1, it2, it_ins);
		size_t output_length = 0;
		T2* aux = output;
		while (*aux!=0)	{
			++output_length;
			++aux;
		}
		
		BOOST_CHECK(compare(Data<T2>::get(),Data<T2>::get()+Data<T2>::size(),output,output+output_length));
		
/*		if (!unicpp::compare(
				Data<T2>::get(),
				Data<T2>::get()+Data<T2>::size(),
				output,output+output_length))
		{
			unicpp::to_hex("Data<T2>::get()",	Data<T2>::get(), Data<T2>::get()+Data<T2>::size());
			
			unicpp::to_hex("output", output, output+output_length);
			std::cout << "\nERROR "<<  std::endl; 
			return;
		}
*/

	}
};




boost::unit_test::test_suite* InputOutputTest::test_suite()	{
	boost::unit_test::test_suite* test = BOOST_TEST_SUITE("test1.cpp");
	// input
//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, StreamInputTest>::reg(test);
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, StreamBufInputTest>::reg(test);
	
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, Insert>::reg(test);
	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, BackInsertTest>::reg(test);
	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, FrontInsertTest>::reg(test);
	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, RowInsertTest>::reg(test);
	
	// output 
	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, StreamTest>::reg(test);
	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, StreamBufTest>::reg(test);


	return test;
}

}
