/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "reg_exp_test.h"
#include "reg_exp.h"

#include "nfa.h"

#include "test_util.h"
#include <cassert>

#include <sstream>
#include <string>

RegExpTest::RegExpTest()
{
}

RegExpTest::~RegExpTest()
{
}

std::string s_("");
std::string s_a("a");
std::string s_b("b");
std::string s_aa("aa");
std::string s_bb("bb");
std::string s_ab("ab");
std::string s_ba("ba");

std::string s_aaa("aaa");
std::string s_aab("aab");
std::string s_aba("aba");
std::string s_abb("abb");
std::string s_baa("baa");
std::string s_bab("bab");
std::string s_bba("bba");
std::string s_bbb("bbb");

std::string s_aaaa("aaaa");
std::string s_aaab("aaab");
std::string s_aaba("aaba");
std::string s_aabb("aabb");
std::string s_abaa("abaa");
std::string s_abab("abab");
std::string s_abba("abba");
std::string s_abbb("abbb");
std::string s_baaa("baaa");
std::string s_baab("baab");
std::string s_baba("baba");
std::string s_babb("babb");
std::string s_bbaa("bbaa");
std::string s_bbab("bbab");
std::string s_bbba("bbba");
std::string s_bbbb("bbbb");

/*
class Expression {
	
public:
	
	struct Operator {
		Operator(char op, int pri):op(op), priority(pri){}
		int priority;
		char op;
	};
	
	int parenthesis_level;
	std::stack<Operator> stack;
	
	int priority(char c)	{
		switch(c)	{
			case '+':
			case '-':
				return 0 + parenthesis_level*3;
			case '*':
			case '/':
				return 1 + parenthesis_level*3;
			case '(':
			case ')':
				return 2 + parenthesis_level*3;
		default:
			abort;
		}
	}
	
	bool is_operand(char c)	{
		switch(c)	{
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
			return true;
		default:
			return false;
		}
	}
	
	std::string evaluate(const std::string& s)	{
		std::string post_fix;
		parenthesis_level =0;
		for(const char& c: s)	{
			if (is_operand(c))	{
				if (c=='(' )	{
					parenthesis_level++; 
					continue;
				}else if (c==')' )	{
					parenthesis_level--; 
					assert (parenthesis_level>=0); 
					continue;
				}
				Operator op(c, priority(c));
				if (stack.empty() )	{
					stack.push(op);
				} else	{
					//std::cout << "c_priority: " << c_priority << "  priority(stack.top()): "<< priority(stack.top()) << std::endl;
					if (op.priority>=stack.top().priority)	{
						stack.push(op);
					} else {
						while (!stack.empty() && op.priority<stack.top().priority)	{
							//std::cout << "top: " << stack.top() << std::endl;
							post_fix.push_back(stack.top().op); 
							stack.pop();
						}
						stack.push(op);
					}
				}
			} else {
				post_fix.push_back(c);
			}
		}
		while (!stack.empty())	{
			//std::cout << "top: " << stack.top() << std::endl;
			post_fix.push_back(stack.top().op); 
			stack.pop();
		}
		return post_fix;
	}
	
};
*/


/*

( CR LF )
| ( Prepend*
    ( L+ | (L* ( ( V | LV ) V* | LVT ) T*) | T+ | [^ Control CR LF ] )
    ( Extend | SpacingMark )*
   )
| .
  
   * 
  * */
