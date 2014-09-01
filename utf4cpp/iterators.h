/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef UTF4CPP_ITERATORS_H
#define UTF4CPP_ITERATORS_H


namespace unicpp	{

	class range_error: public std::exception	{
		virtual const char* what() const throw()	{
			return "range_error";
		}
	};

	
	template <typename BaseIterator>
	class null_iterator_range{
	public:	
		null_iterator_range(){}
		null_iterator_range(const null_iterator_range& ){}
		void check_begin(const BaseIterator& it) const {}
		bool is_begin(const BaseIterator& it) const { return false;}
		void check_end(const BaseIterator& it) const {}
		static const null_iterator_range INST;
//		static int i;
	private:
	}; 
	
	template <typename BaseIterator>
	const null_iterator_range<BaseIterator> null_iterator_range<BaseIterator>::INST;

	
	template <typename BaseIterator>
	class iterator_range{
	public:	
		iterator_range(const BaseIterator& begin, const BaseIterator& end)
		:_begin(begin),_end(end){
			_begin--;
		}
		iterator_range(const iterator_range& range)
		:_begin(range._begin), _end(range._end){}
		void check_begin(const BaseIterator& it) const {
			if (it==_begin)	{
				throw range_error();
			}
		}
		bool is_begin(const BaseIterator& it) const { 
			return it==_begin;
		}
		void check_end(const BaseIterator& it) const {
			if (it==_end)	{
				throw range_error();
			}
		}
	private:
		BaseIterator _begin;
		BaseIterator _end;
	}; 
	
	template <typename BaseIterator, typename Range = null_iterator_range<BaseIterator> >
	class const_iterator : public std::iterator<typename base_iterator_traits<BaseIterator>::category, char32_t> 
	{
				
	public:

		typedef BaseIterator iterator_type;
//		typedef typename base_iterator_traits<BaseIterator>::value_type it_value_type;
		typedef typename std::iterator_traits<BaseIterator>::value_type it_value_type;
		
		
		typedef	utf_iterator_char_traits<it_value_type> iterator_traits_type;
		
		
		typedef typename std::iterator< typename base_iterator_traits<BaseIterator>::category, char32_t>  it_helper;
//		typedef typename it_helper::iterator_category iterator_category;
		typedef typename it_helper::value_type value_type;
		typedef typename it_helper::difference_type difference_type;
		typedef typename it_helper::pointer pointer;
		typedef typename it_helper::reference reference;
		
		const_iterator():_current(0)	{}
		
		explicit const_iterator(const BaseIterator& x):_current(x){
			//iterator_traits_type::sync_code_point(_current);
		}		
		explicit const_iterator(const BaseIterator& x, const BaseIterator& begin, const BaseIterator& end)
		:_current(x),_range(begin, end){
			//iterator_traits_type::sync_code_point(_current);
		}		
		const_iterator(const const_iterator<BaseIterator, Range>& x)
		:_current(x._current), _range(x._range){
//			iterator_traits_type::sync_code_point(current);
		}		

		// is this needed?
//		template <class U> const_iterator(const const_iterator<U>& u):current(u.current()), _range(u._range)	{		}

		BaseIterator base() const	{
			return _current;	
		}
		BaseIterator& base() {
			return _current;	
		}
		
		value_type operator*() const	{
			BaseIterator tmp(_current);
			return iterator_traits_type::value(tmp, _range);			
		}
		//pointer operator->() const;
		
		const_iterator& operator++()	{
			iterator_traits_type::next(_current, _range);
			return *this;
		}
		const_iterator operator++(int)	{
			const_iterator tmp = *this;
			iterator_traits_type::next(_current, _range);
			return tmp;
		}
		const_iterator& operator--()	{
			iterator_traits_type::prev(_current, _range);
			return *this;
		}
		const_iterator operator--(int)	{
			const_iterator tmp = *this;
			iterator_traits_type::prev(_current, _range);
			return tmp;
		}

