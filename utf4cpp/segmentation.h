/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef UTF4CPP_SEGMENTATION_H
#define UTF4CPP_SEGMENTATION_H

#include "iterators.h"
#include "cdb/grapheme_break.h"
#include "cdb/word_break.h"
#include "cdb/sentence_break.h"
#include "cdb/line_break.h"

#include "dfa/grapheme_break_dfa.h"
#include "dfa/word_break_dfa.h"
#include "dfa/sentence_break_dfa.h"


namespace unicpp	{
/*
bool grapheme_boundry(
	cdb::graphemebreak::PropertyValue prop_value, 
	cdb::graphemebreak::PropertyValue  next_prop_value)	
{
	using namespace cdb::graphemebreak;
	bool debug = false;
	if (prop_value == PropertyValue::CR && next_prop_value == PropertyValue::LF)	{
		//GB3.
		if (debug) cout << "GB3." << endl;
		return false;
	}else if (	prop_value == PropertyValue::Control || 
				prop_value == PropertyValue::CR || 
				prop_value == PropertyValue::LF )	{
		//GB4.
		if (debug) cout << "GB4." << endl;
		return true;
	}else if(	next_prop_value == PropertyValue::Control || 
				next_prop_value == PropertyValue::CR || 
				next_prop_value == PropertyValue::LF )	{
		//GB5.
		if (debug) cout << "GB5." << endl;
		return true;
	}else if(	prop_value == PropertyValue::L && 
			(	next_prop_value == PropertyValue::L || 
				next_prop_value == PropertyValue::V || 
				next_prop_value == PropertyValue::LV || 
				next_prop_value == PropertyValue::LVT ))	{
		//GB6.
		if (debug) cout << "GB6." << endl;
		return false;
	}else if((prop_value == PropertyValue::LV || prop_value == PropertyValue::V ) && 
				(	next_prop_value == PropertyValue::V || 
					next_prop_value == PropertyValue::T )){
		//GB7.
		if (debug) cout << "GB7." << endl;				
		return false;
	}else if((prop_value == PropertyValue::LVT || prop_value == PropertyValue::T)  && 
			(	next_prop_value == PropertyValue::T)){
		//GB8.
		if (debug) cout << "GB8." << endl;
		return false;
	}else if(next_prop_value == PropertyValue::Extend){
		//GB9.
		if (debug) cout << "GB9." << endl;
		return false;
	}else if(next_prop_value == PropertyValue::SpacingMark){
		//GB9a.
		if (debug) cout << "GB9a." << endl;
		return false;
	}else if(prop_value == PropertyValue::Prepend){
		//GB9b.
		if (debug) {
			
			cout << "GB9b. " << prop_value << " " << next_prop_value << endl;
		}
		return false;
	}else {
		if (debug) cout << "GB10." << endl;
		return true;
	}
}

template <typename CodepointIterator>	
class grapheme_range	{
	public:
	
	class iterator {
	public:
		iterator(grapheme_range& range, const CodepointIterator& cpi)
			:_range(&range), _current(cpi)
		{
		}
		iterator(const iterator& it)//=default;
			:_range(it._range), _current(it._current)	
		{
		}
		
		
		void operator=(const iterator& it)		{
			_range = it._range;
			_current = it._current;
		}
		
		iterator& operator++()	{
			next();
			return *this;
		}
		iterator operator++(int)	{
			iterator tmp = *this;
			next();
			return tmp;
		}
		
		void next()	{
			
			if (*this!=_range->end())	{
				using namespace cdb::graphemebreak;
				PropertyValue prior_value = get_value(*_current);
				//cout << hex << "next() values " << hex << *_current; 
				++_current;
				//cout << "  " << *_current << endl ; 
				PropertyValue value = get_value(*_current);
				while (*this!=_range->end())	{
					if (grapheme_boundry(prior_value, value))	{
						break;
					}
					prior_value = value;
					++_current;
					value = get_value(*_current);
				}
			}
		}
		iterator& operator--()	{
//			iterator_traits_type::prev(current);
			return *this;
		}
		iterator operator--(int)	{
			iterator tmp = *this;
//			iterator_traits_type::prev(current);
			return tmp;
		}
		bool operator==(const iterator& it)	const {
			return _current==it._current;
		}
		bool operator!=(const iterator& it)	const {
			return !(*this==it);
		}
		
		CodepointIterator current()	{ return _current; }
	private:
		CodepointIterator _current;
		grapheme_range* _range;
	};
	
	grapheme_range(const CodepointIterator& begin, const CodepointIterator& end)
	:_begin(*this, begin),_end(*this, end)
	{
	}
//	grapheme_range(const grapheme_range& gr) 	{
//		_begin = gr._begin;
//		_end   = gr._end;
//	}
	
	const iterator& begin()	{return _begin;}
	const iterator& end()	{return _end;}
private:
	iterator _begin;
	iterator _end;
	
};
	
*/	
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
namespace v1 {
	

bool word_boundry(
	cdb::wordbreak::PropertyValue* props)	
{
	using namespace cdb::wordbreak;
	if (
		//WB3. 	CR 	× 	LF
		props[1] == PropertyValue::CR && 
		props[2] == PropertyValue::LF)	{
		return false;
	}else if (	
		//WB3a. 	(Newline | CR | LF) 	÷ 	 
		props[1] == PropertyValue::Newline || 
		props[1] == PropertyValue::CR ||
		props[1] == PropertyValue::LF ) {
		return true;
	}else if (	
		//WB3b. 	  	÷ 	(Newline | CR | LF)
		props[2] == PropertyValue::Newline || 
		props[2] == PropertyValue::CR ||
		props[2] == PropertyValue::LF ) {
		return true;
//	}else if (	
//		//WB4. 	X (Extend | Format)* 	→ 	X		
//	)
	}else if (	
		//WB5. 	ALetter 	× 	ALetter
		props[1] == PropertyValue::ALetter && 
		props[2] == PropertyValue::ALetter ) {
		return false;
	}else if (	
		//WB6. 	ALetter 	× 	(MidLetter | MidNumLet) ALetter
		props[1] == PropertyValue::ALetter && 
		(
		props[2] == PropertyValue::MidLetter ||
		props[2] == PropertyValue::MidNumLet) && 
		props[3] == PropertyValue::ALetter) {
		return false;
	}else if (	
		//WB7. 	ALetter (MidLetter | MidNumLet) 	× 	ALetter
		props[0] == PropertyValue::ALetter && 
		(
		props[1] == PropertyValue::MidLetter ||
		props[1] == PropertyValue::MidNumLet) && 
		props[2] == PropertyValue::ALetter) {
		return false;
	}else if (	
		//WB8. 	Numeric 	× 	Numeric
		props[1] == PropertyValue::Numeric && 
		props[2] == PropertyValue::Numeric) {
		return false;
	
	}else if (	
		//WB9. 	ALetter 	× 	Numeric
		props[1] == PropertyValue::ALetter && 
		props[2] == PropertyValue::Numeric)	{
		return false;
	}else if (	
	//WB10. 	Numeric 	× 	ALetter
		props[1] == PropertyValue::Numeric && 
		props[2] == PropertyValue::ALetter)	{
		return false;
	}else if (	
		//WB11. 	Numeric (MidNum | MidNumLet) 	× 	Numeric
		props[0] == PropertyValue::Numeric &&
		(props[1] == PropertyValue::MidNum || 
		props[1] == PropertyValue::MidNumLet) &&
		props[2] == PropertyValue::Numeric) {
		return false;
	}else if (	
		//WB12. 	Numeric 	× 	(MidNum | MidNumLet) Numeric
		props[1] == PropertyValue::Numeric &&
		(props[2] == PropertyValue::MidNum || 
		props[2] == PropertyValue::MidNumLet) &&
		props[3] == PropertyValue::Numeric){
		return false;
	}else if (	
		//WB13. 	Katakana 	× 	Katakana
		props[1] == PropertyValue::Katakana && 
		props[2] == PropertyValue::Katakana)	{
		return false;
	}else if (	
		//WB13a. 	(ALetter | Numeric | Katakana | ExtendNumLet) 	× 	ExtendNumLet
		(props[1] == PropertyValue::ALetter || 
		props[1] == PropertyValue::Numeric || 
		props[1] == PropertyValue::Katakana || 
		props[1] == PropertyValue::ExtendNumLet) && 
		props[2] == PropertyValue::ExtendNumLet)	{
		return false;
	}else if (	
		//WB13b. 	ExtendNumLet 	× 	(ALetter | Numeric | Katakana)
		props[1] == PropertyValue::ExtendNumLet &&
		(props[2] == PropertyValue::ALetter || 
		props[2] == PropertyValue::Numeric || 
		props[2] == PropertyValue::Katakana))	{
		return false;
	}else {
		//WB14. 	Any 	÷ 	Any	
		return true;
	}

}





template <typename CodepointIterator>	
class word_range	{
	public:
	