/*  
( CR LF )
| ( Prepend*
    ( L+ | (L* ( ( V | LV ) V* | LVT ) T*) | T+ | [^ Control CR LF ] )
    ( Extend | SpacingMark )*
   )
| .

L 	× 	( L | V | LV | LVT )
( LV | V ) 	× 	( V | T )
( LVT | T) 	× 	T

L	L*
L	V*
		V*
		T*	
L	LV
		V*
		T*
L	LVT
		T*
			T*

LV	V
LV	T
V	V
V	T
LVT T
T	T

L+ | ((LV V* T*) | (LVT T*) | V*T*)

*/  
void RegExpTest::operator()()	{
	test1();
	test2();
	test3();
	test4();
//	word_segmentation_test();
	test5();
	test6();
/*	Expression exp;
	std::cout << exp.evaluate("a+b*c") << std::endl;
	std::cout << exp.evaluate("a*b+c") << std::endl;
	std::cout << exp.evaluate("a+b*c+d*e+f") << std::endl;
	std::cout << exp.evaluate("(a+b)*c") << std::endl;
	std::cout << exp.evaluate("a*(b+c)") << std::endl;
	std::cout << exp.evaluate("((a+b)*(b+c))") << std::endl;

	std::cout << exp.evaluate("((a+b)*(b+c))*d") << std::endl;
	std::cout << exp.evaluate("((a+b)*(b+c))+d") << std::endl;
*/
}

