/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef DFA_H
#define DFA_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept> 

#include "nfa.h"



template <typename V>
std::ostream& operator<<(std::ostream& os, const std::set<V>& t);

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K,V>& t);

template <typename CharT>
struct Dfa {

	public:


	struct State	{
	private :
	public:
		State():_final(false){};
		State(bool final):
		_final(final){}
		
		State(const State& st):
			_final(st._final), 
			transitions(st.transitions){			
		} 
		State(const State&& st):
			_final(st._final), 
			transitions(st.transitions){			
		} 
		
		void operator=(const State& st)	{
			_final=st._final;
		}
				
		typedef std::map<CharT, size_t> Transitions;
		bool _final;
		Transitions transitions;
		void set_final(bool final)	{ _final = final;}
		bool final() const { return _final;}
		
		bool equiv(const State& s)	{
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

		void set_transitions(const Transitions& t){
			transitions = t;
		}
		void set_transitions(const std::initializer_list<std::pair<CharT, size_t> > t){
			transitions = Transitions(t.begin(), t.end());
		}
		


		std::ostream& log (std::ostream& os, size_t index)const	{
			os << "S" << index << " "; 
			for(auto it=transitions.begin();it!=transitions.end();++it)	{
				os << it->first << "->" << "S" << it->second << " ";
			}
			if (_final)	{
				os << '+';
			}
			os << std::endl;
			return os;
		}

		const size_t next(CharT c) const	{
			auto it = transitions.find(c);
			if (it!=transitions.end())	{
				return it->second;
			}
			//std::string s = "invalid char:";
			//throw std::logic_error( s + c);
			return std::numeric_limits<size_t>::max();
		}
			
	};
	
//	std::map<std::string, std::map<CharT, std::string> > states;
public:
	
	typedef std::vector<State> States;
	State OTHER; 
	
	States states;
	size_t _initial_state;
	
	Dfa(size_t num_states=0)
	{
		//initial_state = 0;//states.end();
		states.resize(num_states);
		_initial_state = 0;
	}
	
//	Dfa(const Dfa&& dfa)=delete;
	Dfa(const Dfa&& dfa)	{
		states = std::move(dfa.states);
		_initial_state = dfa._initial_state;
		
	}
	
	Dfa(const Dfa& dfa) {
		states = dfa.states;
		_initial_state = dfa._initial_state;
	}

	void operator=(const Dfa&& dfa)	{
		states = std::move(dfa.states);
		_initial_state = dfa._initial_state;
		
	}
	void operator=(const Dfa& dfa)	{
		states = std::move(dfa.states);
		_initial_state = dfa._initial_state;
		
	}
	
	
	~Dfa(){}


	void set_state_info(const size_t id, const std::map<CharT, size_t>& transitions, bool final=false)	{
		if (id >= states.size())	{
			//b
			states.resize(id+1);
		}
		
		states[id].set_transitions(transitions);   
		states[id].set_final(final);
	}

	void set_state_info(const size_t id, const std::initializer_list<std::pair<CharT, size_t>>& transitions, bool final=false)	{
//		typename State::Transitions trs = typename State::Transitions(transitions.begin(), transitions.end());
		set_state_info(id, typename State::Transitions(transitions.begin(), transitions.end()), final);
	}
	size_t initial_state()	const { return _initial_state;}
	void set_initial_state(size_t is)	{ _initial_state = is;}
	

