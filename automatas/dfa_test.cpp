/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "dfa_test.h"


#include "dfa.h"
#include "nfa.h"
#include "test_util.h"


DfaTest::DfaTest()
{
}

DfaTest::~DfaTest()
{
}
/*	
template <typename CharT>
void check(const std::string& test, typename const Dfa<CharT>& dfa, bool result)	{
	std::cout << std:: boolalpha  << check(dfa, ) << std::endl;	
}
*/


void DfaTest::test1()	{
	typedef char CharT;	
	typedef Dfa<CharT> Dfa;
//	typedef Nfa<CharT> Nfa;

	const size_t state_A = 0;
	const size_t state_B = 1;
	const size_t state_C = 2;

	Dfa dfa_null;
	dfa_null.set_state_info(state_A, {}, true);

	Dfa dfa_a;
	dfa_a.set_state_info(state_A, {{'a', state_B}});
	dfa_a.set_state_info(state_B, {}, true);

	Dfa dfa_aa;
	dfa_aa.set_state_info(state_A, {{'a', state_B}});
	dfa_aa.set_state_info(state_B, {{'a', state_C}});
	dfa_aa.set_state_info(state_C, {}, true);

	Dfa dfa_ab;
	dfa_ab.set_state_info(state_A, {{'a', state_B}});
	dfa_ab.set_state_info(state_B, {{'b', state_C}});
	dfa_ab.set_state_info(state_C, {}, true);
	
	std::string s_null = "";
	std::string s_a = "a";
	std::string s_aa = "aa";
	std::string s_ab = "ab";
//	std::cout << std:: boolalpha  << check(dfa1, s1) << std::endl;
//	std::cout << std:: boolalpha  << check(dfa1, s2) << std::endl;
//	std::cout << std:: boolalpha  << check(dfa2, s2) << std::endl;

	CHECK(dfa_null, s_a,	false);
	CHECK(dfa_null, s_null,	true);
	
	CHECK(dfa_a, s_a,	true);
	CHECK(dfa_a, s_aa,	false);
	CHECK(dfa_a, s_ab,	false);
	
	CHECK(dfa_aa, s_a,	false);
	CHECK(dfa_aa, s_aa, true);
	CHECK(dfa_aa, s_ab, false);
	
	CHECK(dfa_ab, s_a,	false);
	CHECK(dfa_ab, s_aa, false);
	CHECK(dfa_ab, s_ab, true);
}