	class iterator {
	public:
		iterator(word_range& range, const CodepointIterator& cpi)
			:_range(&range)		{
			init_props(cpi);
		}
		
		iterator(const iterator& it)//=default;
			:_range(it._range)
		{
			memcpy((void*)_props, (void*)it._props, sizeof(_props)); 
			memcpy((void*)_iters, (void*)it._iters, sizeof(_iters)); 
		}
		
		void init_props(const CodepointIterator& cpi)	{
			using namespace cdb::wordbreak;
			CodepointIterator tmp = cpi;
//			if (tmp!=_range.begin().current())	{
//				--tmp;
//				_iters[0] = tmp;
//			}
			_props[0] = PropertyValue::Other;
			_iters[0] = cpi;
//			if (_iters[0]!=_range.end().current())	{
//				--_iters[0];
//			}
			_props[1] = PropertyValue::Other;
			_iters[1] = cpi;
			
			_iters[2] = cpi;
			_props[2] = get_value(*_iters[2]);
			
			_iters[3] = _iters[2];
			inc_pointer(_iters[3]);
			_props[3] = get_value(*_iters[3]);
			
			
//			if (_reader!=_range->end().current())	{
//				_props[3] = inc_pointer(_reader);
//			}
		}
		
//		void operator=(const iterator& it)		{
//			_range = it._range;
//			_current = it._current;
//		}
		
