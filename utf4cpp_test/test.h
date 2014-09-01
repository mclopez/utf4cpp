/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <iostream>
#include "time.h"

#include <cxxabi.h>
#include <chrono>

using namespace std;

template<typename T>
std::string name()	{
  int     status;
  return abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
	
}

/* 
struct Context	{
	std::ostream& log()	{
		return cout;
	}
	std::ostream& error()	{
		return cout;
	}
};
*/
template <typename _Test, int Cont> 
struct TestRepetition	{
public:
	typedef _Test Type;
//	TestRepetition(Type t):t(t), rep(rep){}

	void operator ()()	{
		for(int i=0;i<Cont;++i)	{
			t();
		}
	}	

	Type t;
	int rep;
}; 

template <typename T, int c> 
std::ostream& operator << (std::ostream& cout, TestRepetition<T, c> t)
{
	cout << "repetition:" << t.rep;
    return cout;
}

/*
template <typename T> 
struct TestTimer	{

public:
	typedef T Type; 
//	typedef Time<CLOCK_REALTIME> TTime;
//	typedef Time<CLOCK_MONOTONIC> TTime;
	typedef Time<CLOCK_PROCESS_CPUTIME_ID> TTime;
//	typedef Time<CLOCK_THREAD_CPUTIME_ID> TTime;
       
	TTime tr;
//	TestTimer(Type t):t(t){};
	void operator ()()	{
		TTime t1;
		t();			
		TTime t2;
		tr = t2-t1;
		std::cout << tr << std::endl;
		//c.log() <<"hola" << std::endl;
	}
	Type t;

};
*/

template <typename T> 
struct TestTimer	{

public:
	typedef T Type; 
//	typedef Time<CLOCK_REALTIME> TTime;
//	typedef Time<CLOCK_MONOTONIC> TTime;
	typedef Time<CLOCK_PROCESS_CPUTIME_ID> TTime;
//	typedef Time<CLOCK_THREAD_CPUTIME_ID> TTime;
       
	TTime tr;
//	TestTimer(Type t):t(t){};
	void operator ()()	{
		
		chrono::high_resolution_clock clock;
		chrono::high_resolution_clock::time_point t1 = clock.now();
		t();
		chrono::high_resolution_clock::time_point  t2 = clock.now();
		cout << name<TestTimer>() <<  t2.time_since_epoch().count()-t1.time_since_epoch().count() << endl;
		
	}
	Type t;

};

/*
	chrono::high_resolution_clock clock;
	chrono::high_resolution_clock::time_point t1 = clock.now();
	for(char32_t cp=0;cp<=0x10ffff;++cp)	{
		GraphemeBinary::get_value(cp);
	}
	chrono::high_resolution_clock::time_point  t2 = clock.now();
	cout << "GraphemeBinary::get_value " <<  t2.time_since_epoch().count()-t1.time_since_epoch().count() << endl;
*/

/*
template <typename _T, typename _Context> std::ostream& operator << (std::ostream& cout, TestTimer<_T, _Context>& t)
{
	cout << "time:" << t.tr;
    return cout;
}
*/


template<typename T1,typename T2,typename T3,typename T4, template<typename> class Test >
struct Combine1Test	 {
	void operator()()	{
		Test<T1> t1; t1();
		Test<T2> t2; t2();
		Test<T3> t3; t3();
		Test<T4> t4; t4();
	}
	static void exec()	{
		Combine1Test t;
		t();
	}
};
  
template<typename T1,typename T2,typename T3,typename T4, template<typename, typename> class Test >
struct Combine2Test	 {
	void operator()()	{
		Test<T1, T1> t1; t1();
		Test<T1, T2> t2; t2();
		Test<T1, T3> t3; t3();
		Test<T1, T4> t4; t4();
		Test<T2, T1> t5; t5();
		Test<T2, T2> t6; t6();
		Test<T2, T3> t7; t7();
		Test<T2, T4> t8; t8();
		Test<T3, T1> t9; t9();
		Test<T3, T2> t10; t10();
		Test<T3, T3> t11; t11();
		Test<T3, T4> t12; t12();
		Test<T4, T1> t13; t13();
		Test<T4, T2> t14; t14();
		Test<T4, T3> t15; t15();
		Test<T4, T4> t16; t16();
	}
	
};




typedef void(*function_void)() ;
template <typename T>
void reg_function(boost::unit_test::test_suite* test, function_void v )	{
	test->add(boost::unit_test::make_test_case( 
		boost::unit_test::callback0<>(v), 		
		name<T>() ));
}

template<typename T>
struct BoostTestRegister	{
	static void reg(boost::unit_test::test_suite* test)	{
		test->add( BOOST_TEST_CASE( 
			(&T::exec) )); 
	}
};


template<typename T1,typename T2,typename T3,typename T4, template<typename> class Test >
struct MultipleBoostTestRegister	{
	static void reg(boost::unit_test::test_suite* test)	{
		reg_function<Test<T1>>(test, &Test<T1>::exec);	
		reg_function<Test<T2>>(test, &Test<T2>::exec);	
		reg_function<Test<T3>>(test, &Test<T3>::exec);	
		reg_function<Test<T4>>(test, &Test<T4>::exec);	
	}
};



template<typename T1,typename T2,typename T3,typename T4, template<typename, typename> class Test >
struct Multiple2BoostTestRegister	{
	static void reg(boost::unit_test::test_suite* test)	{		
		reg_function<Test<T1, T1> >(test, &Test<T1, T1>::exec);	
		reg_function<Test<T1, T2> >(test, &Test<T1, T2>::exec);	
		reg_function<Test<T1, T3> >(test, &Test<T1, T3>::exec);	
		reg_function<Test<T1, T4> >(test, &Test<T1, T4>::exec);	
		reg_function<Test<T2, T1> >(test, &Test<T2, T1>::exec);	
		reg_function<Test<T2, T2> >(test, &Test<T2, T2>::exec);	
		reg_function<Test<T2, T3> >(test, &Test<T2, T3>::exec);	
		reg_function<Test<T2, T4> >(test, &Test<T2, T4>::exec);	
		reg_function<Test<T3, T1> >(test, &Test<T3, T1>::exec);	
		reg_function<Test<T3, T2> >(test, &Test<T3, T2>::exec);	
		reg_function<Test<T3, T3> >(test, &Test<T3, T3>::exec);	
		reg_function<Test<T3, T4> >(test, &Test<T3, T4>::exec);	
		reg_function<Test<T4, T1> >(test, &Test<T4, T1>::exec);	
		reg_function<Test<T4, T2> >(test, &Test<T4, T2>::exec);	
		reg_function<Test<T4, T3> >(test, &Test<T4, T3>::exec);	
		reg_function<Test<T4, T4> >(test, &Test<T4, T4>::exec);	
	}
	
};



