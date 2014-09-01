/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#pragma once
#ifndef NFA_H
#define NFA_H

#include <map>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

template<typename CharT> 
class Nfa {

public:

	struct State	{
		
		State(int flag=0):flag(flag){}

		
		typedef std::multimap<CharT, size_t> Transitions;
		Transitions transitions;
		enum Kind {INITIAL=1, FINAL=2};
		int flag;
		void set_flag(int f){ flag = f;}
		
/*		bool equiv(const State& s)	{
			if (transitions.size()!=s.transitions.size())	{
				return false;
			}	
			for(auto it = transitions.begin();it!=transitions.end();++it)	{
				std::string state = s.transitions.find(it->first)->second;
				if (it->second != state)	{
					return false;
				}
				return true;
			}
		}
*/		
		void set_transitions(const Transitions& t)	{
			transitions = t;
		}

/*		void set_transitions(const std::initializer_list<std::pair<CharT, size_t> > t){
			transitions = Transitions(transitions.begin(), transitions.end());
		}
*/
		std::ostream& log (std::ostream& os, size_t index)const	{
			if (flag & INITIAL)	{
				os << "->";
			}else 	{
				os << "  ";				
			}
			os << 'S' << index << " "; 
			for(auto it=transitions.begin();it!=transitions.end();++it)	{
				os << it->first << "->S" << it->second << " ";
			}
			if (flag & FINAL)	{
				os << '+';
			}
			os << std::endl;
			return os;
		}
		
		inline bool initial() const	{
			return flag & INITIAL;
		}
		inline bool final()	const {
			return flag & FINAL;
		}
			
	};
	
	Nfa(size_t  size=0)
		:states(size)
	{}
	Nfa(const Nfa& nfa){
		for(size_t i=0;i!=nfa.states.size();++i)	{
			const State& state = nfa.states[i];
			typename State::Transitions transitions;
			for(auto it2=state.transitions.begin();it2!=state.transitions.end();++it2)	{
				typename State::Transitions::value_type v(it2->first, it2->second);
				transitions.insert(v);
			}
			set_state_info(i, transitions, state.flag);
			
		}	
	}
	
	std::vector<State> states;
	

	void set_state_info(const size_t id, const std::multimap<CharT, size_t>& transitions, const int flag=0)	{
		if (id >= states.size())	{
			//b
			states.resize(id+1, State());
		}
		
		states[id].set_transitions(transitions);   
		states[id].set_flag(flag);
	}

	void set_state_info(const size_t id, const std::initializer_list<std::pair<CharT, size_t>>& transitions, const int flag=0)	{
		set_state_info(id, typename State::Transitions(transitions.begin(), transitions.end()), flag);
	}


	std::set<size_t> get_final_states() const {
		std::set<size_t> result;
		for(size_t i=0;i<states.size();++i)	{
			
			if (states[i].final())	{
				//State const *  state = &it->second;
				result.insert(i);
			}
		}
		return result;
	}
	
	std::set<size_t> get_initial_states() const {
		std::set<size_t> result;
		for(size_t i=0;i<states.size();++i)	{
			
			if (states[i].initial())	{
				//State const *  state = &it->second;
				result.insert(i);
			}
		}
		return result;
	}
	
	State& get_state(const std::string& name)	{
		//return states[state];
		for(auto it=states.begin(); it!=states.end();++it )	{
			if (it->name == name)	{
				return *it;
			}
		}
		std::cout << "get_state() cant find " << name << std::endl;
		State state;
		state.name = name;
		states.push_back(state);
		return states.back();
	}
	
	const State& get_state(const std::string& name)const	{
		//return states[state];
		for(auto it=states.begin(); it!=states.end();++it )	{
			if (it->name == name)	{
				return *it;
			}
		}
		std::cout << "get_state() cant find " << name << std::endl;
		throw "State& get_state(std::string state)const	";
	}
	
/*	bool accept_null()	const {
		//for(auto state: get_initial_states()){
		auto ini_states = get_initial_states();
		for(size_t i=0;i!=ini_states.size();++i)	{
			//auto state = *it;
			if (states[i].initial() && states[i].final())	{
				return true;
			}
		}
		return false;
	}*/

	bool accept_null()	const {
		for(size_t i=0;i!=states.size();++i)	{
			if (states[i].initial() && states[i].final())	{
				return true;
			}
		}
		return false;
	}
	
	void clear()	{
		states.clear();
	}
	
	std::set<CharT> input()	const {
		std::set<CharT> input_aux;
		for(size_t i=0;i<states.size();++i)	{			
			const typename State::Transitions& transitions = states[i].transitions;	
			for(auto it = transitions.begin();it!=transitions.end();++it)	{				
				input_aux.insert(it->first);
			}
		}
		return input_aux;
		
	}
};