void RegExpTest::test1()
{
	RegExp<char> regexp_ab;
	regexp_ab.evaluate("a.b");	
	std::cout << "regexp1:\n" << regexp_ab.dfa() << std::endl;
	CHECK(regexp_ab.dfa(), s_, false);
	CHECK(regexp_ab.dfa(), s_a, false);
	CHECK(regexp_ab.dfa(), s_b, false);
	CHECK(regexp_ab.dfa(), s_aa, false);
	CHECK(regexp_ab.dfa(), s_bb, false);


	RegExp<char> regexp_a_kc;
	regexp_a_kc.evaluate("a+");	
	std::cout << "regexp_a_kc:\n" << regexp_a_kc.dfa() << std::endl;
	CHECK(regexp_a_kc.dfa(), s_, false);
	CHECK(regexp_a_kc.dfa(), s_a, true);
	CHECK(regexp_a_kc.dfa(), s_b, false);
	CHECK(regexp_a_kc.dfa(), s_aa, true);
	CHECK(regexp_a_kc.dfa(), s_bb, false);
	CHECK(regexp_a_kc.dfa(), s_aba, false);


	RegExp<char> regexp_a_ks;
	regexp_a_ks.evaluate("a*");	
	std::cout << "regexp_a_ks:\n" << regexp_a_ks.dfa() << std::endl;
	CHECK(regexp_a_ks.dfa(), s_, true);
	CHECK(regexp_a_ks.dfa(), s_a, true);
	CHECK(regexp_a_ks.dfa(), s_b, false);
	CHECK(regexp_a_ks.dfa(), s_aa, true);
	CHECK(regexp_a_ks.dfa(), s_bb, false);
	CHECK(regexp_a_ks.dfa(), s_aba, false);


	RegExp<char> regexp_ab_ks;
	regexp_ab_ks.evaluate("a.b*");	
	std::cout << "regexp_ab_ks:\n" << regexp_ab_ks.dfa() << std::endl;
	CHECK(regexp_ab_ks.dfa(), s_, false);
	CHECK(regexp_ab_ks.dfa(), s_a, true);
	CHECK(regexp_ab_ks.dfa(), s_b, false);
	CHECK(regexp_ab_ks.dfa(), s_aa, false);
	CHECK(regexp_ab_ks.dfa(), s_bb, false);
	CHECK(regexp_ab_ks.dfa(), s_ab, true);
	CHECK(regexp_ab_ks.dfa(), s_ba, false);
	
	CHECK(regexp_ab_ks.dfa(), s_aaa, false);
	CHECK(regexp_ab_ks.dfa(), s_aab, false);
	CHECK(regexp_ab_ks.dfa(), s_aba, false);
	CHECK(regexp_ab_ks.dfa(), s_abb, true);
	CHECK(regexp_ab_ks.dfa(), s_baa, false);
	CHECK(regexp_ab_ks.dfa(), s_bab, false);
	CHECK(regexp_ab_ks.dfa(), s_bba, false);
	CHECK(regexp_ab_ks.dfa(), s_bbb, false);

	RegExp<char> regexp_a_ks_b_ks;
	regexp_a_ks_b_ks.evaluate("a*.b*");	
	std::cout << "regexp_a_ks_b_ks:\n" << regexp_a_ks_b_ks.dfa() << std::endl;
	CHECK(regexp_a_ks_b_ks.dfa(), s_, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_a, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_b, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aa, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bb, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_ab, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_ba, false);
	
	CHECK(regexp_a_ks_b_ks.dfa(), s_aaa, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aab, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_abb, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_baa, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bab, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bbb, true);

	CHECK(regexp_a_ks_b_ks.dfa(), s_aaaa, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aaab, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aaba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_aabb, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_abaa, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_abab, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_abba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_abbb, true);
	CHECK(regexp_a_ks_b_ks.dfa(), s_baaa, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_baab, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_baba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_babb, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bbaa, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bbab, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bbba, false);
	CHECK(regexp_a_ks_b_ks.dfa(), s_bbbb, true);


	RegExp<char> regexp_a_or_b;
	regexp_a_or_b.evaluate("a|b");	
	std::cout << "regexp_a_or_b:\n" << regexp_a_or_b.dfa() << std::endl;
	CHECK(regexp_a_or_b.dfa(), s_, false);
	CHECK(regexp_a_or_b.dfa(), s_a, true);
	CHECK(regexp_a_or_b.dfa(), s_b, true);
	CHECK(regexp_a_or_b.dfa(), s_aa, false);
	CHECK(regexp_a_or_b.dfa(), s_bb, false);
	CHECK(regexp_a_or_b.dfa(), s_ab, false);
	CHECK(regexp_a_or_b.dfa(), s_ba, false);


	RegExp<char> regexp_a_ks_or_b;
	regexp_a_ks_or_b.evaluate("a*|b");	
	std::cout << "regexp_a_ks_or_b:\n" << regexp_a_ks_or_b.dfa() << std::endl;
	CHECK(regexp_a_ks_or_b.dfa(), s_, true);
	CHECK(regexp_a_ks_or_b.dfa(), s_a, true);
	CHECK(regexp_a_ks_or_b.dfa(), s_b, true);
	CHECK(regexp_a_ks_or_b.dfa(), s_aa, true);
	CHECK(regexp_a_ks_or_b.dfa(), s_bb, false);
	CHECK(regexp_a_ks_or_b.dfa(), s_ab, false);
	CHECK(regexp_a_ks_or_b.dfa(), s_ba, false);

	RegExp<char> regexp_a_ks_or_b_ks;
	regexp_a_ks_or_b_ks.evaluate("a*|b*");	
	std::cout << "regexp_a_ks_or_b_ks:\n" << regexp_a_ks_or_b_ks.dfa() << std::endl;
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_a, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_b, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aa, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bb, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_ab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_ba, false);
	
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aaa, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_abb, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_baa, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bbb, true);

	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aaaa, true);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aaab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aaba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_aabb, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_abaa, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_abab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_abba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_abbb, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_baaa, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_baab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_baba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_babb, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bbaa, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bbab, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bbba, false);
	CHECK(regexp_a_ks_or_b_ks.dfa(), s_bbbb, true);


	RegExp<char> regexp_a_or_b_ks;
	regexp_a_or_b_ks.evaluate("(a|b)*");	
	std::cout << "regexp_a_ks_or_b_ks:\n" << regexp_a_ks_or_b_ks.dfa() << std::endl;
	CHECK(regexp_a_or_b_ks.dfa(), s_, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_a, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_b, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bb, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_ab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_ba, true);
	
	CHECK(regexp_a_or_b_ks.dfa(), s_aaa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_abb, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_baa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bbb, true);

	CHECK(regexp_a_or_b_ks.dfa(), s_aaaa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aaab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aaba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_aabb, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_abaa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_abab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_abba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_abbb, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_baaa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_baab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_baba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_babb, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bbaa, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bbab, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bbba, true);
	CHECK(regexp_a_or_b_ks.dfa(), s_bbbb, true);


	
}

