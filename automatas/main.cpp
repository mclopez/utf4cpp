/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <stdio.h>

#include <map>
#include <string>
#include <cassert>


//#include "dfa.h"
//#include "nfa.h"

//#include "reg_exp.h"

//#include "dfa_test.h"
#include "reg_exp_test.h"

/*
void test_v1_dfa()	{
	using namespace v1;
	Dfa<char> dfa;
	dfa.add_state("A", {{'a', "B"}, {'b', "C"}}, true);
	dfa.add_state("B", {{'a', "E"}, {'b', "C"}});
	dfa.add_state("C", {{'a', "B"}, {'b', "D"}});
	dfa.add_state("D", {{'a', "B"}, {'b', "D"}});
	dfa.add_state("E", {{'a', "F"}, {'b', "H"}});
	dfa.add_state("F", {{'a', "G"}, {'b', "H"}});
	dfa.add_state("G", {{'a', "G"}, {'b', "I"}});
	dfa.add_state("H", {{'a', "H"}, {'b', "I"}}, true);
	dfa.add_state("I", {{'a', "I"}, {'b', "I"}}, true);
	
	std::cout << dfa << std::endl;
	
	Dfa<char> dfa2 = dfa.minimize();

	std::cout << dfa << std::endl;
	std::cout << dfa2 << std::endl;


	Dfa<char> dfa;
	dfa.add_state("A", {{'a', "B"}, {'b', "C"}}, true);
	dfa.add_state("B", {{'a', "E"}, {'b', "C"}});
	dfa.add_state("C", {{'a', "B"}, {'b', "D"}});
	dfa.add_state("D", {{'a', "B"}});
	dfa.add_state("E", {{'a', "F"}, {'b', "H"}});
	dfa.add_state("F", {{'a', "G"}, {'b', "H"}});
	dfa.add_state("G", {{'b', "I"}});
	dfa.add_state("H", {{'b', "I"}}, true);
	dfa.add_state("I", {{'b', "I"}}, true);

	std::cout << dfa << std::endl;
*/	
/*	
}

void test_v1_nfa()	{
	using namespace v1;
	Nfa<char> nfa;
	nfa.add_state("A", {{'a', "B"}, {'b', "C"}}, Nfa<char>::State::INITIAL|Nfa<char>::State::FINAL);
	nfa.add_state("B", {{'a', "E"}, {'b', "C"}});

	nfa.add_state("C", {{'a', "B"}, {'b', "D"}});
	nfa.add_state("D", {{'a', "B"}});
	nfa.add_state("E", {{'a', "F"}, {'b', "H"}});
	nfa.add_state("F", {{'a', "G"}, {'b', "H"}});
	nfa.add_state("G", {{'b', "I"}});
	nfa.add_state("H", {{'b', "I"}}, Nfa<char>::State::FINAL);
	nfa.add_state("I", {{'b', "I"}}, Nfa<char>::State::FINAL);

	std::cout << nfa << std::endl;
	Dfa<char> dfa;
	convert(nfa, dfa);
	std::cout << dfa << std::endl;
	
}

void test_v1_nfa2()	{
	using namespace v1;
	Nfa<char> nfa;
	nfa.add_state("A", {{'a', "B"}}, Nfa<char>::State::INITIAL);
	nfa.add_state("B", {{'a', "B"}, {'b', "B"},{'b', "C"}});
	nfa.add_state("C", {}, Nfa<char>::State::FINAL);

	nfa.add_state("D", {{'b', "E"}}, Nfa<char>::State::INITIAL);
	nfa.add_state("E", {{'a', "E"}, {'b', "E"},{'a', "F"}});
	nfa.add_state("F", {}, Nfa<char>::State::FINAL);


	std::cout << nfa << std::endl;
	Dfa<char> dfa;
	convert(nfa, dfa);
	std::cout << "dfa result: " << std::endl;
	std::cout << dfa << std::endl;
	
}

void test_v1_nfa3()	{
	using namespace v1;
	Nfa<char> nfa1;
	nfa1.add_state("A", {{'a', "B"}}, Nfa<char>::State::INITIAL);
	nfa1.add_state("B", {{'a', "B"}, {'b', "B"},{'b', "C"}});
	nfa1.add_state("C", {}, Nfa<char>::State::FINAL);

	nfa1.add_state("D", {{'b', "E"}}, Nfa<char>::State::INITIAL);
	nfa1.add_state("E", {{'a', "E"}, {'b', "E"},{'a', "F"}});
	nfa1.add_state("F", {}, Nfa<char>::State::FINAL);

	Nfa<char> nfa2;
	nfa2.add_state("A", {{'a', "B"}}, Nfa<char>::State::INITIAL);
	nfa2.add_state("B", {{'a', "B"}, {'b', "B"},{'b', "C"}});
	nfa2.add_state("C", {}, Nfa<char>::State::FINAL);

	nfa2.add_state("D", {{'b', "E"}}, Nfa<char>::State::INITIAL);
	nfa2.add_state("E", {{'a', "E"}, {'b', "E"},{'a', "F"}});
	nfa2.add_state("F", {}, Nfa<char>::State::FINAL);


	std::cout << nfa1 << std::endl;
	std::cout << nfa2 << std::endl;
	Nfa<char> nfa = concat(nfa1,nfa2);
	std::cout << nfa << std::endl;
	
	Dfa<char> dfa;
	convert(nfa, dfa);
	
	std::cout << std::endl;	
	std::cout << "dfa result: " << std::endl;	
	std::cout << dfa << std::endl;	

	
}

void test_v1_nfa4()	{
	using namespace v1;
	Nfa<char> nfa1;
*/	/*
->S1|A a->S1|B 
  S1|B a->S1|B b->S1|B b->S1|C b->S2|A b->S2|D 
  S1|C 
->S1|D b->S1|E 
  S1|E a->S1|E a->S1|F a->S2|A a->S2|D b->S1|E 
  S1|F 
  S2|A a->S2|B 
  S2|B a->S2|B b->S2|B b->S2|C 
  S2|C +
  S2|D b->S2|E 
  S2|E a->S2|E a->S2|F b->S2|E 
  S2|F +
	 
	 * */
	 
