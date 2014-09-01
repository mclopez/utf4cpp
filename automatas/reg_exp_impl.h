/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef REGEXP_IMPL_H
#define REGEXP_IMPL_H

#include <cassert>
#include "reg_exp.h"
#include <string>

template<typename CharT>
RegExp<CharT>::RegExp()
{
}

template<typename CharT>
RegExp<CharT>::~RegExp()
{
}

template<typename CharT>	
Nfa<CharT> RegExp<CharT>::create_nfa(CharT c)	{
	const size_t state_A = 0;
	const size_t state_B = 1;

	_Nfa nfa_c(2);
	nfa_c.set_state_info(state_A, {{c, state_B}}, _Nfa::State::INITIAL);
	nfa_c.set_state_info(state_B, {}, _Nfa::State::FINAL);
	return nfa_c;
}

template<typename CharT>
void RegExp<CharT>::eval_concat()	{
//	std::cout << "RegExp<CharT>::eval_concat()\n";
	_Nfa op1 = operands.top();
//	std::cout << "op1: \n"  << op1;
	operands.pop();
	_Nfa op2 = operands.top();
//	std::cout << "op2: \n"  << op2;
	operands.pop();
	_Nfa r = concat(op2, op1);
//	std::cout << "r: \n"  << r;
/*	std::cout << "r2: \n"  << to_dfa(r);
	std::cout << "r3: \n"  << minimize(to_dfa(r));
	std::cout << "r4: \n"  << normalize(minimize(to_dfa(r)));
*/	
	operands.push(r);	
}

template<typename CharT>
void RegExp<CharT>::eval_kleene_cross()	{
//	std::cout << "RegExp<CharT>::eval_kleene_cross()\n";
	_Nfa op1 = operands.top();
//	std::cout << "op1: \n"  << op1;
	operands.pop();
	
	_Nfa r = kleene_cross(op1);
//	std::cout << "r: \n"  << r;
	operands.push(r);	
}

template<typename CharT>
void RegExp<CharT>::eval_kleene_star()	{
//	std::cout << "RegExp<CharT>::eval_kleene_star()\n";
	_Nfa op1 = operands.top();
//	std::cout << "op1: \n"  << op1;
	operands.pop();
	_Nfa r = kleene_star(op1);
	
//	std::cout << "r: \n"  << r;
	operands.push(r);	
}

template<typename CharT>
void RegExp<CharT>::eval_not()	{
//	std::cout << "RegExp<CharT>::eval_not()\n";
	_Nfa op1 = operands.top();
//	std::cout << "op1: \n"  << op1;
	operands.pop();
	_Nfa r = nfa_not(op1);
	
//	std::cout << "r: \n"  << r;
	operands.push(r);	
}

/*
template<typename CharT>
void RegExp<CharT>::eval_one_char()	{
	std::cout << "RegExp<CharT>::eval_one_char()\n";
	_Nfa op1 = operands.top();
	std::cout << "op1: \n"  << op1;
	operands.pop();
	_Nfa r = v2::nfa_one_char(op1);
	
	std::cout << "r: \n"  << r;
	operands.push(r);	
}
*/

template<typename CharT>
void RegExp<CharT>::eval_or()	{
//	std::cout << "RegExp<CharT>::eval_or()\n";
	_Nfa op1 = operands.top();
//	std::cout << "op1: \n"  << op1;
	operands.pop();
	_Nfa op2 = operands.top();
//	std::cout << "op2: \n"  << op2;
	operands.pop();
	_Nfa r = nfa_union(op1, op2);
//	std::cout << "r: \n"  << r;
	operands.push(r);	
}