	std::ostream& operator<<(std::ostream& os)	{
		for(auto it=states.begin();it!=states.end();++it)	{
			os << *it;	
		}
		os << std::endl;
		return os; 
	}

	
};



template<typename CharT>
bool check(const Dfa<CharT>& dfa, const std::basic_string<CharT>& s)	{
//	int i =0;
	if (dfa.states.empty())	{
		return false;
	}
	const typename Dfa<CharT>::State* _state = &dfa.states[dfa._initial_state];
	for(auto it=s.begin();it!=s.end();++it)	{
//		std::cout << "check()" << ++i << std::endl;
		size_t index = _state->next(*it);
		if (index!=std::numeric_limits<size_t>::max())	{
			_state = &dfa.states[index]; 	
		}else	{
			_state = &dfa.OTHER; 	
		}
//		std::cout << "check()" << index << std::endl;
	}
	return _state->_final;
}

template<typename CharT>
bool check_aux(const Dfa<CharT>& dfa, const std::basic_string<CharT>& s, CharT char_aux)	{
//	int i =0;
	if (dfa.states.empty())	{
		return false;
	}
	const typename Dfa<CharT>::State* _state = &dfa.states[dfa._initial_state];
	for(auto it=s.begin();it!=s.end();++it)	{
//		std::cout << "check()" << ++i << std::endl;
		size_t index = _state->next(*it+char_aux);
		if (index!=std::numeric_limits<size_t>::max())	{
			_state = &dfa.states[index]; 	
		}else	{
			_state = &dfa.OTHER; 	
		}
//		std::cout << "check()" << index << std::endl;
	}
	return _state->_final;
}


template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K,V>& t)	{
	os << "[ ";
	bool first =true;
	for(typename std::map<K,V>::const_iterator it=t.begin();it!=t.end();++it)	{
		if (!first) 	{
			 os << ", ";
		}
		first = false;
		os << it->first << " -> " << it->second;
	}
	os << " ]";
	return os;
}

template <typename V>
std::ostream& operator<<(std::ostream& os, const std::set<V>& t)	{
	os << "[ ";
	bool first =true;
	for(typename std::set<V>::const_iterator it=t.begin();it!=t.end();++it)	{
		if (!first) 	{
			 os << ", ";
		}		
		first = false;
		os << *it;
	}
	os << " ]";
	return os;
}



template<typename CharT>
std::ostream& operator<<(std::ostream& os, const Dfa<CharT>& dfa)	{
	
	for(size_t i = 0;i<dfa.states.size();++i)	{
		if (dfa.initial_state()==i)	{
			os << "->";
		} else	{
			os << "  ";
		}
		dfa.states[i].log(os, i);
	}
	os << std::endl;
	return os; 
}


template <typename CharT>
void to_cpp(std::ostream& os, const Dfa<CharT>& dfa, const std::string& var_name) {
	typedef typename Dfa<CharT>::State  _State;
	bool first_s = true;
	
	size_t state_length = dfa.states[0].transitions.size()+1;
	os << "static const size_t " << var_name << "_length = " << state_length << ";\n";
	os << "static const int " << var_name << "[]["<< state_length << "] { \n";

	size_t pit_state = -1;
	for (size_t indx=0;indx!=dfa.states.size();indx++)	{
		const _State& state = dfa.states[indx];
		os << "{";
		bool first_t = true;
		bool maybe_pit_state = true;
		
		for(auto it=state.transitions.begin();it!=state.transitions.end();++it)	{
			if (!first_t)	{
				os << ", ";
			}
			os << it->second;
			first_t = false;
			if (maybe_pit_state && it->second!=indx)	{
				maybe_pit_state = false;
			}
		}
		if (maybe_pit_state)	{
			pit_state = indx;
		}
		if (state._final)	{
			os << ", 1";
		}else	{
			os << ", 0";
		}
		
		os << "}";
		if (first_s)	{
			os << ',';
		}
		os << "\n";
		
	}
	os << "};" << std::endl;
	
	os << "static const size_t " << var_name << "_pit_state = " << pit_state << ";" << std::endl;
	
	
	
}

template <typename CharT>
void to_table(const Dfa<CharT>& dfa, int*& states_table, int& state_length, int& num_states) {
	typedef typename Dfa<CharT>::State  _State;
	bool first_s = true;
	state_length = dfa.states[0].transitions.size()+1;
	
	int *states = new int[(state_length) * dfa.states.size()];
	
	size_t pos = 0;
	
	for (const _State& state: dfa.states)	{
		for(auto it=state.transitions.begin();it!=state.transitions.end();++it)	{
			states[pos++] = it->second;
		}
		if (state._final)	{
			states[pos++] = 1;
		}else	{
			states[pos++] = 0;
		}
	}
	states_table = states;
	num_states = dfa.states.size();
}

