/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <iterator>

namespace unicpp	{

	class codification_error: public std::exception	{
		virtual const char* what() const throw()	{
			return "codification_error";
		}
	};

	template <typename CharT>	struct utf_iterator_char_traits	{
		typedef std::random_access_iterator_tag category;
		
	};
	
	template <typename CharT>
	struct utf_iterator_char_traits_32	{
		typedef CharT value_type;
//		typedef std::bidirectional_iterator_tag category;
		typedef std::random_access_iterator_tag category;
		
		template <typename BaseIterator, typename Range>
		inline static void next(BaseIterator& it, const Range& range){
			//std::cout << "inline static void next(BaseIterator& it)\n"; 
			++it;
		}
		
		template <typename BaseIterator, typename Range>
		inline static void prev(BaseIterator& it, const Range&){
			--it;
		}
		template <typename BaseIterator, typename Range>
		inline static const char32_t value(BaseIterator& it, const Range& range)	{
			return *it; 
		}

		template <typename BaseIterator, typename Range>
		inline static void write_value(char32_t val, BaseIterator& it, const Range& range)	{
			*it = val; 
			++it;
		}

		template <typename BaseIterator>
		inline static void  write_value_inv(char32_t val, BaseIterator& it)	{			
			*it = val; 
			++it;
		}
		template <typename BaseIterator, typename Range>
		inline static void sync_code_point(BaseIterator& it, const Range&)	{
		}

		// for ramdom access iterators
		template <typename BaseIterator>
		inline static BaseIterator add(BaseIterator& it, typename std::iterator_traits<BaseIterator>::difference_type n)	{
			return it+n;
		}
		template <typename BaseIterator>
		inline static BaseIterator sub(BaseIterator& it, typename std::iterator_traits<BaseIterator>::difference_type n)	{
			return it-n;
		}

		template <typename BaseIterator>
		inline static void inc(BaseIterator& it, typename std::iterator_traits<BaseIterator>::difference_type n)	{
			it+=n;
		}
		template <typename BaseIterator>
		inline static void dec(BaseIterator& it, typename std::iterator_traits<BaseIterator>::difference_type n)	{
			it-=n;
		}
		template <typename BaseIterator>
		inline static char32_t get(BaseIterator& it, typename std::iterator_traits<BaseIterator>::difference_type n)	{
			return it[n];
		}
		template <typename BaseIterator>
		inline static 
		typename std::iterator_traits<BaseIterator>::difference_type  diff(BaseIterator& it1, BaseIterator& it2)	{
			return it1-it2;
		}
	};
	
	template <>
	struct utf_iterator_char_traits<char>	{
		typedef char value_type;
		typedef std::bidirectional_iterator_tag category;
		
		template<typename BaseIterator, typename Range>
		inline static void next(BaseIterator& it, const Range& range){
			range.check_end(it);
			it+=size(*it);
		}
		
		template<typename BaseIterator, typename Range>
		inline static void prev(BaseIterator& it, const Range& range){
			--it;
			sync_code_point(it, range);
		}


		template<typename OutputIteator, typename Range>
		inline static void write_value(char32_t val, OutputIteator& it, const Range& range) {			
			if (val <= 0x007f)	{
				//1 byte
				*it= (val & 0x7f);
				++it;
			}else if (val <=0x07ff)	{				
				//2 bytes
				char32_t value = val >> 6;
				*it= ((value & 0x1f) | 0xc0);
				++it;
				range.check_end(it);
				*it= ((val & 0x3f) | 0x80);
				++it;
			}else if (val <=0xffff)	{				
				//3 bytes
				char32_t value = val >> 12;
				*it= ((value & 0x0f) | 0xe0);
				++it;
				range.check_end(it);
				value = val >> 6;
				*it= ((value & 0x3f) | 0x80);
				++it;
				range.check_end(it);
				*it= ((val & 0x3f) | 0x80);
				++it;
			}else if (val <=0x10ffff)	{
				//4 bytes
				char32_t value = val >> 18;
				*it= ((value & 0x07) | 0xf0);
				++it;
				range.check_end(it);
				value = val >> 12;
				*it= ((value & 0x3f) | 0x80);
				++it;
				range.check_end(it);
				value = val >> 6;
				*it= ((value & 0x3f) | 0x80);
				++it;
				range.check_end(it);
				*it= ((val & 0x3f) | 0x80);
				++it;
			}else	{
				codification_error e;
				throw e;			
			}
		}
		