		// random
		const_iterator operator+ (difference_type n) const	{
			return const_iterator(iterator_traits_type::add(_current, n));
		}
		const_iterator& operator+=(difference_type n)	{
			iterator_traits_type::inc(_current, n);
			return *this;
		}
		const_iterator operator- (difference_type n) const	{
			return const_iterator(iterator_traits_type::sub(_current, n));
		}
		const_iterator& operator-=(difference_type n)	{
			iterator_traits_type::dec(_current, n);
			return *this;
		}
		char32_t operator[](difference_type n) const	{
			return iterator_traits_type::get(_current, n);			
		}

		difference_type  operator-(const_iterator it)	{
			return iterator_traits_type::diff(_current, it._current);						
		}

		bool operator==(const const_iterator& y) const {
			return _current == y._current; 
		}
//		const BaseIterator& base current() const {return _current;}
	
	protected:
		BaseIterator _current;
		Range _range;
	};	

	template <typename Iterator, typename Range>
	inline bool operator!=(const const_iterator<Iterator, Range>& x, const const_iterator<Iterator, Range>& y) 	{
		return !(x.base() == y.base()); 
	}

/*
	template <typename Iterator, typename Range1, typename Range2>
	inline bool operator!=(const const_iterator<Iterator, Range1>& x, const const_iterator<Iterator, Range2>& y) 	{
		return !(x.base() == y.base()); 
	}
*/

	template <class Iterator>
	const_iterator<Iterator> make_const_iterator(const Iterator& i)	{
		return const_iterator<Iterator>(i);
	}

	template <class Iterator>
	const_iterator<Iterator, iterator_range<Iterator> > make_const_iterator(const Iterator& i, const Iterator& begin, const Iterator& end)	{
		return const_iterator<Iterator, iterator_range<Iterator> >(i, begin, end);
	}

	template <typename Cont>
	const_iterator< typename Cont::const_iterator, iterator_range<typename Cont::const_iterator> > make_const_iterator(const Cont& c, const typename Cont::const_iterator& i)	{
		return make_const_iterator(i, c.begin(), c.end());
	}
	
	template <typename InputIterator>
	class input_iterator:	public std::iterator<std::input_iterator_tag, char32_t> {
	public:
		typedef InputIterator iterator_type;
		typedef typename iterator_type::value_type iterator_value_type;
		typedef	utf_iterator_char_traits<typename InputIterator::value_type> iterator_traits_type;
		
		input_iterator()
		:value(0),value_ok(false),it(InputIterator()){
		}
		input_iterator(const InputIterator& _it)
		:value(0),value_ok(false),it(_it){
		}
		input_iterator(const input_iterator& x) = default;
		~input_iterator() = default;
		
		const value_type& operator*() 	{
			if (!value_ok)	{
				value = iterator_traits_type::value(it, null_iterator_range<iterator_type>::INST);
				++it;
				value_ok = true;
			}	
			return value;
		}
		const value_type* operator->() const;
		
		input_iterator& operator++()	{
			value_ok = false;
			return *this;
		}
		
		input_iterator operator++(int)	{
			value_ok = false;
			input_iterator tmp = *this;
			return tmp;
		}

		template <typename _InputIterator> friend 
		bool operator==(const input_iterator<_InputIterator>& x,	const input_iterator<_InputIterator>& y);

		template <typename _InputIterator> friend
		bool operator!=(const input_iterator<_InputIterator>& x,	const input_iterator<_InputIterator>& y);
			
	private:
		value_type value;
		bool value_ok;
		iterator_type it;		
	};
	

	template <class Iterator>
	input_iterator<Iterator> make_input_iterator(Iterator s=Iterator())	{
		return input_iterator<Iterator>(s);
	}

	template <typename _InputIterator> 
	bool operator==(const input_iterator<_InputIterator>& x,	const input_iterator<_InputIterator>& y)	{
		//std::cout << "bool operator==(const input_iterator<_InputIterator>& x,	const input_iterator<_InputIterator>& y) " 
		//	<< (x.it==y.it)<< std::endl;
		return x.it==y.it;
	}

