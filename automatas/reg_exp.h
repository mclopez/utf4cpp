/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef REGEXP_H
#define REGEXP_H

#include <string>
#include <stack>
#include <queue>

#include "nfa.h"
#include "dfa.h"

// kleene star
// klenne cross
// question mark
// concatenation

//#define DEBUG_LOG

  
template<typename CharT>
class RegExp {

	typedef std::basic_string<CharT> _string;
	typedef typename std::basic_string<CharT>::const_iterator _iterator;
	typedef Nfa<CharT> _Nfa;
	typedef Dfa<CharT> _Dfa;

	
	bool is_operator(const CharT& c);
	int priority(char c);
	
//	std::queue<_Nfa> operands;
//	std::queue<CharT> operators;

	struct Operator {
		Operator(char op, int pri):op(op), priority(pri){}
		char op;
		int priority;
	};
	
	int parenthesis_level;
	std::stack<Operator> stack;
	std::stack<_Nfa> operands;

	_Dfa result;
	_Nfa create_nfa(CharT c);
	
	void eval_concat();
	void eval_kleene_star();
	void eval_kleene_cross();
	void eval_or();
	void eval_not();
	void eval_one_char();

	void exec_operator(CharT op);
	
public:
	RegExp();
	~RegExp();

	void evaluate(const _string& s);
	void evaluate_reverse(const _string& s);
	const _Dfa& dfa(){return result;}

};

template<typename CharT>
class RegExpWithTokens {
	typedef std::basic_string<CharT> _string;
	typedef typename std::pair<_string, size_t> _pair;
	typedef std::vector<_pair> _ordered_tokens_cont;
	
	std::vector<_string> _tokens;
	_ordered_tokens_cont _tokens_ordered_by_size;
	RegExp<CharT> reg_exp;
	CharT _first_char;
	
	struct Comparator {
		bool operator() (const _pair& i,const _pair& j) { return (i.first.size()>j.first.size());}
	};
	
public:
	
	RegExpWithTokens(const std::vector<_string>& tokens, CharT first_char ):_tokens(tokens), _first_char(first_char)	{
		for(size_t i=0;i<_tokens.size();++i)	{
			_tokens_ordered_by_size.push_back(_pair(_tokens[i], i));
		}
		
		Comparator c;
		std::sort(_tokens_ordered_by_size.begin(), _tokens_ordered_by_size.end(), c);
#ifdef DEBUG_LOG		
		std::cout << "RegExpWithTokens::RegExpWithTokens()\n";
		for(std::string& s: _tokens)	{
			std::cout << s << '\n'; 
		}
		for(_pair& p: _tokens_ordered_by_size)	{
			std::cout << p.first << ' ' << p.second <<  ' ' << char(_first_char + p.second) << '\n'; 
		}
#endif		
	}
	
	void evaluate(const _string& s)	{
#ifdef DEBUG_LOG		
		std::cout << "RegExpWithTokens::evaluate()\n";
		std::cout << "s: " << s << " size: " << s.size() << '\n';
#endif		
		std::string s_new = s;
/*		size_t pos = s_new.find("CR");
		std::cout << "pos: " << pos << '\n';
		s_new.replace(pos, 2, std::string("x"));
		//s_new = s_new.replace(pos, 2, "xx", 2);*/
		for(_pair& p: _tokens_ordered_by_size)	{
#ifdef DEBUG_LOG		
			std::cout << p.first << ' ' << p.second <<  ' ' << char(_first_char + p.second) << '\n'; 
#endif
			size_t pos = s_new.find(p.first);
			std::stringstream ss;
			ss << CharT(_first_char + p.second);
			while (pos !=_string::npos)	{
				s_new = s_new.replace(pos, p.first.size(), ss.str());
				pos = s_new.find(p.first);
			}
		}
		
		
#ifdef DEBUG_LOG		
		std::cout << "s_new : " << s_new << " size: " << s_new.size() <<'\n';
#endif
		reg_exp.evaluate(s_new);	
#ifdef DEBUG_LOG		
		std::cout << "reg_exp.dfa() : \n" << reg_exp.dfa() << '\n';
		to_cpp(std::cout, reg_exp.dfa(), "grapheme_states");
		to_str(std::cout, reg_exp.dfa(), _tokens, 'a');
#endif		
		
	}
	const Dfa<CharT>& dfa(){ return reg_exp.dfa();}
};

#endif // REGEXP_H