		iterator& operator++()	{
			next();
			return *this;
		}
		iterator operator++(int)	{
			iterator tmp = *this;
			next();
			return tmp;
		}
		
		inline void inc_pointer(CodepointIterator& it)	{
			using namespace cdb::wordbreak;
			if (it!=_range->end().current())	{
				++it;
				PropertyValue  v = get_value(*it);
				while (it!=_range->end().current() && 
						(v==PropertyValue::Extend || v==PropertyValue::Format))
				{
					++it;
					//++_current;
					v = get_value(*it);
				}
//				return v;
			} else	{
//				return cdb::wordbreak::PropertyValue::Other;
			}	
		}
		
		void next()	{			
			using namespace cdb::wordbreak;
			while (_iters[2]!=_iters[3] 
			 //|| _reader!=_range->end().current()
			   )	{
				//cout << "next() while " << endl;
//				std::string aux(_iters[0].base(), _iters[3].base());
					cout << "next() while " << 
						_props[0] << ',' << 
						_props[1] << ',' <<
						_props[2] << ',' << 
						_props[3] <<  " " 
						//<< aux 
						<< endl;
				_iters[0] = _iters[1];
				_iters[1] = _iters[2];
				_iters[2] = _iters[3];
				//inc_pointer(_iters[3]);
				
				_props[0] = _props[1];
				_props[1] = _props[2];
				_props[2] = _props[3];

				if (_iters[3]!=_range->end().current())	{
					inc_pointer(_iters[3]);
					_props[3] = get_value(*_iters[3]);
				}else {
					_props[3] = cdb::wordbreak::PropertyValue::Other;
				}

				if (word_boundry(_props))	{
					cout << "next() while " << 
						_props[0] << ',' << 
						_props[1] << ',' <<
						_props[2] << ',' << 
						_props[3] <<  " ** break **" << endl;
					break;
				}
				//break;
			}
		}
		
		bool operator==(const iterator& it)	const {
//			bool result = _current==it._current && _offset==it._offset;
//			cout << "iterator==()" << _offset << " " << it._offset << " " << boolalpha << result << endl;
			
//			bool result = _pointers[1] == it._pointers[1];
//			cout << result << " " << (void*)_pointers[1] << " " << (void*)it._pointers[1] << endl;;
//			cout << "operator==() " << result  << endl;;
			return _iters[2]==it._iters[2];
		}
		bool operator!=(const iterator& it)	const {
			return !(*this==it);
		}
		
		CodepointIterator current() const	{ return _iters[2]; }
	private:
		//CodepointIterator _current;
//		CodepointIterator& _reader;
//		int _offset;
		word_range* _range;
		cdb::wordbreak::PropertyValue _props[4];
		CodepointIterator _iters[4]; 
//		typename CodepointIterator::iterator_type _pointers[4];
	};
	
	word_range(const CodepointIterator& begin, const CodepointIterator& end)
	:_begin(*this, begin),_end(*this, end)
	{
	}
//	grapheme_range(const grapheme_range& gr) 	{
//		_begin = gr._begin;
//		_end   = gr._end;
//	}
	