template<typename CharT>
void to_str(std::ostream& os, const Dfa<CharT>& dfa, const std::vector<std::string>& tokens, CharT first_char)	{
	
	for(size_t i = 0;i<dfa.states.size();++i)	{
		if (dfa.initial_state()==i)	{
			os << "->";
		} else	{
			os << "  ";
		}
		//dfa.states[i].log(os, i);
		
		os << "S" << i << " "; 
		const typename Dfa<CharT>::State::Transitions& trans = dfa.states[i].transitions;
		for(auto it=trans.begin();it!=trans.end();++it)	{
			os << tokens[it->first-first_char] << "->" << "S" << it->second << " ";
		}
		if (dfa.states[i]._final)	{
			os << '+';
		}
		os << std::endl;
		
	}
	os << std::endl;
}


template<typename CharT>	
class Converter{
	typedef std::set<size_t> StateSet;
	typedef std::map<CharT, size_t> Transitions;	
	typedef std::map<CharT, StateSet> TransitionsAux;	
	
	const Nfa<CharT>& nfa;
	Dfa<CharT>& dfa;
	std::map<StateSet, size_t> new_states_to_state;
	std::set<StateSet> states_done;
	std::set<CharT> input;

	size_t translate(const StateSet& states)	{
		auto it_aux = new_states_to_state.find(states);
		if (it_aux==new_states_to_state.end())	{
			size_t dfa_state = new_states_to_state.size();
			new_states_to_state[states] = dfa_state;
			return dfa_state;
		}else	{
			return it_aux->second;
		}
	}
	
	void convert(const StateSet& nfa_states){
		using namespace std;
		//cout << endl;
		//cout << "converting nfa_states: " << nfa_states << endl;
		TransitionsAux new_trans_aux;
		
		for(auto it_char=input.begin();it_char!=input.end();++it_char)	{
			// inicialization of empty state set for every character
			new_trans_aux[*it_char] = StateSet();	
		}
		for(auto it=nfa_states.begin();it!=nfa_states.end();++it)	{
			const typename Nfa<CharT>::State& nfa_state = nfa.states[*it];
			for(auto it2=nfa_state.transitions.begin();it2!=nfa_state.transitions.end();++it2)	{
				//cout << " trans: " << it2->first << " "<< endl << it2->second << endl;
				new_trans_aux[it2->first].insert(it2->second);	
			}				
		}
		//cout << "new_trans_aux: " << new_trans_aux << endl;
		bool final = false;
		for(auto it=nfa_states.begin();it!=nfa_states.end();++it)	{
			const typename Nfa<CharT>::State& state = nfa.states[*it]; 
			if (state.final())	{
				final = true;
				break;
			}
		}
		size_t dfa_state = translate(nfa_states);
		Transitions new_transitions;
		for (auto it=new_trans_aux.begin();it!=new_trans_aux.end();++it)	{
			//size_t state = new_states_to_state[it->second];
			size_t state = translate(it->second); 
			new_transitions[it->first] = state;
		}
		
		//cout << "dfa_state: " << dfa_state << " new_transitions: " << new_transitions << endl;
		dfa.set_state_info(dfa_state, new_transitions, final);				
		//cout << "dfa: " << dfa << endl;
		
		
		states_done.insert(nfa_states);
		
		//cout << "new_states_to_state: " << new_states_to_state << endl;
		for(auto it=new_trans_aux.begin();it!=new_trans_aux.end();++it)	{
			//if (dfa.states.find(new_name(it->second))==dfa.states.end())	{
			if (states_done.find(it->second)==states_done.end())	{
				convert(it->second);
			}else {
				//cout << "convert: State end" << endl;
			}
		}
		
			
	}


public:

	Converter(const Nfa<CharT>& nfa, Dfa<CharT>& dfa):nfa(nfa), dfa(dfa)	{
		input = nfa.input();
	}
	
	void exec(){
		convert(nfa.get_initial_states());
	}
	
	
	
};


template <typename CharT>
Dfa<CharT> to_dfa(const Nfa<CharT>& nfa)	{
	Dfa<CharT> dfa;
	Converter<CharT> c(nfa, dfa);
	c.exec();
	return dfa;
}

template <typename CharT>
void to_dfa(const Nfa<CharT>& nfa, Dfa<CharT>& result)	{
	Converter<CharT> c(nfa, result);
	c.exec();
}


template <typename CharT>	
class Minimizer{	
	typedef std::set<size_t> Partition;
	typedef std::vector<Partition> Partitions; 
	typedef typename Dfa<CharT>::State State;