/*	 
	nfa1.add_state("S1|A", {{'a', "S1|B" }}, Nfa<char>::State::INITIAL);
	nfa1.add_state("S1|B", {{'a', "S1|B"}, {'b', "S1|B"}, {'b', "S1|C"}, {'b', "S2|A"}, {'b', "S2|D"  }});
	nfa1.add_state("S1|C", {});
	nfa1.add_state("S1|D", {{'b', "S1|E"  }}, Nfa<char>::State::INITIAL);
	nfa1.add_state("S1|E", {{'a', "S1|E"}, {'a', "S1|F"}, {'a', "S2|A"}, {'a', "S2|D"}, {'b', "S1|E"  }});
	nfa1.add_state("S1|F", {});
	nfa1.add_state("S2|A", {{'a', "S2|B"  }}); 
	nfa1.add_state("S2|B", {{'a', "S2|B"}, {'b', "S2|B"}, {'b', "S2|C"}}); 
	nfa1.add_state("S2|C", {}, Nfa<char>::State::FINAL);
	nfa1.add_state("S2|D", {{'b', "S2|E"}});
	nfa1.add_state("S2|E", {{'a', "S2|E"}, {'a', "S2|F"}, {'b', "S2|E"}}); 
	nfa1.add_state("S2|F", {}, Nfa<char>::State::FINAL);
	

	Dfa<char> dfa;
	convert(nfa1, dfa);
	
	std::cout << std::endl;	
	std::cout << "dfa result: " << std::endl;	
	std::cout << dfa << std::endl;	

}
*/