void DfaTest::test2()	{
	typedef char CharT;	
	typedef Dfa<CharT> _Dfa;
	typedef Nfa<CharT> _Nfa;

	const size_t state_A = 0;
	const size_t state_B = 1;
//	const size_t state_C = 2;

	_Nfa nfa_a;
	nfa_a.set_state_info(state_A, {{'a', state_B}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(state_B, {}, _Nfa::State::FINAL);
//	std::cout <<"nfa_a:\n" << nfa_a << '\n';

	_Nfa nfa_b;
	nfa_b.set_state_info(state_A, {{'b', state_B}}, _Nfa::State::INITIAL);
	nfa_b.set_state_info(state_B, {}, _Nfa::State::FINAL);
//	std::cout <<"nfa_b:\n" << nfa_b << '\n';

	_Nfa nfa_ab = concat(nfa_a, nfa_b);
//	std::cout <<"nfa_ab:\n" << nfa_ab << '\n';
	
	//_Dfa dfa_ab = minimize(to_dfa(nfa_ab));
	_Dfa dfa_ab = minimize(to_dfa(nfa_ab));
//	std::cout <<"dfa_ab:\n " << dfa_ab << '\n';
//	_Dfa dfa_ab_nor = normalize(minimize(to_dfa(nfa_ab)));
//	std::cout <<"dfa_ab_nor:\n " << dfa_ab_nor << '\n';

	std::string s_a = "a";
	std::string s_aa = "aa";
	std::string s_ab = "ab";
	
	CHECK(dfa_ab, s_a,	false);
	CHECK(dfa_ab, s_aa, false);
	CHECK(dfa_ab, s_ab, true);
}

void DfaTest::test3()	{
	typedef char CharT;	
	typedef Dfa<CharT> _Dfa;
	typedef Nfa<CharT> _Nfa;

	const size_t state_A = 0;
	const size_t state_B = 1;
//	const size_t state_C = 2;

	_Nfa nfa_a;
	nfa_a.set_state_info(state_A, {{'a', state_B}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(state_B, {}, _Nfa::State::FINAL);
	//std::cout <<"nfa_a:\n" << nfa_a << '\n';

	_Nfa nfa_b;
	nfa_b.set_state_info(state_A, {{'b', state_B}}, _Nfa::State::INITIAL);
	nfa_b.set_state_info(state_B, {}, _Nfa::State::FINAL);
	//std::cout <<"nfa_b:\n" << nfa_b << '\n';

	_Nfa nfa_a_u_b = nfa_union(nfa_a, nfa_b);
	//std::cout <<"nfa_a_u_b:\n" << nfa_a_u_b << '\n';
	_Dfa dfa_a_u_b = normalize(minimize(to_dfa(nfa_a_u_b)));
	//std::cout <<"dfa_a_u_b:\n" << dfa_a_u_b << '\n';
	
	std::string s_a = "a";
	std::string s_b = "b";
	std::string s_aa = "aa";
	std::string s_ab = "ab";
	
	CHECK(dfa_a_u_b, s_a,	true);
	CHECK(dfa_a_u_b, s_b,	true);
	CHECK(dfa_a_u_b, s_aa,	false);
	CHECK(dfa_a_u_b, s_ab,	false);
	
	
}

void DfaTest::test4()	{
	typedef char CharT;	
	typedef Dfa<CharT> _Dfa;
	typedef Nfa<CharT> _Nfa;

	const size_t state_A = 0;
	const size_t state_B = 1;
//	const size_t state_C = 2;

	_Nfa nfa_a;
	nfa_a.set_state_info(state_A, {{'a', state_B}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(state_B, {}, _Nfa::State::FINAL);
	std::cout <<"nfa_a:\n" << nfa_a << '\n';

	_Nfa nfa_b;
	nfa_b.set_state_info(state_A, {{'b', state_B}}, _Nfa::State::INITIAL);
	nfa_b.set_state_info(state_B, {}, _Nfa::State::FINAL);
	//std::cout <<"nfa_b:\n" << nfa_b << '\n';

	_Nfa nfa_a_kleene_cross = kleene_cross(nfa_a);
	std::cout <<"nfa_a_kleene_cross:\n" << nfa_a_kleene_cross << '\n';

	_Dfa dfa_a_kleene_cross = normalize(minimize(to_dfa(nfa_a_kleene_cross)));
	std::cout <<"dfa_a_kleene_cross:\n" << dfa_a_kleene_cross << '\n';

	_Nfa nfa_ab_kleene_cross = kleene_cross(concat(nfa_a, nfa_b));
	std::cout <<"nfa_ab_kleene_cross:\n" << nfa_ab_kleene_cross << '\n';

	_Dfa dfa_ab_kleene_cross = normalize(minimize(to_dfa(nfa_ab_kleene_cross)));
	std::cout <<"dfa_ab_kleene_cross:\n" << dfa_ab_kleene_cross << '\n';

	
	std::string s_a = "a";
	std::string s_b = "b";
	std::string s_aa = "aa";
	std::string s_ab = "ab";
	std::string s_abab = "abab";
	std::string s_aba = "aba";
	
	CHECK(dfa_a_kleene_cross, s_a,	true);
	CHECK(dfa_a_kleene_cross, s_b,	false);
	CHECK(dfa_a_kleene_cross, s_aa,	true);
	CHECK(dfa_a_kleene_cross, s_ab,	false);

	CHECK(dfa_ab_kleene_cross, s_a,	false);
	CHECK(dfa_ab_kleene_cross, s_b,	false);
	CHECK(dfa_ab_kleene_cross, s_aa,false);
	CHECK(dfa_ab_kleene_cross, s_ab,true);
	CHECK(dfa_ab_kleene_cross, s_aba,false);
	CHECK(dfa_ab_kleene_cross, s_abab,true);
	
}


void DfaTest::test5()	{
	typedef char CharT;	
	typedef Dfa<CharT> _Dfa;
	typedef Nfa<CharT> _Nfa;

//	const size_t state_A = 0;
//	const size_t state_B = 1;
//	const size_t state_C = 2;

/*
->S0 k->S1 k->S4 k->S5 
  S1 
->S2 i->S3 i->S4 i->S5 
  S3 
->S4 +
->S5 i->S6 i->S5 
  S6 +
*/
	_Nfa nfa_a;
	nfa_a.set_state_info(0, {{'k', 1}, {'k', 4}, {'k', 5}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(1, {});
	nfa_a.set_state_info(2, {{'i', 3}, {'i', 4}, {'i', 5}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(3, {});
	nfa_a.set_state_info(4, {}, _Nfa::State::INITIAL | _Nfa::State::FINAL);
	nfa_a.set_state_info(5, {{'i', 6}, {'i', 5}}, _Nfa::State::INITIAL);
	nfa_a.set_state_info(6, {}, _Nfa::State::FINAL);
	
	std::cout <<"nfa_a:\n" << nfa_a << '\n';



	_Dfa dfa_b = to_dfa(nfa_a);
	//_Dfa dfa_b = normalize(minimize(to_dfa(nfa_a)));
	std::cout <<"dfa_b:\n" << dfa_b << '\n';



} 
  
  
void DfaTest::operator()()	{
/*	test1();
	test2();
	test3();
	test4();*/
	test5();
	std::cout << "OK" << std::endl;
}