	const iterator& begin() const	{return _begin;}
	const iterator& end() const	{return _end;}
private:
	iterator _begin;
	iterator _end;
	
};

} // namespace v1
*/

/*
namespace v2 {

	
	
template <typename CodepointIterator>	
struct filter {

	filter(const CodepointIterator& cpi, const CodepointIterator& begin, const CodepointIterator& end)
	:_begin(begin), _end(end)
	{
		using namespace cdb::wordbreak;
		_values[0] = PropertyValue::Other;
		_values[1] = get_value_checked(cpi);
		_values[2] = PropertyValue::Other;
		_values[3] = PropertyValue::Other;
		
		_buffer[0] = cpi;
		_buffer[1] = cpi;
		_buffer[2] = cpi;
		_buffer[3] = cpi;
		inc(_buffer[2], _values[2]);
		_buffer[3] = _buffer[2];
		inc(_buffer[3], _values[3]);		
//		cout << _values[0] << " " << _values[1]  << " " << _values[2]  << " " << _values[3] << endl;
	}
	
	cdb::wordbreak::PropertyValue get_value_checked(const CodepointIterator& it)	{
		if (it!=_end)	{
//			size_t s = (_end.base() - it.base());
//			cout << "filter::get_value_checked() " << hex << *it << " " << s << endl;
			return cdb::wordbreak::get_value(*it);
		}else	{
			return cdb::wordbreak::PropertyValue::Other;
		}
	}
	
	void inc(CodepointIterator& it, cdb::wordbreak::PropertyValue& value)	{
		using namespace cdb::wordbreak;
		if (it!=_end)	{
			++it;
			value = get_value_checked(it);
			while((it!=_end) && (value==PropertyValue::Extend || value==PropertyValue::Format))	{
				++it;
				value = get_value_checked(it);
			}		
		}
	}
	
	void next()	{
//		cout << "filter::next()" << endl;
		using namespace cdb::wordbreak;
		if (_buffer[2]!=_end)	{
			_buffer[0] = _buffer[1];
			_buffer[1] = _buffer[2];		
			_buffer[2] = _buffer[3];		

			_values[0] = _values[1];		
			_values[1] = _values[2];		
			_values[2] = _values[3];		
			inc(_buffer[3], _values[3]);
		}
	}
	
	void operator++()	{
		next();
	}
	CodepointIterator _begin;
	CodepointIterator _end;
	CodepointIterator _buffer[4];
	cdb::wordbreak::PropertyValue _values[4];
	
};
	
template <typename CodepointIterator>	
bool word_boundry1(
	cdb::wordbreak::PropertyValue v1, cdb::wordbreak::PropertyValue v2, const filter<CodepointIterator>& f)	
{
	using namespace cdb::wordbreak;
//	cout << "word_boundry1: " << v1 << ' ' << v2 << endl;	
	const PropertyValue *props = &(f._values[0]);
//	cout << "word_boundry2: " << props[0]<< ' ' << props[1]<< ' '<< props[2]<< ' '<< props[3]<< ' '<< endl;	
//	bool debug = false;
	if (
		//WB3. 	CR 	× 	LF
		v1 == PropertyValue::CR && 
		v2 == PropertyValue::LF)	{
		return false;
	}else if (	
		//WB3a. 	(Newline | CR | LF) 	÷ 	 
		v1 == PropertyValue::Newline || 
		v1 == PropertyValue::CR ||
		v1 == PropertyValue::LF ) {
		return true;
	}else if (	
		//WB3b. 	  	÷ 	(Newline | CR | LF)
		v2 == PropertyValue::Newline || 
		v2 == PropertyValue::CR ||
		v2 == PropertyValue::LF ) {
		return true;
	}else if (
	//WB4. 	X (Extend | Format)* 	→ 	X
	//WB4 (¬Sep) × (Extend | Format)
		v2 == PropertyValue::Extend || 
		v2 == PropertyValue::Format	){
		return false;
	} else 	{
		if (	
			//WB5. 	ALetter 	× 	ALetter
			props[1] == PropertyValue::ALetter && 
			props[2] == PropertyValue::ALetter ) {
			return false;
		}else if (	
			//WB6. 	ALetter 	× 	(MidLetter | MidNumLet) ALetter
			props[1] == PropertyValue::ALetter && 
			(
			props[2] == PropertyValue::MidLetter ||
			props[2] == PropertyValue::MidNumLet) && 
			props[3] == PropertyValue::ALetter) {
			return false;
		}else if (	
			//WB7. 	ALetter (MidLetter | MidNumLet) 	× 	ALetter
			props[0] == PropertyValue::ALetter && 
			(
			props[1] == PropertyValue::MidLetter ||
			props[1] == PropertyValue::MidNumLet) && 
			props[2] == PropertyValue::ALetter) {
			return false;
		}else if (	
			//WB8. 	Numeric 	× 	Numeric
			props[1] == PropertyValue::Numeric && 
			props[2] == PropertyValue::Numeric) {
			return false;
		
		}else if (	
			//WB9. 	ALetter 	× 	Numeric
			props[1] == PropertyValue::ALetter && 
			props[2] == PropertyValue::Numeric)	{
			return false;
		}else if (	
		//WB10. 	Numeric 	× 	ALetter
			props[1] == PropertyValue::Numeric && 
			props[2] == PropertyValue::ALetter)	{
			return false;
		}else if (	
			//WB11. 	Numeric (MidNum | MidNumLet) 	× 	Numeric
			props[0] == PropertyValue::Numeric &&
			(props[1] == PropertyValue::MidNum || 
			props[1] == PropertyValue::MidNumLet) &&
			props[2] == PropertyValue::Numeric) {
			return false;
		}else if (	
			//WB12. 	Numeric 	× 	(MidNum | MidNumLet) Numeric
			props[1] == PropertyValue::Numeric &&
			(props[2] == PropertyValue::MidNum || 
			props[2] == PropertyValue::MidNumLet) &&
			props[3] == PropertyValue::Numeric){
			return false;
		}else if (	
			//WB13. 	Katakana 	× 	Katakana
			props[1] == PropertyValue::Katakana && 
			props[2] == PropertyValue::Katakana)	{
			return false;
		}else if (	
			//WB13a. 	(ALetter | Numeric | Katakana | ExtendNumLet) 	× 	ExtendNumLet
			(props[1] == PropertyValue::ALetter || 
			props[1] == PropertyValue::Numeric || 
			props[1] == PropertyValue::Katakana || 
			props[1] == PropertyValue::ExtendNumLet) && 
			props[2] == PropertyValue::ExtendNumLet)	{
			return false;
		}else if (	
			//WB13b. 	ExtendNumLet 	× 	(ALetter | Numeric | Katakana)
			props[1] == PropertyValue::ExtendNumLet &&
			(props[2] == PropertyValue::ALetter || 
			props[2] == PropertyValue::Numeric || 
			props[2] == PropertyValue::Katakana))	{
			return false;
		}else {
			//WB14. 	Any 	÷ 	Any	
			return true;
		}
	}
	return true;
}
	
	


template <typename CodepointIterator>
	class iterator {
	public:
		iterator(const CodepointIterator& cpi, const CodepointIterator& begin, const CodepointIterator& end)
			:_current(cpi),_begin(begin), _end(end),  _filter(cpi, begin, end)		{
//			init_props(cpi);
		}

		iterator(const iterator& it)=default;
		
		
		iterator& operator++()	{
			next();
			return *this;
		}
		iterator operator++(int)	{
			iterator tmp = *this;
			next();
			return tmp;
		}
		

		void next()	{
			if (_current!=_end)	{
//				cout << "word_range::iterator::next() " << hex << *_current << endl;
				using namespace cdb::wordbreak;
				PropertyValue prior_value = get_value(*_current);
				bool inc_filter = _filter._buffer[2].base() == _current.base();
				++_current;
				if (_current ==_end)	{
//					cout << "word_range::iterator::next() end" << endl;
					return;
				}
				PropertyValue value = get_value(*_current);
				
				while (_current !=_end)	{
					if (inc_filter)	{
						++_filter;
					}	
					if (word_boundry1(prior_value, value, _filter))	{
//						cout << "boundry founded" << endl;
						break;
					}
					
					prior_value = value;
					inc_filter = _filter._buffer[2].base() == _current.base();
					++_current;
					if (_current !=_end)	{
						value = get_value(*_current);					
					}else	{
						break;
					}
				}
			}
		}

		bool operator==(const iterator& it)	const {
			return _current==it._current;
		}
		bool operator!=(const iterator& it)	const {
			return !(*this==it);
		}
		
		CodepointIterator current() const	{ return _current; }
	private:
		CodepointIterator _current;
		CodepointIterator _begin;
		CodepointIterator _end;
		filter<CodepointIterator> _filter;
	};



template <typename CodepointIterator>	
class word_range	{
	public:
	
	
	word_range(const CodepointIterator& begin, const CodepointIterator& end)
	:_begin(begin, begin, end),_end(end, begin, end)
	{
	}
	
	const iterator<CodepointIterator>& begin() const	{return _begin;}
	const iterator<CodepointIterator>& end() const	{return _end;}
private:
	iterator<CodepointIterator> _begin;
	iterator<CodepointIterator> _end;
	
};

} // namespace v2
*/

namespace v3	{

template <typename CodepointIterator, typename Tokenizer>	class segmentation_range;

class GraphemeTokenizer {
	size_t _state;
public:

	GraphemeTokenizer ():_state(0)	{
	}

	int new_state_forward(char32_t c)	{
		using namespace cdb::graphemebreak;
		PropertyValue value = get_value(c);
//		std::cout << "segmentation_range::iterator::new_state() car:" <<std::hex <<  c << " prop: " << value << " " << _state << " "; 
//		std::cout << " -> " << grapheme_dfa[_state][(int)value]; ;
//		std::cout<< std::endl;
		return grapheme_dfa[_state][(int)value];
	}
	
	bool state_accepts_forward()	{		
//		return *(_state + word_states_length-1);					
		return grapheme_dfa[_state][ grapheme_dfa_length-1];
		 
	}

	int new_state_backwards(char32_t c)	{
		using namespace cdb::graphemebreak;
		PropertyValue value = get_value(c);
		//std::cout << "segmentation_range::iterator::new_state_backwards() car:" <<std::hex <<  c << " prop: " << value << " " << _state << " "; 
		//std::cout << " -> " << grapheme_dfa[_state][(int)value]; ;
		//std::cout<< std::endl;
		return grapheme_backwards_dfa[_state][(int)value];
	}
	
	bool state_accepts_backwards()	{		
//		return *(_state + word_states_length-1);					
		return grapheme_backwards_dfa[_state][ grapheme_backwards_dfa_length-1];
		 
	}

/*	template <typename CodepointIterator>
	void next(CodepointIterator& it, const CodepointIterator& end){
		//std::cout << "GraphemeSplitter::next() " << _state  << endl;
		_state =0;
		bool result;
		while (it!=end )	{
			
			_state = new_state_forward(*it);
			result = state_accepts_forward();
			//std::cout << "GraphemeSplitter::next() result: " << result  << endl;
			if (!result)	{
				_state =0;
				break;
			}
			++it;
			
		}
	}
*/	
	template <typename CodepointIterator>
	void next(CodepointIterator& it, const CodepointIterator& end){
		//std::cout << "WordSplitter::next() ini **********************" << endl;
		_state =0;		
		_state = new_state_forward(*it);
		//at least one step forward
		if (it==end)	{
			return;
		}
		++it;
		CodepointIterator tmp = it;
		while (tmp!=end && _state != grapheme_dfa_pit_state)	{
			_state = new_state_forward(*tmp);
			++tmp;
			//std::cout << "WordSplitter::next() _state:j " << _state << endl;			
			if (state_accepts_forward())	{
				it = tmp;
			}
		}
	}
	

