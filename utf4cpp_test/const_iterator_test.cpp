/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include <list> 

#include <utf4cpp/unicpp.h>

#include <boost/test/unit_test.hpp>

#include "test.h"
#include "test_data.h"

#include "const_iterator_test.h"

namespace test {

	void log(std::random_access_iterator_tag& i)	{
		cout << "std::random_access_iterator_tag" << endl;	
	}
	void log(std::bidirectional_iterator_tag& i)	{
		cout << "std::bidirectional_iterator_tag" << endl;	
	}
	
// it compares iteration from a basic_string<char32_t> with basic_string<T>. forward itereation (++it operator)
template<typename T> 
struct Test1	{
	static void exec()	{
		Test1<T> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		auto begin = make_const_iterator(input.begin());
		auto end = make_const_iterator(input.end());
		auto it=begin;
		auto it_ref = ref.begin();
		for(;it!=end;++it)	{
			BOOST_CHECK(*it==*it_ref);
			++it_ref;
		}
	}
};

// it compares iteration from a basic_string<char32_t> with basic_string<T>. forward itereation (it++ operator)
template<typename T> 
struct Test2	{
	static void exec()	{
		Test2<T> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		auto begin = make_const_iterator(input.begin());
		auto end = make_const_iterator(input.end());
		auto it=begin;
		auto it_ref = ref.begin();
		for(;it!=end;it++ )	{
			BOOST_CHECK(*it==*it_ref);
			it_ref++;
		}
	}
};


// it compares iteration from a basic_string<char32_t> with basic_string<T>. reverse iteration (--it operator)
template<typename T> 
struct Test3	{
	static void exec()	{
		Test3<T> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		//all but the first code point
		auto begin = make_const_iterator(input.begin());
		auto end = make_const_iterator(input.end());
		auto it=--end;
	
		auto it_ref = --ref.end();
		for(;it!=begin;--it )	{
			if (*it!=*it_ref)	{
				break;
			}
			--it_ref;
		}
		BOOST_CHECK(*it==*it_ref);
//		assert(*it==*it_ref);
	}
};

// it compares iteration from a basic_string<char32_t> with basic_string<T>. reverse iteration (it-- operator)
template<typename T> 
struct Test4	{
	static void exec()	{
		Test4<T> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<T> input = create_container<std::basic_string<T>>();
		
		//all but the first code point
		auto begin = make_const_iterator(input.begin());
		auto end = make_const_iterator(input.end());
		auto it=--end;
		auto it_ref = --ref.end();
		for(;it!=begin;it-- )	{
			if (*it!=*it_ref)	{
				break;
			}
			it_ref--;
		}
		BOOST_CHECK(*it==*it_ref);
	}
};


// ramdom access. checks char32_t value equals in both reference and basic_string<T>
struct RamdomAccesTest	{
	static void exec()	{
		RamdomAccesTest t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_begin = make_const_iterator(input.begin());
		auto ref_begin = ref.begin();
		char32_t c_input, c_ref;
		for(size_t i=0;i<ref.size();i++)	{
			c_input = input_begin[i];
			c_ref = ref_begin[i];
			if (c_input!=c_ref)	{
				break;
			}
		}
		BOOST_CHECK(c_input==c_ref);

	}
};

// ramdom access. compares access with std::basic_string<char32_t>::begin and const_iterator
struct RamdomAccesTest2	{
	static void exec()	{
		RamdomAccesTest2 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_begin = make_const_iterator(input.begin());
		auto ref_begin = ref.begin();
		char32_t c_input, c_ref;
		for(size_t i=0;i<ref.size();i++)	{
			c_input = *(input_begin+i);
			c_ref   = *(ref_begin+i);
			if (c_input!=c_ref)	{
				break;
			}
		}
		BOOST_CHECK(c_input==c_ref);
	}
};


// ramdom access. compares access with std::basic_string<char32_t>::begin and const_iterator adding offset
struct RamdomAccesTest3	{
	static void exec()	{
		RamdomAccesTest3 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_it = make_const_iterator(input.begin());
		auto ref_it = ref.begin();
		char32_t c_input, c_ref;
		while(ref_it<ref.end())	{
			c_input = *input_it;
			c_ref   = *ref_it;
			if (c_input!=c_ref)	{
				break;
			}
			input_it+=2;
			ref_it+=2;
		}
		BOOST_CHECK(c_input==c_ref);
	}
};


struct RamdomAccesTest4	{
	static void exec()	{
		RamdomAccesTest4 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_end = make_const_iterator(input.end());
		auto ref_end = ref.end();
		char32_t c_input, c_ref;
		for(size_t i=0;i<ref.size();i++)	{
			c_input = *(input_end-i);
			c_ref   = *(ref_end-i);
			if (c_input!=c_ref)	{
				break;
			}
		}
		BOOST_CHECK(c_input==c_ref);
	}
};


struct RamdomAccesTest5	{
	static void exec()	{
		RamdomAccesTest5 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_it = make_const_iterator(input.end());
		auto ref_it = ref.end();
		char32_t c_input, c_ref;
		while(ref_it>=ref.begin())	{
			c_input = *input_it;
			c_ref   = *ref_it;
			if (c_input!=c_ref)	{
				break;
			}
			input_it-=2;
			ref_it-=2;
		}
		BOOST_CHECK(c_input==c_ref);
	}
};

struct RamdomAccesTest6	{
	static void exec()	{
		RamdomAccesTest6 t; t();
	}
	void operator()()	{
		using namespace unicpp;
		std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<char32_t> input = create_container<std::basic_string<char32_t>>();
		
		//all but the first code point
		auto input_begin = make_const_iterator(input.begin());
		auto input_end = make_const_iterator(input.end());
		BOOST_CHECK((input_end-input_begin)==(int)input.size());
		//cout << "(input_end-input_begin): " << (input_end-input_begin) << endl;
		//cout << "input.size(): " << input.size() << endl;
	}
};


template<typename CharT> 
struct IteratorRangeTest1	{
	static void exec()	{
		IteratorRangeTest1<CharT> t; t();
	}
	void operator()()	{
		using namespace unicpp;
		//std::basic_string<char32_t> ref = create_container<std::basic_string<char32_t>>();
		std::basic_string<CharT> input = create_container<std::basic_string<CharT>>();
		//input[input.size()-1] = 0; // error;
		input.resize(input.size()); // error;
		cout << "input.size()  " << input.size() << endl;

		auto it = make_const_iterator(input, input.begin());
//		auto begin = make_const_iterator(input.begin());
		auto end = make_const_iterator(input, input.end());
//		cout << "jlkjl " << (it!=end) << endl;
		CharT c =0;
//		int count =0;
		for(;it!=end;++it)	{				
//			cout << "p  " << (uint)*it.current() << " count: " << count++  << endl;
//			cout << "*it " << (uint)*it << endl;
			if (c == *it.base())	{
				cout << "break" << endl;
				break;
			}
			c = *it.base();
		}
		cout << "loop end" << endl;
//		BOOST_CHECK(*it==*it_ref);

	}
};


ConstIteratorTest::ConstIteratorTest()
{
	
}

ConstIteratorTest::~ConstIteratorTest()
{
}

boost::unit_test::test_suite* ConstIteratorTest::test_suite()	{
/*	Test3<char> t21; t21.exec();
	Test3<char16_t> t22; t22.exec();
	Test3<char32_t> t23; t23.exec();
	Test3<wchar_t> t24; t24.exec();
	boost::unit_test::test_suite* test_ = BOOST_TEST_SUITE("const_iterator_test.cpp");
	return test_;
*/	
	boost::unit_test::test_suite* test = BOOST_TEST_SUITE("const_iterator_test.cpp");
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, Test1>::reg(test);
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, Test2>::reg(test);
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, Test3>::reg(test);
	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, Test4>::reg(test);
//	Multiple2BoostTestRegister<char, char16_t, char32_t, wchar_t, BackInsertTest>::reg(test);

	reg_function<RamdomAccesTest>(test, &RamdomAccesTest::exec);	
	reg_function<RamdomAccesTest2>(test, &RamdomAccesTest2::exec);	
	reg_function<RamdomAccesTest3>(test, &RamdomAccesTest3::exec);	
	reg_function<RamdomAccesTest4>(test, &RamdomAccesTest4::exec);	
	reg_function<RamdomAccesTest5>(test, &RamdomAccesTest5::exec);	
	reg_function<RamdomAccesTest6>(test, &RamdomAccesTest6::exec);	


//	MultipleBoostTestRegister <char, char16_t, char32_t, wchar_t, IteratorRangeTest1>::reg(test);





	reg_function<IteratorRangeTest1<char>>(test, &IteratorRangeTest1<char>::exec);	

	using namespace unicpp;
	const_iterator<u32string::iterator>::iterator_category c1;
	log(c1);

/*	LowestCat<std::random_access_iterator_tag, std::bidirectional_iterator_tag>::Result	c2;
	log(c2);*/
/*	If<true, std::random_access_iterator_tag, std::bidirectional_iterator_tag>::Result r1;
	log(r1);
	If<false, std::random_access_iterator_tag, std::bidirectional_iterator_tag>::Result r2;
	log(r2);
	If< 
			LesserThan<	CategoryTraits< std::random_access_iterator_tag >::priority, 
						CategoryTraits< std::bidirectional_iterator_tag >::priority>::Result, 
			std::random_access_iterator_tag, 
			std::bidirectional_iterator_tag
		>::Result r3;
	log(r3);
*/
	std::vector<char32_t> l;
//	auto it = l.begin();
	auto it2 = make_const_iterator(l.begin());
	it2+3;
//	it+3;
	return test;
}

}