	const Dfa<CharT>& _dfa;

	Partitions partitions;

	void log_partitions(const std::string& s, Partitions& partitions)	 const	{
		using namespace std;
		cout << s << " {" ;
		for(auto part=partitions.begin();part!=partitions.end();++part)	{
			log_partition("", *part);
			cout << ", ";
		}
		cout << "}" << endl;
		
	}

	void log_partition(const std::string& name, Partition& partition)	 const	{
		using namespace std;
		cout << name << "(" ;
		for(auto it=partition.begin();it!=partition.end();++it)	{
				cout << *it << ',';
		}
		cout << ") ";
		
	}

	


	int get_partition_index(const Partitions& partitions, const size_t state) const {
		for(size_t i=0;i<partitions.size();i++)	{
			const Partition& p = partitions[i];
			if (p.find(state)!=p.end())	{
				return i;
			}
		}
		return -1;
	}


	bool is_compatible(const Partitions& partitions, const size_t st1, const size_t st2) const		{
		const State& state1 = _dfa.states[st1];
		const State& state2 = _dfa.states[st2];
		for(auto it = state1.transitions.begin();it!=state1.transitions.end();++it)	{
			size_t s1 = it->second;
			auto tr_aux = state2.transitions.find(it->first);
			if (tr_aux!=state2.transitions.end())	{
				size_t s2 = tr_aux->second;
				if (get_partition_index(partitions, s1) != get_partition_index(partitions, s2))	{
					return false;
				}				
			}
		}
		return true;
	}

	bool is_compatible(const Partitions& partitions, const Partition& part, const size_t state) const	{
		const size_t ref_state = *part.begin();
		if (!is_compatible(partitions, ref_state, state) || !is_compatible(partitions, state, ref_state))	{
			return false;
		}
		return true;
	}


	void insert_state_in_partition(const Partitions& partitions, const size_t state, Partitions& new_partitions)	 const	{
		for(size_t i=0;i<new_partitions.size();i++)	{
			if (is_compatible(partitions, new_partitions[i], state))	{
				new_partitions[i].insert(state);
				return;
			}
		}
		Partition p;
		p.insert(state);
		new_partitions.push_back(p);
	}

	
	void split_partition (const Partitions& partitions, const Partition& partition, Partitions& new_partitions ) const	{
			
		if (!partition.empty())	{
			auto it = partition.begin();
//			auto ref = it;
			Partition new_partition;
			new_partition.insert(*it);
			new_partitions.push_back(new_partition);
			++it;
			while(it!=partition.end())	{				
				insert_state_in_partition(partitions, *it, new_partitions);
				++it;
			}
		}
	}

	Dfa<CharT>& _result;

public:
	Minimizer(const Dfa<CharT>& dfa, Dfa<CharT>& result):_dfa(dfa), _result(result)	{ }
	
	void exec() 	{
		using namespace std;
		//cout <<"minimize() _dfa.states.size():" << _dfa.states.size()<< endl;
		
		Partition final_states;
		Partition non_final_states;
		
		for(size_t i=0;i<_dfa.states.size();++i)	{
			//cout <<it->name << endl;
			if (_dfa.states[i]._final)	{
				final_states.insert(i);
			} else	{
				non_final_states.insert(i);
			}
		}
		partitions.push_back(final_states);
		partitions.push_back(non_final_states);
//		log_partitions("partitions", partitions);
		if (final_states.empty() || non_final_states.empty())	{
			_result = _dfa;
			return;
		}
		while(true)	{
			bool go=false;
			Partitions new_partitions;
			for(size_t p=0;p<partitions.size();p++) {
				Partitions partition_fragments;
				split_partition(partitions, partitions[p], partition_fragments);				
//				log_partition("partition ", partition_fragments[0]); cout << endl;
				
				new_partitions.push_back(partition_fragments[0]);
				
				for(size_t i=1;i<partition_fragments.size();++i)	{
//					log_partition("partition " , partition_fragments[i]); cout << endl;
					
					new_partitions.push_back(partition_fragments[i]);
					go = true;
				}
			}
			if (go) {
				partitions = new_partitions;
			}else	{
				break;
			}
			//break;
		}
		//log_partitions("partitions", partitions);
		
		//Dfa<CharT> result(partitions.size());
		
		
		for(size_t part_ind = 0; part_ind<partitions.size();++part_ind)	{
			const State& ref_state = _dfa.states[*partitions[part_ind].begin()];
			
			const typename Dfa<CharT>::State::Transitions& trs = ref_state.transitions;
			typename Dfa<CharT>::State::Transitions new_trs; 
			
			for(auto tr=trs.begin();tr!=trs.end();++tr)	{
				new_trs[tr->first] = get_partition_index(partitions, tr->second);
			}
			bool final = ref_state._final;
			_result.set_state_info(part_ind, new_trs, final);
		}
		_result.set_initial_state(get_partition_index(partitions, _dfa.initial_state()));
		//cout <<"minimize() end" << endl;
//		return result;
	}

	
};