/*
const size_t state_A = 0;
const size_t state_B = 1;
const size_t state_C = 2;
const size_t state_D = 3;
const size_t state_E = 4;
const size_t state_F = 5;
const size_t state_G = 6;
const size_t state_H = 7;
const size_t state_I = 8;

const size_t state_1 = 0;
const size_t state_2 = 1;
const size_t state_3 = 2;
const size_t state_4 = 3;
const size_t state_5 = 4;

template<typename CharT>
class Test	{
	typedef Dfa<CharT> Dfa;
	typedef Nfa<CharT> Nfa;
	Dfa dfa1;	
	Dfa dfa1_min;	
	Dfa dfa2;	
	Dfa dfa2_min;
	Nfa nfa1a;
	Nfa nfa1b;
	Nfa nfa2;
	Nfa nfa_concat_nfa1a_nfa2;
	Nfa nfa_concat_nfa1b_nfa2;
	Dfa dfa_concat_nfa1a_nfa2;
	Dfa dfa_concat_nfa1b_nfa2;
	
public:
	Test():
		dfa1(9),
		dfa1_min(5),
		dfa2(8)			
	{
		dfa1.set_state_info(state_A, {{'a', state_B}, {'b', state_C}}, true);
		dfa1.set_state_info(state_B, {{'a', state_E}, {'b', state_C}});
		dfa1.set_state_info(state_C, {{'a', state_B}, {'b', state_D}});
		dfa1.set_state_info(state_D, {{'a', state_B}, {'b', state_D}});
		dfa1.set_state_info(state_E, {{'a', state_F}, {'b', state_H}});
		dfa1.set_state_info(state_F, {{'a', state_G}, {'b', state_H}});
		dfa1.set_state_info(state_G, {{'a', state_G}, {'b', state_I}});
		dfa1.set_state_info(state_H, {{'a', state_H}, {'b', state_I}}, true);
		dfa1.set_state_info(state_I, {{'a', state_I}, {'b', state_I}}, true);
		

		dfa1_min.set_state_info(0, {{'a', 1}, {'b', 2}}, true);
		dfa1_min.set_state_info(1, {{'a', 3}, {'b', 2}});
		dfa1_min.set_state_info(2, {{'a', 1}, {'b', 2}});
		dfa1_min.set_state_info(3, {{'a', 3}, {'b', 4}});
		dfa1_min.set_state_info(4, {{'a', 4}, {'b', 4}}, true);
		dfa1_min = normalize(dfa1_min);
		
		
		dfa2.set_state_info(state_A, {{'a', state_A}, {'b', state_B}});
		dfa2.set_state_info(state_B, {{'a', state_C}, {'b', state_D}});
		dfa2.set_state_info(state_C, {{'a', state_E}, {'b', state_F}});
		dfa2.set_state_info(state_D, {{'a', state_G}, {'b', state_H}});
		dfa2.set_state_info(state_E, {{'a', state_A}, {'b', state_C}}, true);
		dfa2.set_state_info(state_F, {{'a', state_C}, {'b', state_D}}, true);
		dfa2.set_state_info(state_G, {{'a', state_E}, {'b', state_F}}, true);
		dfa2.set_state_info(state_H, {{'a', state_G}, {'b', state_G}}, true);
		

		dfa2_min.set_state_info(state_A, {{'a', state_A}, {'b', state_B}});
		dfa2_min.set_state_info(state_B, {{'a', state_C}, {'b', state_D}});
		dfa2_min.set_state_info(state_C, {{'a', state_E}, {'b', state_F}});
		dfa2_min.set_state_info(state_D, {{'a', state_G}, {'b', state_H}});
		dfa2_min.set_state_info(state_E, {{'a', state_A}, {'b', state_C}}, true);
		dfa2_min.set_state_info(state_F, {{'a', state_C}, {'b', state_D}}, true);
		dfa2_min.set_state_info(state_G, {{'a', state_E}, {'b', state_F}}, true);
		dfa2_min.set_state_info(state_H, {{'a', state_G}, {'b', state_G}}, true);
		
		
		
		// example pag40
		nfa1a.set_state_info(state_A, {{'a', state_B}, {'b', state_A}}, Nfa::State::INITIAL|Nfa::State::FINAL);
		nfa1a.set_state_info(state_B, {{'a', state_C}, {'b', state_B}});
		nfa1a.set_state_info(state_C, {{'a', state_A}, {'b', state_C}});

		// same as nfa1a but end state
		nfa1b.set_state_info(state_A, {{'a', state_B}, {'b', state_A}}, Nfa::State::INITIAL);
		nfa1b.set_state_info(state_B, {{'a', state_C}, {'b', state_B}});
		nfa1b.set_state_info(state_C, {{'a', state_A}, {'b', state_C}}, Nfa::State::FINAL);


		nfa2.set_state_info(state_1, {{'a', state_2}}, Nfa::State::INITIAL);
		nfa2.set_state_info(state_2, {{'a', state_2}, {'b', state_2}}, Nfa::State::FINAL);
		nfa2.set_state_info(state_3, {{'a', state_3}, {'b', state_3}, {'b', state_4}}, Nfa::State::INITIAL);
		nfa2.set_state_info(state_4, {}, Nfa::State::FINAL);
		
		nfa_concat_nfa1a_nfa2.set_state_info(state_A, {{'a', state_B}, {'b', state_A}, {'b', state_D}, {'b', state_F}}, Nfa::State::INITIAL);
		nfa_concat_nfa1a_nfa2.set_state_info(state_B, {{'a', state_C}, {'b', state_B}});
		nfa_concat_nfa1a_nfa2.set_state_info(state_C, {{'a', state_A}, {'a', state_D}, {'a', state_F}, {'b', state_C}, });
		nfa_concat_nfa1a_nfa2.set_state_info(state_D, {{'a', state_E}}, Nfa::State::INITIAL);
		nfa_concat_nfa1a_nfa2.set_state_info(state_E, {{'a', state_E}, {'b', state_E}}, Nfa::State::FINAL);
		nfa_concat_nfa1a_nfa2.set_state_info(state_F, {{'a', state_F}, {'b', state_F}, {'b', state_G}}, Nfa::State::INITIAL);
		nfa_concat_nfa1a_nfa2.set_state_info(state_G, {}, Nfa::State::FINAL);

		nfa_concat_nfa1b_nfa2.set_state_info(state_A, {{'a', state_B}, {'b', state_A}, {'b', state_D}, {'b', state_F}}, Nfa::State::INITIAL);
		nfa_concat_nfa1b_nfa2.set_state_info(state_B, {{'a', state_C}, {'b', state_B}});
		nfa_concat_nfa1b_nfa2.set_state_info(state_C, {{'a', state_A}, {'a', state_D}, {'a', state_F}, {'b', state_C}, });
		nfa_concat_nfa1b_nfa2.set_state_info(state_D, {{'a', state_E}});
		nfa_concat_nfa1b_nfa2.set_state_info(state_E, {{'a', state_E}, {'b', state_E}}, Nfa::State::FINAL);
		nfa_concat_nfa1b_nfa2.set_state_info(state_F, {{'a', state_F}, {'b', state_F}, {'b', state_G}});
		nfa_concat_nfa1b_nfa2.set_state_info(state_G, {}, Nfa::State::FINAL);


		//std::cout << "nfa_concat_nfa1_nfa2: \n" << nfa_concat_nfa1a_nfa2 << std::endl;
		dfa_concat_nfa1a_nfa2 = normalize(minimize(to_dfa(nfa_concat_nfa1a_nfa2)));
//		dfa_concat_nfa1_nfa2 = convert(nfa_concat_nfa1_nfa2);
		dfa_concat_nfa1b_nfa2 = normalize(minimize(to_dfa(nfa_concat_nfa1b_nfa2)));
	}
	
	void dfa_minimize1_test()	{
		


//		std::cout << "dfa: \n " << dfa << std::endl;

		Dfa dfa2 = normalize(minimize(dfa1));
//		std::cout << "dfa2: \n" << dfa2 << std::endl;

//		std::cout << "dfa1_min: \n" << dfa1_min << std::endl;
		assert(dfa1_min==dfa2);
		std::cout << "Test::dfa_minimize1_test() ok \n";
		
	}
	
	
	void dfa_minimize2_test()	{
		//std::cout << "dfa: \n " << dfa2 << std::endl;
		Dfa dfa_aux = normalize(minimize(dfa2));
		//std::cout << "dfa (minimize): \n" << dfa3 << std::endl;
		//Dfa<char> result_m = normalize(minimize(result));
		//std::cout << "dfa2_min: \n" << dfa2_min << std::endl;
		assert(dfa2_min==dfa_aux);
		std::cout << "Test::dfa_minimize2_test() ok \n";
		
	}
	
	void nfa_concatenation1_test()	{


		//std::cout << nfa1 << std::endl;
		//std::cout << nfa2 << std::endl;
		Nfa nfa = concat(nfa1a, nfa2);
		//std::cout << "nfa (concat): \n" << nfa << std::endl;
		Dfa dfa = to_dfa(nfa);
		//std::cout << "dfa (convert): \n" << dfa << std::endl;	
		Dfa dfa2 = minimize(dfa);
		//std::cout << "dfa (minimize): \n"  << dfa2 << std::endl;
		Dfa dfa3 = normalize(dfa2);
		//std::cout << "dfa (normalized): \n"  << dfa3 << std::endl;	
		
		
		//std::cout << "dfa_concat_nfa1_nfa2: \n"  << dfa_concat_nfa1a_nfa2 << std::endl;	
		
		assert(dfa_concat_nfa1a_nfa2==dfa3);
		std::cout << "Test::nfa_concatenation1_test() ok \n";
		
	}
	
	void nfa_concatenation2_test()	{

		//std::cout << nfa1 << std::endl;
		//std::cout << nfa2 << std::endl;
		Nfa nfa = concat(nfa1b, nfa2);
		//std::cout << "nfa (concat): \n" << nfa << std::endl;
		Dfa dfa = to_dfa(nfa);
		//std::cout << "dfa (convert): \n" << dfa << std::endl;	
		Dfa dfa2 = minimize(dfa);
		//std::cout << "dfa (minimize): \n"  << dfa2 << std::endl;
		Dfa dfa3 = normalize(dfa2);
		std::cout << "dfa (normalized): \n"  << dfa3 << std::endl;	
		
		
		std::cout << "dfa_concat_nfa1b_nfa2: \n"  << dfa_concat_nfa1b_nfa2 << std::endl;	
		
		assert(dfa_concat_nfa1b_nfa2==dfa3);
		std::cout << "Test::nfa_concatenation2_test() ok \n";
		
	}
	
	void nfa_concatenation3_test()	{
		//std::cout << nfa1 << std::endl;
		//std::cout << nfa2 << std::endl;
		Nfa nfa = concat(minimize(to_dfa(nfa1b)), minimize(to_dfa(nfa2)));
		//std::cout << "nfa (concat): \n" << nfa << std::endl;
		Dfa dfa = to_dfa(nfa);
		//std::cout << "dfa (convert): \n" << dfa << std::endl;	
		Dfa dfa2 = minimize(dfa);
		//std::cout << "dfa (minimize): \n"  << dfa2 << std::endl;
		Dfa dfa3 = normalize(dfa2);
		//std::cout << "dfa (normalized): \n"  << dfa3 << std::endl;	
		
		
		//std::cout << "dfa_concat_nfa1b_nfa2: \n"  << dfa_concat_nfa1b_nfa2 << std::endl;	
		
		assert(dfa_concat_nfa1b_nfa2==dfa3);
		std::cout << "Test::nfa_concatenation3_test() ok \n";
		
	}
	
	
};

*/
/*
void test_v2_dfa()	{
	using namespace v2;
	Dfa<char> dfa(9);
	const size_t state_A = 0;
	const size_t state_B = 1;
	const size_t state_C = 2;
	const size_t state_D = 3;
	const size_t state_E = 4;
	const size_t state_F = 5;
	const size_t state_G = 6;
	const size_t state_H = 7;
	const size_t state_I = 8;
	
	
	dfa.set_state_info(state_A, {{'a', state_B}, {'b', state_C}}, true);
	dfa.set_state_info(state_B, {{'a', state_E}, {'b', state_C}});
	dfa.set_state_info(state_C, {{'a', state_B}, {'b', state_D}});
	dfa.set_state_info(state_D, {{'a', state_B}, {'b', state_D}});
	dfa.set_state_info(state_E, {{'a', state_F}, {'b', state_H}});
	dfa.set_state_info(state_F, {{'a', state_G}, {'b', state_H}});
	dfa.set_state_info(state_G, {{'a', state_G}, {'b', state_I}});
	dfa.set_state_info(state_H, {{'a', state_H}, {'b', state_I}}, true);
	dfa.set_state_info(state_I, {{'a', state_I}, {'b', state_I}}, true);
	
	std::cout << dfa << std::endl;

	Dfa<char> dfa2 = minimize(dfa);

	std::cout << dfa << std::endl;
	std::cout << dfa2 << std::endl;
	
}

void test_v2_nfa3()	{
	using namespace v2;
	typedef Nfa<char> Nfa;
	typedef Dfa<char> Dfa;
	Nfa nfa1;
	const size_t state_A = 0;
	const size_t state_B = 1;
	const size_t state_C = 2;
	const size_t state_D = 3;
	const size_t state_E = 4;
	const size_t state_F = 5;
	const size_t state_G = 6;
	const size_t state_H = 7;
	const size_t state_I = 8;
	
	nfa1.set_state_info(state_A, {{'a', state_B}}, Nfa::State::INITIAL);
	nfa1.set_state_info(state_B, {{'a', state_B}, {'b', state_B},{'b', state_C}});
	nfa1.set_state_info(state_C, {}, Nfa::State::FINAL);

	nfa1.set_state_info(state_D, {{'b', state_E}}, Nfa::State::INITIAL);
	nfa1.set_state_info(state_E, {{'a', state_E}, {'b', state_E},{'a', state_F}});
	nfa1.set_state_info(state_F, {}, Nfa::State::FINAL);

	Nfa nfa2;
	nfa2.set_state_info(state_A, {{'a', state_B}}, Nfa::State::INITIAL);
	nfa2.set_state_info(state_B, {{'a', state_B}, {'b', state_B},{'b', state_C}});
	nfa2.set_state_info(state_C, {}, Nfa::State::FINAL);

	nfa2.set_state_info(state_D, {{'b', state_E}}, Nfa::State::INITIAL);
	nfa2.set_state_info(state_E, {{'a', state_E}, {'b', state_E},{'a', state_F}});
	nfa2.set_state_info(state_F, {}, Nfa::State::FINAL);


	std::cout << nfa1 << std::endl;
	std::cout << nfa2 << std::endl;
	Nfa nfa = concat(nfa1,nfa2);
	std::cout << nfa << std::endl;
	//return;
	
	Dfa dfa = to_dfa(nfa);
	std::cout << "dfa result: \n" << dfa << std::endl;	
	Dfa dfa2 = minimize(dfa);
	std::cout << "dfa2 (minimize): \n"  << dfa2 << std::endl;
	Dfa dfa3 = normalize(dfa2);
	std::cout << "dfa3 (normalized): \n"  << dfa3 << std::endl;	

	
}

void test_v2_nfa4()	 {
	using namespace v2;
	typedef v2::Nfa<char> Nfa;
	typedef typename v2::Nfa<char>::State State;
	Nfa nfa(9);
	const size_t state_A = 0;
	const size_t state_B = 1;
	const size_t state_C = 2;
	const size_t state_D = 3;
	const size_t state_E = 4;
	const size_t state_F = 5;
	const size_t state_G = 6;
	const size_t state_H = 7;
	const size_t state_I = 8;

	nfa.set_state_info(state_A, {{'a', state_B}, {'b', state_C}},State::INITIAL|State::FINAL);
	nfa.set_state_info(state_B, {{'a', state_E}, {'b', state_C}});
	nfa.set_state_info(state_C, {{'a', state_B}, {'b', state_D}});
	nfa.set_state_info(state_D, {{'a', state_B}});
	nfa.set_state_info(state_E, {{'a', state_F}, {'b', state_H}});
	nfa.set_state_info(state_F, {{'a', state_G}, {'b', state_H}});
	nfa.set_state_info(state_G, {{'b', state_I}});
	nfa.set_state_info(state_H, {{'b', state_I}}, State::FINAL);
	nfa.set_state_info(state_I, {{'b', state_I}}, State::FINAL);

	std::cout << nfa << std::endl;
	Dfa<char> dfa = to_dfa(nfa);
	std::cout << dfa << std::endl;
	
}


void test_v2_nfa5()	 {
	using namespace v2;
	typedef v2::Nfa<char> Nfa;
	typedef typename v2::Nfa<char>::State State;
	Nfa nfa(9);

	const size_t state_A = 0;
	const size_t state_B = 1;
	const size_t state_C = 2;
	const size_t state_D = 3;
	const size_t state_E = 4;
	const size_t state_F = 5;
	const size_t state_G = 6;

	nfa.set_state_info(state_A, {{'a', state_B}, {'b', state_B} }, State::INITIAL);
	nfa.set_state_info(state_B, {{'a', state_C}, {'b', state_C} });
	nfa.set_state_info(state_C, {{'a', state_A}, {'a', state_D}, {'b', state_A}, {'b', state_D}});
	nfa.set_state_info(state_D, {{'a', state_E}, {'b', state_E} }, State::INITIAL);
	nfa.set_state_info(state_E, {{'a', state_F}, {'b', state_F} });
	nfa.set_state_info(state_F, {{'a', state_G}                 });
	nfa.set_state_info(state_G, {{'a', state_G}, {'b', state_G} }, State::FINAL);

	std::cout << nfa << std::endl;
	Dfa<char> dfa = to_dfa(nfa);	
	std::cout << dfa << std::endl;
	Dfa<char> dfa2 = minimize(dfa);	
	std::cout << dfa2 << std::endl;
	
}
*/


/*	"1+(2*3)+4";
	1
	(
	2
	3
	*
	)
	+
	4
	+
	"1+2+3+4";
	1
	2
	+
	3
	+
	4
	+
	"1+2*3+4";
	1
	2
	3
	*
	+
	4
	+
*
*/
	






int main(int argc, char **argv)
{
	printf("Automatas\n");
	RegExpTest regexp1;	regexp1();
	return 0;
}