void RegExpTest::test2()	{
	RegExp<char> regexp_n_a;
	regexp_n_a.evaluate("a!");	
	std::cout << "regexp1:\n" << regexp_n_a.dfa() << std::endl;
	CHECK(regexp_n_a.dfa(), s_, true);
	CHECK(regexp_n_a.dfa(), s_a, false);
	CHECK(regexp_n_a.dfa(), s_b, false);
	CHECK(regexp_n_a.dfa(), s_aa, false);
	CHECK(regexp_n_a.dfa(), s_bb, false);

/*
	RegExp<char> regexp_n_a_ks;
	regexp_n_a_ks.evaluate("a!|b");	
	std::cout << "regexp_a_kc:\n" << regexp_n_a_ks.dfa() << std::endl;
	CHECK(regexp_n_a_ks.dfa(), s_, false);
	CHECK(regexp_n_a_ks.dfa(), s_a, false);
	CHECK(regexp_n_a_ks.dfa(), s_b, true);
	CHECK(regexp_n_a_ks.dfa(), s_aa, false);
	CHECK(regexp_n_a_ks.dfa(), s_bb, false);
	CHECK(regexp_n_a_ks.dfa(), s_aba, false);
*/	

}

void RegExpTest::test3()
{
//	std::vector<std::string> tokens = {"CR", "LF", "Prepend", "L", "V", "LV", "LVT", "T", "Control", "Extend", "SpacingMark"}; 
	
	std::vector<std::string> tokens = {	"Other", 
										"CR", 
										"LF", 
										"Control", 
										"Extend", 
										"Prepend", 
										"SpacingMark", 
										"L", 
										"V", 
										"T", 
										"LV", 
										"LVT"
	};
	
/*
( CR LF )
| ( Prepend*
    ( L+ | (L* ( ( V | LV ) V* | LVT ) T*) | T+ | [^ Control CR LF ] )
    ( Extend | SpacingMark )*
   )
| .
*/

	std::string s = "(CR.LF)"		\
					"|(Prepend*."	\
					"(L+|(L*.((V|LV).(V*)|LVT).T*)|T+|(Other|SpacingMark|Prepend|Extend|LVT|LV|L|V|T))"  \
					".(Extend|SpacingMark)*" \
					")"
					"|(Other|SpacingMark|Prepend|Control|Extend|LVT|CR|LF|LV|L|V|T)"
	;

//	std::string s = "(V|LV).(V*)|LVT";		
		
	
	
//	std::string s = "L+|(L*.((V|LV).V*|LVT).T*)";
	
	RegExpWithTokens<char> reg_exp(tokens, 'a');
	//reg_exp.evaluate(exp.str());
	reg_exp.evaluate(s);
}
/*

WB1. 	sot 	÷ 	
WB2. 		÷ 	eot
WB3. 	CR 	× 	LF
WB3a. 	(Newline | CR | LF) 	÷ 	 
WB3b. 	  	÷ 	(Newline | CR | LF)
WB4. 	X (Extend | Format)* 	→ 	X
WB5. 	ALetter 	× 	ALetter
WB6. 	ALetter 	× 	(MidLetter | MidNumLet) ALetter
WB7. 	ALetter (MidLetter | MidNumLet) 	× 	ALetter
WB8. 	Numeric 	× 	Numeric
WB9. 	ALetter 	× 	Numeric
WB10. 	Numeric 	× 	ALetter
WB11. 	Numeric (MidNum | MidNumLet) 	× 	Numeric
WB12. 	Numeric 	× 	(MidNum | MidNumLet) Numeric
WB13. 	Katakana 	× 	Katakana
WB13a. 	(ALetter | Numeric | Katakana | ExtendNumLet) 	× 	ExtendNumLet
WB13b. 	ExtendNumLet 	× 	(ALetter | Numeric | Katakana)
WB14. 	Any 	÷ 	Any

 
*/