		template<typename OutputIterator>
		inline static void write_value_inv(char32_t val, OutputIterator& it) {
			if (val <= 0x007f)	{
				*it = val;
				++it;
			}else if (val <=0x07ff)	{				
				//2 bytes
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x1f) | 0xc0;
				++it;
			}else if (val <=0xffff)	{				
				//3 bytes
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x0f) | 0xe0;
				++it;
			}else if (val <=0x10ffff)	{
				//4 bytes
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x3f) | 0x80;
				++it;
				val >>= 6;
				*it = (val & 0x07) | 0xf0;
				++it;
			}else	{
				codification_error e;
				throw e;			
			}
		}

		
		template<typename BaseIterator, typename Range>
		inline static char32_t value(BaseIterator& it, const Range& range)	{
			//std::cout << "inline static char32_t value(BaseIterator& it) " << std::endl; 			
			char32_t val;
			switch(size(*it))	{
				case 1:
					return *it;
				case 2:
					val = (*it & 0x1f) << 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					return val;
				case 3:
					val = (*it & 0x0f) << 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					val <<= 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					return val;
				case 4:
					val = (*it & 0x07) << 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					val <<= 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					val <<= 6;
					++it;
					range.check_end(it);
					val += *it & 0x3f;
					return val;
			}
			codification_error e;
			throw e;
		}

		template<typename BaseIterator, typename Range>
		inline static void sync_code_point(BaseIterator& it, const Range& range)	{
			while((~(*it) & 0x40) && (*it & 0x80) && !range.is_begin(it))	{
				--it;
			}
		}
		
//	private:

		inline static int size(const value_type& value)	{
			//value_type tmp = *it;
			value_type ntmp = ~value;

			if ((ntmp&0x80)==0x80)	{
				return 1;
			}else if(((ntmp&0x20)==0x20) && ((value&0xc0)==0xc0))	{
				return 2;
			}else if(((ntmp&0x10)==0x10) && ((value&0xe0)==0xe0))	{
				return 3;
			}else if(((ntmp&0x08)==0x08) && ((value&0xf0)==0xf0))	{
				return 4;
			}
			codification_error e;
			throw e;
		}


		inline static int _size(const unsigned char& value)	{
			
			//static 
			const int table[]={
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0 };			
			return table[value];
		}

	};
	
	template <typename CharT>
	struct utf_iterator_char_traits_16{
		typedef CharT value_type;
		typedef std::bidirectional_iterator_tag category;
		
		static const CharT HI_BEGIN = 0xd800;
		static const CharT HI_END   = 0xdbff;
		static const CharT LO_BEGIN = 0xdc00;
		static const CharT LO_END   = 0xdfff;
		
		template<typename BaseIterator, typename Range>
		inline static void next(BaseIterator& it, const Range& range){
			if (is_surrogate_pair(*it))	{
				++it;
				range.check_begin(it);
			}
			++it;
		}
		template<typename BaseIterator, typename Range>
		inline static void prev(BaseIterator& it, const Range& range){
			--it;
			range.check_begin(it);
			if (is_lo_surrogate_pair(*it))	{
				--it;
			}
		}
		
		template<typename BaseIterator, typename Range>
		inline static char32_t value(BaseIterator& it, const Range& range)	{
			if (is_surrogate_pair(*it))	{
				//BaseIterator tmp = it;
				char32_t val = *it - HI_BEGIN;
				val <<= 10;
				++it;
				range.check_end(it);
								
				//if (!is_lo_surrogate_pair(*tmp))	{
				//if (!(LO_BEGIN <= *tmp && *tmp <= LO_END))	{
				char32_t val2 = *it;
				if (LO_BEGIN > val2 )	{
					codification_error e;
					throw e;
				}  
				val += val2 - LO_BEGIN;
				val += 0x10000;
				return val;
			} else	{
				return *it;				
			}
		}


		template<typename OutputIterator, typename Range>
		inline static void write_value(char32_t val, OutputIterator& it, const Range& range) {
			if (val<=0xFFFF)	{
				*it=val;
				++it;
			}else	{   
				val-=0x10000;
				CharT val_hi = val >> 10;
				CharT val_lo = val & 0x3ff;
				*it=val_hi+HI_BEGIN;
				++it;
				range.check_end(it);
				*it=val_lo+LO_BEGIN;
				++it;
			}
			
		}

		template<typename OutputIterator>
		inline static void write_value_inv(char32_t val, OutputIterator& it) {
			if (val<=0xFFFF)	{
				*it = val;
				++it;
			}else	{   
				val-=0x10000;
				CharT val_hi = val >> 10;
				CharT val_lo = val & 0x3ff;
				*it= val_lo+LO_BEGIN;
				++it;
				*it = val_hi+HI_BEGIN;
				++it;
			}
		}
		
		template<typename BaseIterator, typename Range>
		inline static void sync_code_point(BaseIterator& it, const Range& range)	{
			value_type v = *it;
			if (is_lo_surrogate_pair(v))	{
				--it;
			}
		}
		
	private:
		inline static bool is_hi_surrogate_pair(const value_type v)	{
			return   HI_BEGIN <= v && v <= HI_END;  
		}
		inline static bool is_lo_surrogate_pair(const value_type v)	{
			return   LO_BEGIN <= v && v <= LO_END;  
		}
		inline static bool is_surrogate_pair(const value_type& v)	{
			return   HI_BEGIN <= v && v <= LO_END;  
		}
	};

	template <>
	struct utf_iterator_char_traits<char16_t>: public utf_iterator_char_traits_16<char16_t>{
	};


	template <>
	struct utf_iterator_char_traits<char32_t>: public utf_iterator_char_traits_32<char32_t>{
	};