	template <typename CodepointIterator>
	void prior(CodepointIterator& it, const CodepointIterator& passed_begin){
		//std::cout << "GraphemeSplitter::prior() begin" << endl;
		_state =0;
		bool result;
		while (it!=passed_begin )	{
//			std::cout << "GraphemeSplitter::prior() while" << endl;
			_state = new_state_backwards(*it);
			result = state_accepts_backwards();
//			std::cout << "GraphemeSplitter::prior() result: " << result  << endl;
			if (!result)	{
				_state =0;
				break;
			}
			--it;
		}
//		std::cout << "GraphemeSplitter::prior() end" << endl;
	}
};

class WordTokenizer {
	int _state;
//	int _pit_state;
public:

	WordTokenizer ():_state(0)	{
	}



	int new_state_forward(char32_t c)	{
		using namespace cdb::wordbreak;
		PropertyValue value = get_value(c);
//		std::cout << "segmentation_range::iterator::new_state() car:" <<std::hex <<  c << " prop: " << (int)value << " " << value << " _state:" << _state << " -> "; 
//		size_t index = _state*word_dfa_length + (int)value;
		int ns = word_dfa[_state][(int)value];
//		std::cout << ns <<  "\n "; 
		return ns;
		
	}
	
	bool state_accepts_forward()	{		
//		return *(_state + word_states_length-1);					
//		return word_states[_state*word_states_length + word_states_length-1];
		return word_dfa[_state][ word_dfa_length-1];
	}
	
	int new_state_backwards(char32_t c)	{
		using namespace cdb::wordbreak;
		PropertyValue value = get_value(c);
//		std::cout << "segmentation_range::iterator::new_state() car:" <<std::hex <<  c << " prop: " << value << " " << _state << " "; 
//		size_t index = _state*word_backwards_dfa_length + (int)value;
//		size_t index = *(_state + (int)value);
		//std::cout << " -> " << word_backwards_dfa[index] ;
		//std::cout<< std::endl;
		//return word_dfa[index];
		return word_backwards_dfa[_state][(int)value];
		
	}
	
	bool state_accepts_backwards()	{		
//		return *(_state + word_states_length-1);					
//		return word_states[_state*word_states_length + word_states_length-1];
		return word_backwards_dfa[_state][ word_backwards_dfa_length-1];
	}
	

	template <typename CodepointIterator>
	void next(CodepointIterator& it, const CodepointIterator& end){
		//std::cout << "WordSplitter::next() ini **********************" << endl;
		_state =0;		
		_state = new_state_forward(*it);
		//at least one step forward
		if (it==end)	{
			return;
		}
		++it;
		CodepointIterator tmp = it;
		while (tmp!=end && _state != word_dfa_pit_state)	{
			_state = new_state_forward(*tmp);
			++tmp;
			//std::cout << "WordSplitter::next() _state:j " << _state << endl;			
			if (state_accepts_forward())	{
				it = tmp;
			}
		}
	}