/*
ALetter.ALetter+.
ALetter.(MidLetter|MidNumLet).ALetter
ALetter.Numeric
Numeric.Numeric+
Numeric.(MidNum|MidNumLet).Numeric
Katakana.Katakana
(ALetter|Numeric|Katakana|ExtendNumLet).ExtendNumLet
ExtendNumLet.(ALetter|Numeric|Katakana)


(ALetter|Numeric|Katakana|ExtendNumLet).ExtendNumLet
ExtendNumLet.(ALetter|Numeric|Katakana)

(ALetter|Numeric|Katakana)ExtendNumLet+.(ALetter|Numeric|Katakana)

ALetter.ExtendNumLet+.ALetter
ALetter.ExtendNumLet+.Numeric
ALetter.ExtendNumLet+.Katakana

Numeric.ExtendNumLet+.ALetter
Numeric.ExtendNumLet+.Numeric
Numeric.ExtendNumLet+.Katakana

Katakana.ExtendNumLet+.ALetter
Katakana.ExtendNumLet+.Numeric
Katakana.ExtendNumLet+.Katakana

Katakana*.ExtendNumLet*.Katakana*



	(	
		(ALetter*|(ALetter+.(MidLetter|MidNumLet).ALetter+))|
		(Numeric*|(Numeric+.(MidNum|MidNumLet).Numeric+))
	)*
	|
	(Katakana*|(Katakana+.(ExtendNumLet*).Katakana+))
	

	((ALetter|Numeric)*.(ExtendNumLet+).(ALetter|Numeric)*)
	(Katakana+.(ExtendNumLet+).(ALetter+|Numeric+|Katakana+))*

--- version 2
(
	(	
		(ALetter*|(ALetter+.(MidLetter|MidNumLet).ALetter+))|
		(Numeric*|(Numeric+.(MidNum|MidNumLet).Numeric+))
	)*

	(Katakana*|(Katakana+.(ExtendNumLet*).Katakana+))
)*

-- version 3
(a*|c*)b+(a*|c*)

	(	
		(ALetter*|(ALetter+.(MidLetter|MidNumLet).ALetter+))|
		(Numeric*|(Numeric+.(MidNum|MidNumLet).Numeric+))
	)*
	|
	(
	(	
		(ALetter+|(ALetter+.(MidLetter|MidNumLet).ALetter+))|
		(Numeric+|(Numeric+.(MidNum|MidNumLet).Numeric+))
	)*
	|
	Katakana+)
		.ExtendNumLet+
	(	
		(ALetter+|(ALetter+.(MidLetter|MidNumLet).ALetter+))|
		(Numeric+|(Numeric+.(MidNum|MidNumLet).Numeric+))
	)*
	|
	Katakana+)
	
*/

	
void RegExpTest::test4()	{
	RegExp<char> regexp;
	regexp.evaluate("h+|(h*.((i|k).i*|l).j*)");	
//	regexp.evaluate("(i|k).i*|l)");	
//	regexp.evaluate("(i|k).i*");	
	std::cout << "regexp1:\n" << regexp.dfa() << std::endl;
	CHECK(regexp.dfa(), std::string(""), false);
	CHECK(regexp.dfa(), std::string("hhh"), true);
	CHECK(regexp.dfa(), std::string("iii"), true);
	CHECK(regexp.dfa(), std::string("h"), true);
	CHECK(regexp.dfa(), std::string("i"), true);
	CHECK(regexp.dfa(), std::string("k"), true);
	CHECK(regexp.dfa(), std::string("ij"), true);
	CHECK(regexp.dfa(), std::string("kj"), true);
	CHECK(regexp.dfa(), std::string("j"), false);
	CHECK(regexp.dfa(), std::string("hkj"), true);
	CHECK(regexp.dfa(), std::string("hij"), true);
	CHECK(regexp.dfa(), std::string("hilj"), false);
	CHECK(regexp.dfa(), std::string("hklj"), false);
	CHECK(regexp.dfa(), std::string("hkiiiiiij"), true);
	
}

enum class PV : unsigned char {
	Other, 
	CR, 
	LF, 
	Newline, 
	Extend, 
	Format, 
	Katakana, 
	ALetter, 
	MidLetter, 
	MidNum, 
	MidNumLet, 
	Numeric, 
	ExtendNumLet
};

struct TestData {
	std::string s;
	bool result;
};