	template <typename _InputIterator> 
	bool operator!=(const input_iterator<_InputIterator>& x,	const input_iterator<_InputIterator>& y)	{
	//	return !(x==y);
		return !(x.it==y.it);

	}





	template<typename OutputIterator, typename Range = null_iterator_range<OutputIterator> >
	class output_iterator: public std::iterator<std::output_iterator_tag, char32_t, void, void, void>	{
		
	public:
		typedef	utf_iterator_char_traits<typename base_iterator_traits<OutputIterator>::value_type> iterator_traits_type;
		
		output_iterator(OutputIterator it):it(it){}
		
		output_iterator&	operator=(const char32_t value){
			iterator_traits_type::write_value(value,  it, _range);
			return *this;
		}
		
		output_iterator& operator*()	{
			return *this;
		}
		output_iterator& operator++()	{
			return *this;
		}
		output_iterator& operator++(int)	{
			return *this;
		}
		
		
	private:
		OutputIterator it;
		Range _range;
	};
	

	template<typename _Container>
	class output_iterator<std::front_insert_iterator<_Container> >: public std::iterator<std::output_iterator_tag, char32_t, void, void, void>	
	{
		
	public:
		typedef	utf_iterator_char_traits<typename _Container::value_type> iterator_traits_type;
		
		output_iterator(typename std::front_insert_iterator<_Container> it):it(it){}
		
		output_iterator&	operator=(const char32_t value){
			iterator_traits_type::write_value_inv(value,  it);
			return *this;
		}
		
		output_iterator& operator*()	{
			return *this;
		}
		output_iterator& operator++()	{
			return *this;
		}
		output_iterator& operator++(int)	{
			return *this;
		}
		
		
	private:
		typename std::front_insert_iterator<_Container> it;
	};
	


	template <class Container>
	output_iterator<std::insert_iterator<Container>	>  
	inserter(Container& x, typename Container::iterator it)	{
		return output_iterator<std::insert_iterator<Container>>(std::inserter(x, it));
	}

	template <class Iterator>
	output_iterator<Iterator> inserter(Iterator it)	{
		return output_iterator<Iterator>(it);
	}


	template <class Container>
	output_iterator<std::front_insert_iterator<Container> > 
	front_inserter(Container& x)	{
		return output_iterator<std::front_insert_iterator<Container> >(std::front_inserter(x));
	}

	template <class Container>
	output_iterator<std::back_insert_iterator<Container> > 
	back_inserter(Container& x)	{
		return output_iterator<std::back_insert_iterator<Container> >(std::back_inserter(x));
	}

	template <typename _CharT, typename _Traits>
	output_iterator<std::ostream_iterator<_CharT, _CharT, _Traits> > 
	stream_inserter(std::basic_ostream<_CharT, _Traits>& x)	{
		typedef output_iterator< std::ostream_iterator<_CharT, _CharT, _Traits> > _type;
		return _type(std::ostream_iterator<_CharT, _CharT, _Traits>(x));
		
	};
	


	template <typename _CharT, typename _Traits>
	output_iterator<std::ostreambuf_iterator<_CharT, _Traits> > 
	streambuf_inserter(std::basic_streambuf<_CharT, _Traits>* sb)	{
		typedef output_iterator< std::ostreambuf_iterator<_CharT, _Traits> > _type;

		std::ostreambuf_iterator<_CharT, _Traits> sbi(sb);
		_type x(sbi);
		return x;
		
	};

	template<typename C1, typename C2> 
	void convert(const C1& c1, C2& c2)	{
		copy(make_const_iterator(c1.begin(), c1.begin(), c1.end()), make_const_iterator(c1.end(), c1.begin(), c1.end()), unicpp::back_inserter(c2));	
	};

	template<typename C> 
	void convert(const C& c1, C& c2)	{
		c2 = c1;
	};

	
} //namespace unicpp	

#endif // UTF4CPP_ITERATORS_H