template <typename CharT>	
class Concatenator	{
	typedef typename Nfa<CharT>::State State;
	typedef typename Nfa<CharT>::State::Transitions Transitions;
	const Nfa<CharT>& _nfa1;
	const Nfa<CharT>& _nfa2;
	Nfa<CharT>& _result;
public:
	Concatenator(const Nfa<CharT>& nfa1, const Nfa<CharT>& nfa2, Nfa<CharT>& result):_nfa1(nfa1),_nfa2(nfa2),_result(result)	{
		std::set<size_t> initial_states = _nfa1.get_initial_states();
	}
	
	Nfa<CharT>& result(){ return _result;}
	
	void exec()	{
		_result = _nfa1;
		std::set<size_t> nfa1_final_states = _nfa1.get_final_states();
		std::set<size_t> nfa2_initial_states = _nfa2.get_initial_states();
		size_t first = _result.states.size();
		for(State& state: _result.states)	{
			state.flag &= ~State::FINAL;
			//state.set_final(false);
			
		}
		for(size_t id_state=0; id_state<_nfa1.states.size();++id_state)	{
			const State& state = _nfa1.states[id_state];
			for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
				if (nfa1_final_states.find(it_trans->second)!=nfa1_final_states.end())	{
					for(auto it_ini_st=nfa2_initial_states.begin();it_ini_st!=nfa2_initial_states.end();++it_ini_st)	{
						typename State::Transitions::value_type value(it_trans->first, *it_ini_st + first);
						
						_result.states[id_state].transitions.insert(value);
					}
					//nfa2_initial_states
				}
			}
		}
		bool nfa1_accepts_nulls = _nfa1.accept_null();
		for(size_t ind_state=0;ind_state!=_nfa2.states.size();++ind_state)	{
			const State& state = _nfa2.states[ind_state];
			Transitions new_transitions;
			for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
				typename Transitions::value_type v(it_trans->first, it_trans->second + first);
				new_transitions.insert(v);
			}
			int flag = 0;
//			std::cout << "Concatenator::exec() nfa1_accepts_nulls : " << nfa1_accepts_nulls  << std::endl;
//			std::cout << "Concatenator::exec() state.initial() : " << state.initial()  << std::endl;
//			std::cout << "Concatenator::exec() state.final() : " << state.final()  << std::endl;
			
			if (nfa1_accepts_nulls && state.initial())	{
				flag |= State::INITIAL;
			}
			if (state.final())	{
				flag |= State::FINAL;
			}
//			std::cout << "Concatenator::exec() flag: " << flag << std::endl;
			_result.set_state_info(ind_state + first, new_transitions, flag);
		}
		
		
	}
};

template<typename CharT>
void concat(const Nfa<CharT>& dfa1, const Nfa<CharT>& dfa2, Nfa<CharT>& result)	{
	Concatenator<CharT> c(dfa1, dfa2, result);
	c.exec();
	//return c.result;
}

template<typename CharT>
Nfa<CharT> concat(const Nfa<CharT>& nfa1, const Nfa<CharT>& nfa2)	{
	Nfa<CharT> result;
	Concatenator<CharT> c(nfa1, nfa2, result);
	c.exec();
	return result;
}



template <typename CharT>	
class KleeneCross	{
	typedef typename Nfa<CharT>::State State;
	typedef typename Nfa<CharT>::State::Transitions Transitions;
	const Nfa<CharT>& _nfa1;
	Nfa<CharT>& _result;
public:
	KleeneCross(const Nfa<CharT>& nfa1, Nfa<CharT>& result):_nfa1(nfa1),_result(result)	{
		std::set<size_t> initial_states = _nfa1.get_initial_states();
	}
	
	Nfa<CharT>& result(){ return _result;}
	
	void exec()	{
		_result = _nfa1;
		std::set<size_t> final_states = _nfa1.get_final_states();
		std::set<size_t> initial_states = _nfa1.get_initial_states();

/*		for(State& state: _result.states)	{
			state.flag &= ~State::FINAL;
			//state.set_final(false);
		}*/
		
		for(size_t id_state=0; id_state<_nfa1.states.size();++id_state)	{
			const State& state = _nfa1.states[id_state];
			for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
				if (final_states.find(it_trans->second)!=final_states.end())	{
					for(auto it_ini_st=initial_states.begin();it_ini_st!=initial_states.end();++it_ini_st)	{
						typename State::Transitions::value_type value(it_trans->first, *it_ini_st);
						
						_result.states[id_state].transitions.insert(value);
					}
					//nfa2_initial_states
				}
			}
		}
/*		
		bool nfa1_accepts_nulls = _nfa1.accept_null();
		for(size_t ind_state=0;ind_state!=_nfa1.states.size();++ind_state)	{
			const State& state = _nfa2.states[ind_state];
			Transitions new_transitions;
			for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
				typename Transitions::value_type v(it_trans->first, it_trans->second + first);
				new_transitions.insert(v);
			}
			int flag = 0;
			if (nfa1_accepts_nulls && state.initial())	{
				flag |= State::INITIAL;
			}
			if (state.final())	{
				flag |= State::FINAL;
			}
			_result.set_state_info(ind_state + first, new_transitions, flag);
		}
*/		
		
	}
};