	template <typename CodepointIterator>
	void prior(CodepointIterator& it, const CodepointIterator& passed_begin){
		//std::cout << "WordSplitter::prior() " << endl;
		_state =0;
		CodepointIterator tmp = it;
		while (tmp!=passed_begin && _state != word_backwards_dfa_pit_state)	{
			_state = new_state_backwards(*tmp);
			--tmp;
			if (state_accepts_backwards())	{
				it = tmp;
			}
		}
	}
	
};




class SentenceTokenizer {
	size_t _state;
public:

	SentenceTokenizer ():_state(0)	{
	}

	int new_state_forward(char32_t c)	{
		using namespace cdb::sentencebreak;
		PropertyValue value = get_value(c);
//		std::cout << "segmentation_range::iterator::new_state() car:" <<std::hex <<  c << " prop: " << value << " " << _state << " "; 
//		size_t index = _state*sentence_states_length + (int)value;
//		size_t index = *(_state + (int)value);
//		std::cout << " -> " << sentence_dfa[_state][(int)value];
//		std::cout<< std::endl;
//		return sentence_dfa[_state*sentence_dfa_length +(int)value];
		return sentence_dfa[_state][(int)value];
	}
	

	bool state_accepts_forward(size_t st)	{		
//		return sentence_states[st*sentence_states_length + sentence_states_length-1];		
		return sentence_dfa[_state][ sentence_dfa_length-1];
	}

	int new_state_backwards(char32_t c)	{
		using namespace cdb::sentencebreak;
		PropertyValue value = get_value(c);
//		std::cout << "segmentation_range::iterator::new_state() car:" <<std::hex <<  c << " prop: " << value << " " << _state << " "; 
//		size_t index = _state*sentence_states_length + (int)value;
//		size_t index = *(_state + (int)value);
//		std::cout << " -> " << sentence_backwards_dfa[_state][(int)value];
//		std::cout<< std::endl;
//		return sentence_dfa[_state*sentence_dfa_length +(int)value];
		return sentence_backwards_dfa[_state][(int)value];
	}
	

	bool state_accepts_backwards(size_t st)	{		
//		return sentence_states[st*sentence_states_length + sentence_states_length-1];		
		return sentence_backwards_dfa[_state][ sentence_backwards_dfa_length-1];
	}

	template <typename CodepointIterator>
	void next(CodepointIterator& it, const CodepointIterator& end){
		//std::cout << "SentenceSplitter::next() " << endl;
		_state =0;
		CodepointIterator tmp = it;
		++it;
		while (tmp!=end && _state != sentence_dfa_pit_state)	{
			_state = new_state_forward(*tmp);
			++tmp;
			if (state_accepts_forward(_state))	{
				it = tmp;
			}
		}
	}
	