/*
template<typename CharT>
void  RegExp<CharT>::evaluate(const _string& s)	{
	std::cout << "RegExp<CharT>::evaluate() " << s << std::endl; 
//	operators.emplace();
//	operands.emplace();
	for(auto it = s.begin();it!=s.end();++it)	{
		if (is_operator(it))	{
			operators.push(*it);
		}else	{
			operands.push(create_nfa(*it));
		}
	}
	
	//for(auto it=operators.rbegin();it!=operators.rend();++it)	{
	while (!operators.empty())	{
		
		CharT c = operators.front();
		operators.pop();
		switch(c)	{
			case '.':
				eval_concat();
				break;
			case '*':
				eval_kleene_star();
				
				break;
			case '+':
				eval_kleene_cross();
				
				break;
			case '?':
				//eval_question_mark();
				break;
			case '(':
				//eval_open_parentheses();			
				break;
			case ')':
				//eval_close_parentheses();			
				break;
			default:
				break;
		} 
		
	}
	_Nfa nfa_aux = operands.front();
	std::cout << "nfa_aux:\n" <<  nfa_aux << std::endl;
	
	//_Dfa dfa_aux;  
	//to_dfa(nfa_aux, dfa_aux );	
	//result = dfa_aux;
	
	//std::cout << "dfa_aux\n" << dfa_aux << std::endl;
	//minimize(dfa_aux, result);
	//std::cout << "result\n" << result << std::endl;
	
	//minimize(dfa_aux, result);
	_Dfa dfa_result = to_dfa(nfa_aux);
	std::cout << "dfa_result:\n" <<  dfa_result;
	result = normalize(minimize(dfa_result));
//	std::cout << "result:\n" <<  operands.top();
//	std::cout << "result:\n" <<  v2::normalize(v2::minimize(v2::to_dfa(operands.top())));
	std::cout << "result:\n" <<  result;
//	result = v2::normalize(v2::minimize(v2::to_dfa(operands[0])));
}
*/

template<typename CharT>
bool RegExp<CharT>::is_operator(const CharT& c)	{
	switch(c)	{
		case '.': 
		case '*': 
		case '+': 
		case '(': 
		case ')': 
		case '|':
		case '!':
//		case '_':
			return true;
		default:
			return false;
	}
}

template<typename CharT>
void RegExp<CharT>::exec_operator(CharT op)	{
		switch(op)	{
			case '.':
				eval_concat();
				break;
			case '*':
				eval_kleene_star();				
				break;
			case '+':
				eval_kleene_cross();
				break;
			case '!':
				eval_not();				
				break;
/*			case '_':
				eval_one_char();				
				break;*/
			case '?':
				//eval_question_mark();
				break;
			case '|':
				eval_or();			
				break;
			default:
				break;
		}	
}

template<typename CharT>
int RegExp<CharT>::priority(char c)	{
		switch(c)	{
			case '|':
				return 0 + parenthesis_level*3;
			case '.':
				return 1 + parenthesis_level*3;
			case '*':
			case '+':
			case '!':
				return 2 + parenthesis_level*3;
			
//			case '(':
//			case ')':
//				return 2 + parenthesis_level*3;
		default:
			abort();
		}
	}

template<typename CharT>
void  RegExp<CharT>::evaluate(const _string& s)	{
//		std::string post_fix;
		parenthesis_level =0;
		for(const CharT& c: s)	{
			if (is_operator(c))	{
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
							//post_fix.push_back(stack.top().op); 
							exec_operator(stack.top().op);
							stack.pop();
						}
						stack.push(op);
					}
				}
			} else {
				// character
				//post_fix.push_back(c);
				operands.push(create_nfa(c));
			}
		}
		while (!stack.empty())	{
			//std::cout << "top: " << stack.top() << std::endl;
//			post_fix.push_back(stack.top().op); 
			exec_operator(stack.top().op);
			stack.pop();
		}
		//return post_fix;
		//std::cout << "to_dfa:\n" << v2::to_dfa(operands.top()) << std::endl;
		result = normalize(minimize(to_dfa(operands.top())));
		assert(parenthesis_level==0);
	}

#endif // REGEXP_IMPL_H