template<typename CharT>
Nfa<CharT> kleene_cross(const Nfa<CharT>& nfa1)	{
	Nfa<CharT> result;
	KleeneCross<CharT> c(nfa1, result);
	c.exec();
	return result;
}

template<typename CharT>
Nfa<CharT> kleene_star(const Nfa<CharT>& nfa1)	{
	Nfa<CharT> result;
	KleeneCross<CharT> c(nfa1, result);
	c.exec();
	Nfa<CharT> nfa_null;
	nfa_null.set_state_info(0, {}, Nfa<CharT>::State::INITIAL|Nfa<CharT>::State::FINAL);
	result = nfa_union(nfa_null, result);
	return result;
}


template<typename CharT>
Nfa<CharT> nfa_not(const Nfa<CharT>& nfa1)	{
	typedef Nfa<CharT> _Nfa;
	typedef typename Nfa<CharT>::State _State;
	_Nfa result(nfa1);
	for(_State& state: result.states)	{
		if (state.flag & _State::FINAL)	{
			state.flag &= ~_State::FINAL;
		}else	{
			state.flag |= _State::FINAL;			
		}
	}
	return result;
}

/*
template<typename CharT>
Nfa<CharT> nfa_one_char(const Nfa<CharT>& nfa1)	{
	typedef Nfa<CharT> _Nfa;
	typedef typename Nfa<CharT>::State _State;
	_Nfa result(nfa1);
	Nfa<CharT> nfa_null;
	nfa_null.set_state_info(0, {}, Nfa<CharT>::State::INITIAL|Nfa<CharT>::State::FINAL);
	result = nfa_union(nfa_null, result);
	
	return result;
}
*/

template<typename CharT>
Nfa<CharT> nfa_union(const Nfa<CharT>& nfa1, const Nfa<CharT>& nfa2)	{
	typedef typename Nfa<CharT>::State _State;
	typedef typename Nfa<CharT>::State::Transitions _Transitions;
	
	Nfa<CharT> result(nfa1.states.size()+nfa2.states.size());
	for(size_t ind_state=0;ind_state!=nfa1.states.size();++ind_state)	{
		const _State& state = nfa1.states[ind_state];
		_Transitions new_transitions;
		for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
			typename _Transitions::value_type v(it_trans->first, it_trans->second);
			new_transitions.insert(v);
		}
		int flag = 0;
		if (state.initial())	{
			flag |= _State::INITIAL;
		}
		if (state.final())	{
			flag |= _State::FINAL;
		}
		result.set_state_info(ind_state, new_transitions, flag);
	}
	for(size_t ind_state=0;ind_state!=nfa2.states.size();++ind_state)	{
		const _State& state = nfa2.states[ind_state];
		_Transitions new_transitions;
		for(auto it_trans=state.transitions.begin();it_trans!=state.transitions.end();++it_trans)	{
			typename _Transitions::value_type v(it_trans->first, it_trans->second+nfa1.states.size());
			new_transitions.insert(v);
		}
		int flag = 0;
		if (state.initial())	{
			flag |= _State::INITIAL;
		}
		if (state.final())	{
			flag |= _State::FINAL;
		}
		result.set_state_info(ind_state + nfa1.states.size(), new_transitions, flag);
	}
		

	return result;
}

template<typename CharT>
Nfa<CharT> nfa_reverse(const Nfa<CharT>& nfa)	{
	typedef typename Nfa<CharT>::State _State;
	Nfa<CharT> result(nfa.states.size());
	
	for(size_t i=0; i!=nfa.states.size();++i)	{
		const _State& state = nfa.states[i];
		for(auto it_trans = state.transitions.begin(); it_trans!= state.transitions.end();++it_trans)	{
			std::pair<CharT, size_t> transition(it_trans->first, i);
			result.states[it_trans->second].transitions.insert(transition);
		}
		
		int flag=0;
		if (state.final())	{				
			flag = flag | _State::INITIAL;
		}
		if (state.initial())	{				
			flag = flag | _State::FINAL;
		}
		result.states[i].set_flag(flag);
		
	}
	
	return result;
}

template<typename CharT>
std::ostream& operator<<(std::ostream& os, const Nfa<CharT>& dfa)	{
	for(size_t i=0;i<dfa.states.size();++i)	{
		dfa.states[i].log(os, i);
	}
	os << std::endl;
	return os; 
}



#endif // NFA_H