	template <typename CodepointIterator>
	void prior(CodepointIterator& it, const CodepointIterator& passed_begin){
		std::cout << "SentenceSplitter::prior() " << std::endl;
		_state =0;
		std::cout << "SentenceSplitter::prior() _state: " << _state << std::endl;
		CodepointIterator tmp = it;
/*		if (tmp!=passed_begin)	{
			--tmp;
		}else	{
			return;
		}*/
		bool accept = false;
		while (tmp!=passed_begin && _state != sentence_backwards_dfa_pit_state)	{
			_state = new_state_backwards(*tmp);
			std::cout << "SentenceSplitter::prior() _state: " << _state << std::endl;
			if (state_accepts_backwards(_state))	{
				accept = true;
				it = tmp;
				std::cout << "SentenceSplitter::prior() accepted *it: " << std::hex << *it << std::endl;
			}
			--tmp;
		}
		
		if (!accept)	{
			std::cout << "SentenceSplitter::prior() end not accept " << std::hex << *it << std::endl;
		}
		it = tmp;
		//std::cout << "SentenceSplitter::prior() *it: " << std::hex << *it << endl;

	}
	 
/*	
	template <typename CodepointIterator>
	void prior(CodepointIterator& it, const CodepointIterator& passed_begin){
		std::cout << "SentenceSplitter::prior() " << endl;
		_state =0;
		std::cout << "SentenceSplitter::prior() _state: " << _state << endl;
		CodepointIterator tmp = it;
		bool accept = false;
		while (tmp!=passed_begin && _state != sentence_backwards_dfa_pit_state)	{
			_state = new_state_backwards(*tmp);
			std::cout << "SentenceSplitter::prior() _state: " << _state << endl;
			if (state_accepts_backwards(_state))	{
				it = tmp;
				accept = true;
			}
			--tmp;
		}
		if (!accept && tmp==passed_begin)	{
			it = tmp;			
		}
		std::cout << "SentenceSplitter::prior() *it: " << std::hex << *it << endl;
	}
*/	
	
};

inline
std::ostream& operator <<(std::ostream& os, unicpp::cdb::linebreak::oportunity_break  v)	{
	using namespace unicpp::cdb::linebreak;
	switch(v)	{
//	 Prohibited, Indirect, ProhibitedCM, IndirectCM, Direct, Undefined
		case oportunity_break::Prohibited: os << "Prohibited"; break;
		case oportunity_break::Indirect: os << "Indirect"; break;
		case oportunity_break::ProhibitedCM: os << "ProhibitedCM"; break;
		case oportunity_break::IndirectCM: os << "IndirectCM"; break;
		case oportunity_break::Direct: os << "Direct"; break;
		case oportunity_break::Undefined: os << "Undefined"; break;
		default:
			os << "default";
	}
	return os;
}


/*
class LineTokenizer {
public:

	LineTokenizer ()	{
		//grapheme4,states[_state][10];
	}

	template <typename CodepointIterator>
	void next(CodepointIterator& it, const CodepointIterator& end){
		using namespace cdb::linebreak;
		if (it!=end)	{
			PropertyValue value = get_value(*it);
			std::cout << "c: " << std::hex << *it << " prop: " << value << std::endl;
			PropertyValue last_non_cm_value = value;
			PropertyValue last_non_sp_value = value;
			if (last_non_sp_value==PropertyValue::SP)	{
				last_non_sp_value = PropertyValue::WJ;
			}
			PropertyValue last_value = value;
			++it;
			while (it!=end)	{
				value = get_value(*it);
				std::cout << "c: " << *it << " prop: " << value << std::endl;
				if(value ==PropertyValue::BK)	{
					++it;
					break;
				}
				if(value ==PropertyValue::CB)	{
					break;
				}
				if(value ==PropertyValue::SP)	{
					last_value = value;
					last_non_cm_value = value;
					++it;
					continue;
				}
				if(value ==PropertyValue::CM)	{
					last_value = value;
					last_non_sp_value = value;
					++it;
					continue;
				}
				if(value ==PropertyValue::SA)	{
					last_value = value;
					last_non_sp_value = value;
					last_non_cm_value = value;
					++it;
					continue;// complex: 
				}
				oportunity_break ob = pair_table[(int)last_non_sp_value][(int)value];
				std::cout << "pair[" << last_non_sp_value << "][" << value << "] = " << ob << std::endl;
				if (ob == oportunity_break::Indirect)	{
					if (last_value == PropertyValue::SP)	
						{
						std::cout << "break 1" << std::endl;
						break;
					}
				}else if (ob == oportunity_break::IndirectCM)	{
					if (last_value == PropertyValue::SP) {
						std::cout << "break 2" << std::endl;
						break;
					}
//				}else if(last_value == PropertyValue::SP)	{
//					std::cout << "break 3" << std::endl;
//					break;			
				}else if (ob == oportunity_break::Direct 
					//|| ob == oportunity_break::Undefined
					)	
					{
					break;
				}
				
				last_value = value;
				last_non_sp_value = value;
				++it;
			}		
		}
	}

	
};
*/
	
template <typename CodepointIterator, typename Tokenizer>	
class segmentation_range	{
	public:
	
	class iterator {
	public:
		iterator(segmentation_range& range, const CodepointIterator& cpi)
			:_range(&range), _current(cpi)
		{
		}
		iterator(const iterator& it)//=default;
			:_range(it._range), _current(it._current)	
		{
		}
		
		
		void operator=(const iterator& it)		{
			_range = it._range;
			_current = it._current;
		}
		
		iterator& operator++()	{
			next();
			return *this;
		}
		
		iterator operator++(int)	{
			iterator tmp = *this;
			next();
			return tmp;
		}
		
		void next()	{
			_range->_tokenizer.next(_current, _range->end().current());
		}
		
		void prior()	{
			CodepointIterator tmp = _range->begin().current();
			_range->_tokenizer.prior(_current, --tmp);
		}
		
		iterator& operator--()	{
			prior();
			return *this;
		}
		
		iterator operator--(int)	{
			iterator tmp = *this;
			prior();
			return tmp;
		}
		
		bool operator==(const iterator& it)	const {
			return _current==it._current;
		}
		
		bool operator!=(const iterator& it)	const {
			return !(*this==it);
		}
		
		CodepointIterator current()	{ return _current; }
		const CodepointIterator current() const { return _current; }
	private:
		segmentation_range* _range;
		CodepointIterator _current;
	};
	
	
	segmentation_range(const CodepointIterator& begin, const CodepointIterator& end)
	:_begin(*this, begin),_end(*this, end)	{
		
	}
	
	
	const iterator& begin()	{return _begin;}
	const iterator& end()	{return _end;}
	Tokenizer _tokenizer;
private:
	iterator _begin;
	iterator _end;
	
};
	
	
	
}

using namespace v3;


} //namespace unicpp	


#endif //UTF4CPP_SEGMENTATION_H