void RegExpTest::word_segmentation_test()	{
	
	std::vector<std::string> tokens = {	
			"Other", 
			"CR", 
			"LF", 
			"Newline", 
			"Extend", 
			"Format", 
			"Katakana", 
			"ALetter", 
			"MidLetter", 
			"MidNum", 
			"MidNumLet", 
			"Numeric", 
			"ExtendNumLet"
		};		

// begin regular exp
	std::string Other_EF 		= "(Other.(Extend|Format)*)"; 
	std::string ALetter_EF 		= "(ALetter.(Extend|Format)*)"; 
	std::string Numeric_EF 		= "(Numeric.(Extend|Format)*)";
	std::string Katakana_EF  	= "(Katakana.(Extend|Format)*)";
	std::string ExtendNumLet_EF = "(ExtendNumLet.(Extend|Format)*)";
	std::string MidLetter_EF	= "(MidLetter.(Extend|Format)*)";
	std::string MidNumLet_EF	= "(MidNumLet.(Extend|Format)*)";
	std::string MidNum_EF 		= "(MidNum.(Extend|Format)*)";
	std::string MidLetter_MidNumLet_EF = "((MidLetter|MidNumLet).(Extend|Format)*)";
	std::string MidNum_MidNumLet_EF = "((MidNum|MidNumLet).(Extend|Format)*)";
	
//	std::string ALetter			= 	"(" + ALetter_EF + "+|(" + ALetter_EF + "+." + MidLetter_MidNumLet_EF + "." + ALetter_EF + "+))";
	std::string ALetter			= 	"((" + ALetter_EF + "|(" + ALetter_EF + "." + MidLetter_MidNumLet_EF + "." + ALetter_EF + "))+)";
	std::string Numeric			= 	"((" + Numeric_EF + "|(" + Numeric_EF + "+." + MidNum_MidNumLet_EF    + "." + Numeric_EF + "+))+)";
//	std::string Numeric			= 	"(" + Numeric_EF + "+|(" + Numeric_EF + "+." + MidNum_MidNumLet_EF + "." + Numeric_EF + "+))";

	std::string ALetter_Numeric =   	"((" + ALetter + "|" + Numeric + ")+)";

	//std::string Katakana = 			"((" + Katakana_EF + "+|" + ExtendNumLet_EF + "*)*)";
	//std::string Katakana = 				"(" + Katakana_EF + "+)";
	std::string Katakana_ExtendNumLet = "((" + Katakana_EF + "+|" + Katakana_EF + "+." + ExtendNumLet_EF + "+|" + ExtendNumLet_EF + "+." + Katakana_EF + "+)+)";
	std::string ALetter_Numeric_ExtendNumLet = "((" + ALetter_Numeric + "+|" + ALetter_Numeric + "+." + ExtendNumLet_EF + "+|" + ExtendNumLet_EF + "+." + ALetter_Numeric + "+)+)";

	std::string ExtendNumLet = "(" + ExtendNumLet_EF + "+)";

	std::string ALetter_Numeric_Katakana_1 =   "(" + ALetter_Numeric + "+." + ExtendNumLet_EF + "+." + Katakana_ExtendNumLet + "+)";
	std::string ALetter_Numeric_Katakana_2 =   "(" + Katakana_ExtendNumLet + "+." + ExtendNumLet_EF + "+." + ALetter_Numeric + "+)";

	std::stringstream ss;
//	ss << "("+ Other_EF + "|CR|LF|Newline|Extend|Format|Katakana|ALetter|" + MidLetter_EF + "|MidNum|" + MidNumLet_EF + "|Numeric|ExtendNumLet)";
	ss << "((Other|Extend|Format|Katakana|ALetter|MidLetter|MidNum|MidNumLet|Numeric|ExtendNumLet).(Extend|Format)*)";
	ss << "|(CR|LF|Newline)";
	ss << "|(CR.LF)";
	ss << "|((Extend|Format)*)";
	ss << "|" << ALetter_Numeric;
	ss << "|" << ALetter_Numeric_ExtendNumLet ;
	ss << "|" << Katakana_ExtendNumLet;
	ss << "|" << ALetter_Numeric_Katakana_1;
	ss << "|" << ALetter_Numeric_Katakana_2;
	ss << "|" << ExtendNumLet;
	ss << "|" << ALetter;
	
// end regular exp
	
	
	
	RegExpWithTokens<char> reg_exp(tokens, 'a');
	reg_exp.evaluate(ss.str());
	to_str(std::cout, reg_exp.dfa(), tokens, 'a');
	to_cpp(std::cout, reg_exp.dfa(), "word_states");

	std::string s0 = {};
	std::string s1 = {(char)PV::ALetter};
	std::string s2 = {(char)PV::ALetter, (char)PV::ALetter};
	std::string s3 = {(char)PV::ALetter, (char)PV::ALetter, (char)PV::ALetter};
	std::string s4 = {(char)PV::ALetter, (char)PV::Extend, (char)PV::ALetter, (char)PV::Numeric};
	std::string s5 = {(char)PV::Katakana};
	std::string s6 = {(char)PV::Katakana, (char)PV::Katakana};
	std::string s7 = {(char)PV::Katakana, (char)PV::Katakana, (char)PV::Katakana};
	
	std::string s8 = {(char)PV::Katakana, (char)PV::ExtendNumLet};
	std::string s9 = {(char)PV::Katakana, (char)PV::ExtendNumLet, (char)PV::ExtendNumLet, (char)PV::Katakana};
	std::string s10 = {(char)PV::Katakana, (char)PV::ExtendNumLet, (char)PV::Katakana, (char)PV::ExtendNumLet, (char)PV::Katakana};
	std::string s11 = {(char)PV::ExtendNumLet, (char)PV::Katakana, (char)PV::ExtendNumLet, (char)PV::Katakana};

	std::string s12 = {(char)PV::ALetter, (char)PV::Numeric, (char)PV::ALetter};
	std::string s13 = {(char)PV::ExtendNumLet};
	std::string s14 = {(char)PV::ExtendNumLet, (char)PV::ExtendNumLet};

	std::string s15 = {(char)PV::Katakana, (char)PV::ALetter};
	std::string s16 = {(char)PV::ALetter, (char)PV::Katakana};
	std::string s17 = {(char)PV::Katakana, (char)PV::Numeric};
	std::string s18 = {(char)PV::Numeric, (char)PV::Katakana};
	std::string s19 = {(char)PV::Other, (char)PV::Extend};
	std::string s20 = {(char)PV::MidNumLet, (char)PV::Format};
	std::string s21 = {(char)PV::ALetter, (char)PV::MidLetter, (char)PV::ALetter};

	
//	assert (check_aux(reg_exp.dfa(), s0, 'a')==false);
	assert (check_aux(reg_exp.dfa(), s1, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s2, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s3, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s4, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s5, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s6, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s7, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s8, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s9, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s10, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s11, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s12, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s13, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s14, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s15, 'a')==false);
	assert (check_aux(reg_exp.dfa(), s16, 'a')==false);
	assert (check_aux(reg_exp.dfa(), s17, 'a')==false);
	assert (check_aux(reg_exp.dfa(), s18, 'a')==false);
	assert (check_aux(reg_exp.dfa(), s19, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s20, 'a')==true);
	assert (check_aux(reg_exp.dfa(), s21, 'a')==true);
	
/*	check_aux(reg_exp.dfa(), , true};
	check_aux(reg_exp.dfa(), , true},
	check_aux(reg_exp.dfa(), std::string({(char)PV::ALetter, (char)PV::Extend, (char)PV::ALetter, (char)PV::Numeric}, true}
	*/	
	
//	std::string target = {(char)PV::ALetter, (char)PV::Extend, };
	std::string target = {(char)PV::ALetter, (char)PV::Extend, (char)PV::ALetter, (char)PV::Numeric};
//	std::string target = {(char)PV::ALetter, (char)PV::Numeric};
//	CHECK(reg_exp.dfa(), target, true);
	std::cout << "end test5 " << std::endl;
		
}