#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
	template <>	struct utf_iterator_char_traits<wchar_t>: public utf_iterator_char_traits_32<wchar_t>{	};
#elif __SIZEOF_WCHAR_T__ == 2 
	template <>	struct utf_iterator_char_traits<wchar_t>: public utf_iterator_char_traits_16<wchar_t>{	};
#endif

//  struct output_iterator_tag { };
	template<typename T>
	struct CategoryTraits;		

	template<>
	struct CategoryTraits<std::input_iterator_tag>	{
		enum {priority=0};
	};
	template<>
	struct CategoryTraits<std::forward_iterator_tag>	{
		enum {priority=1};
	};
	template<>
	struct CategoryTraits<std::bidirectional_iterator_tag >	{
		enum {priority=2};
	};
	template<>
	struct CategoryTraits<std::random_access_iterator_tag>	{
		enum {priority=3};
	};
	template <bool cond, typename Then, typename Else>	
	struct If	{
		typedef Then Result; 
	};
	template <typename Then, typename Else>	
	struct If<false, Then, Else>	{
		typedef Else Result; 
	};
	template<int N1, int N2> 
	struct GreaterThan	{
		enum {Result=N1>N2};
	};
	template<int N1, int N2> 
	struct LesserThan	{
		enum {Result=N1<N2};
	};

	template<typename Cat1, typename Cat2>
	struct SelectCat	{
		typedef 
			typename If< 
				LesserThan<
						CategoryTraits< Cat1 >::priority, 
						CategoryTraits< Cat2 >::priority 
				>::Result, 
				Cat1, 
				Cat2
			>::Result Result;
	};
 
	
/*	template <typename Cat1, typename Cat2>
	struct LowestCat	{
		typedef Select<Cat1, Cat2, 
//			(typename CategoryTraits<Cat1>::priority < typename CategoryTraits<Cat2>::priority)  >::Result Result;
			false  >::Result Result;
	};
*/
/*	
	template <typename BaseIterator>	
	struct base_iterator_traits	{
		typedef typename BaseIterator::value_type value_type;
		typedef utf_iterator_char_traits< value_type > iterator_char_traits;
//		typedef utf_iterator_char_traits< value_type > category;
//		typedef LowestCat<typename BaseIterator::category , utf_iterator_char_traits<value_type> > category;
	};

	template <typename T>	
	struct base_iterator_traits<const T*>	{
		typedef T value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

	template <typename T>	
	struct base_iterator_traits<T*>	{
		typedef T value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};


	template <typename _CharT, typename _Traits>
	struct base_iterator_traits<std::ostream_iterator<_CharT, _CharT, _Traits> >	{
		typedef _CharT value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};




	template <class Container>
	struct base_iterator_traits<std::front_insert_iterator<Container> >	{
		typedef typename Container::value_type value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

	template <typename _CharT, typename _Traits>
	struct base_iterator_traits<std::ostreambuf_iterator<_CharT, _Traits> >	{
		typedef _CharT value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};
*/


	template <typename BaseIterator>	
	struct base_iterator_traits: public std::iterator_traits<BaseIterator>	{
		typedef typename std::iterator_traits<BaseIterator>::value_type value_type ;
		typedef utf_iterator_char_traits< typename std::iterator_traits<BaseIterator>::value_type > iterator_char_traits;
//		typedef utf_iterator_char_traits< value_type > category;
//		typedef LowestCat<typename std::iterator_traits<BaseIterator>::iterator_category, utf_iterator_char_traits<value_type> > category;
		typedef typename SelectCat<
					typename utf_iterator_char_traits< value_type >::category, 
					typename std::iterator_traits<BaseIterator>::iterator_category
			>::Result category;

	};

	template <class Container>
	struct base_iterator_traits<std::insert_iterator<Container> >	{
		typedef typename Container::value_type value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

	template <typename _CharT, typename _Traits>
	struct base_iterator_traits<std::ostream_iterator<_CharT, _CharT, _Traits> >	{
		typedef _CharT value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

	template <typename _CharT, typename _Traits>
	struct base_iterator_traits<std::ostreambuf_iterator<_CharT, _Traits> >	{
		typedef _CharT value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

	template <class Container>
	struct base_iterator_traits<std::back_insert_iterator<Container> >	{
		typedef typename Container::value_type value_type ;
		typedef utf_iterator_char_traits<value_type> iterator_char_traits;
	};

} //namespace unicpp	