template <typename CharT>
Dfa<CharT> minimize(const Dfa<CharT>& dfa)	{
	Dfa<CharT> result;
	Minimizer<CharT> c(dfa, result);
	c.exec();
	return result;
}

template <typename CharT>
void minimize(const Dfa<CharT>& dfa, Dfa<CharT>& result)	{
	Minimizer<CharT> c(dfa, result);
	c.exec();
}

template <typename CharT>
class Normalizer	{
	typedef typename Dfa<CharT>::State State;
	typedef typename Dfa<CharT>::State::Transitions Transitions;
	const Dfa<CharT>& _dfa;
	Dfa<CharT> _result;
	std::map<size_t, size_t> old_to_new;
	std::set<size_t> states_done;
	
	size_t translate(const size_t old_id)	{
		auto it_aux = old_to_new.find(old_id);
		if (it_aux==old_to_new.end())	{
			size_t new_id = old_to_new.size();
			old_to_new[old_id] = new_id;
			return new_id;
		}else	{
			return it_aux->second;
		}
	}
	
	void process_state(size_t state_id)	{
		size_t new_state = translate(state_id);
		const State& state = _dfa.states[state_id];
		
		Transitions new_transitions;
		for (auto it=state.transitions.begin();it!=state.transitions.end();++it)	{
			// dont add transitions to the same state.
/*			if (state_id==it->second)	{
				continue;
			}*/
			//size_t state = new_states_to_state[it->second];
			size_t state = translate(it->second); 
			new_transitions[it->first] = state;
		}
		_result.set_state_info(new_state, new_transitions, state._final);
		states_done.insert(state_id);
		for (auto it=state.transitions.begin();it!=state.transitions.end();++it)	{
			if (states_done.find(it->second)==states_done.end())	{
				process_state(it->second);		
			}
		}		
	}
	
public:

	Normalizer(const Dfa<CharT>& dfa):_dfa(dfa)	{}
	Dfa<CharT> operator()()	{
		size_t state_id = _dfa.initial_state();
		process_state(state_id);
		return _result;
	}	
};

template <typename CharT>
Dfa<CharT> normalize(const Dfa<CharT>& dfa)	{
	Normalizer<CharT> c(dfa);
	return c();
}

template <typename CharT>
bool operator==(const Dfa<CharT>& dfa1, const Dfa<CharT>& dfa2)	{
	const Dfa<CharT>& norm1 = normalize(dfa1);
	const Dfa<CharT>& norm2 = normalize(dfa2);
	std::stringstream ss1;
	ss1 << norm1;
	std::stringstream ss2;
	ss2 << norm2;
	return ss1.str()==ss2.str();
}

template <typename CharT>
Nfa<CharT> to_nfa(const Dfa<CharT>& dfa)	{
	typedef typename Dfa<CharT>::State _DfaState;
	typedef typename Nfa<CharT>::State _NfaState;
	Nfa<CharT> result(dfa.states.size());
	for(size_t i=0; i!=dfa.states.size();++i)	{
		const _DfaState& state = dfa.states[i];
		for(auto it_trans = state.transitions.begin(); it_trans!= state.transitions.end();++it_trans)	{
			result.states[i].transitions.insert(*it_trans);
			int flag = 0;
			if (state.final())	{				
				flag = flag | _NfaState::FINAL;
			}
			if (i==0)	{				
				flag = flag | _NfaState::INITIAL;
			}
			result.states[i].set_flag(flag);
		}
	}
	return result;
}



#endif // DFA_H