void RegExpTest::sentence_segmentation_test()	{
	
}


void RegExpTest::test5()
{
	RegExp<char> regexp;
	regexp.evaluate("a.((b.(c|d)*)*.(e.(c|d)*)*).f");	
	std::cout << "regexp:\n" << regexp.dfa() << std::endl;
	CHECK(regexp.dfa(), std::string("af"), true);
	CHECK(regexp.dfa(), std::string("abcf"), true);
	CHECK(regexp.dfa(), std::string("abef"), true);
	CHECK(regexp.dfa(), std::string("abecf"), true);


/*	regexp.evaluate("(b.(c|d)*)*.(e.(c|d)*)*");	
	std::cout << "regexp:\n" << regexp.dfa() << std::endl;
	CHECK(regexp.dfa(), std::string("b"), true);
	CHECK(regexp.dfa(), std::string("be"), true);
*/

/*	regexp.evaluate("(b.(c|d)*)*");	
	std::cout << "regexp:\n" << regexp.dfa() << std::endl;
	CHECK(regexp.dfa(), std::string("b"), true);
*/

/*	regexp.evaluate("b*");	
	std::cout << "regexp:\n" << regexp.dfa() << std::endl;
	CHECK(regexp.dfa(), std::string("b"), true);
*/

//	regexp.evaluate("(((l.(d|f)*).(((n.(d|f)*))*.((g.(d|f)*))*).(h.(d|f)*)))");	
//	regexp.evaluate("(((l.(d|f)*).(((n.(d|f)*)*).((g.(d|f)*)*)).(h.(d|f)*)))");	
//	regexp.evaluate("(((l.(d|f)*).((n.(d|f)*)*.(g.(d|f)*)*).(h.(d|f)*)))");	
//	regexp.evaluate("(l.(((n.(d|f)*))*.((g.(d|f)*))*).h)");	

//	regexp.evaluate("l.(((n.(d|f)*)*).((g.(d|f)*)*)).h");
//	regexp.evaluate("l.(((c*.d*))).h");

//	regexp.evaluate("((n.(d|f)*)*.(g.(d|f)*)*)");
//	std::cout << "regexp:\n" << regexp.dfa() << std::endl;
//	CHECK(regexp.dfa(), std::string("lh"), true);

/*	RegExp<char> regexp2;
	regexp2.evaluate("a.((n.(d|f)*)*.(g.(d|f)*)*).b");
	std::cout << "regexp2:\n" << regexp2.dfa() << std::endl;
*/
/*
	RegExp<char> regexp2;
//	regexp2.evaluate("a.((b.(e|f)*)*.(c.(e|f)*)*).d");
//	regexp2.evaluate("((b.(e|f)*)*.(c.(e|f)*)*)");
//	std::cout << "regexp2:\n" << regexp2.dfa() << std::endl;
//	regexp2.evaluate("a.((b.(e|f)*)*.(c.(e|f)*)*)");
//	std::cout << "regexp2:\n" << regexp2.dfa() << std::endl;

//	regexp2.evaluate("((b.(e|f)*)*.(c.(e|f)*)*).g");
	regexp2.evaluate("((b.(e|f)*)*.(c.(e|f)*)*.g");
	std::cout << "regexp2:\n" << regexp2.dfa() << std::endl;
	CHECK(regexp2.dfa(), std::string("g"), true);
*/

}


void RegExpTest::test6()	{
	RegExp<char> regexp;
	regexp.evaluate("a.a.b");
	std::cout << "test6 dfa:\n" << regexp.dfa() << std::endl;
	
	Nfa<char> nfa1 = to_nfa(regexp.dfa());
	std::cout << "test6 nfa1:\n" << nfa1 << std::endl;
	
	Nfa<char> nfa2 = nfa_reverse(nfa1);
	std::cout << "test6 nfa2:\n" << nfa2 << std::endl;

	Dfa<char> dfa2 = normalize(minimize(to_dfa(nfa2)));
	std::cout << "test6 dfa2:\n" << dfa2 << std::endl;
	
	CHECK(dfa2, s_, false);
	CHECK(dfa2, s_a, false);
	CHECK(dfa2, s_b, false);
	CHECK(dfa2, s_aa, false);
	CHECK(dfa2, s_bb, false);
	CHECK(dfa2, s_baa, true);


	

}
