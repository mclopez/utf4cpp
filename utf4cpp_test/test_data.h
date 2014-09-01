/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef TESTDATA_H
#define TESTDATA_H

#include <string>

namespace test
{


 
class TestData {

public:
	TestData();
	~TestData();


	std::u32string s32;
	std::u16string s16;
	std::wstring ws;
	std::string s8;

	std::u32string s32i;
	std::u16string s16i;
	std::wstring wsi;
	std::string s8i;

	static inline const TestData& get()	{
		if (!_instance)	{
		
			_instance = new TestData();
			//test::insert_test();
		}
		return *_instance;
	}

private:
	static TestData* _instance;


};


template<typename T> struct TypeInfo;

#define PUBLISH_TYPE(T) \
	template<> struct TypeInfo<T>	{ \
		static const std::string name(){return #T;}\
	};\
/*	
template<> struct TypeInfo<char>	{
	static const std::string name(){return "char";}
};
*/
PUBLISH_TYPE(char);
PUBLISH_TYPE(char16_t);
PUBLISH_TYPE(char32_t);
PUBLISH_TYPE(wchar_t);
PUBLISH_TYPE(std::string);
PUBLISH_TYPE(std::u16string);
PUBLISH_TYPE(std::u32string);
PUBLISH_TYPE(std::wstring);

template<typename T> struct Data;

/*
template<> struct Data<std::string>	{
	static const std::string& get()	{
		return TestData::get().s8;
	}
	static const std::string& get_i()	{
		return TestData::get().s8i;
	}
	
	static const std::string name()	{
		return "std::string";
	}
	static size_t size()	{
		return get().size();
	}
};

template<> struct Data<std::u16string>	{
	static const std::u16string& get()	{
		return TestData::get().s16;
	}
	static const std::u16string& get_i()	{
		return TestData::get().s16i;
	}
	static const std::string name()	{
		return "std::u16string";
	}
	static size_t size()	{
		return get().size();
	}
};

template<> struct Data<std::u32string>	{
	static const std::u32string& get()	{
		return TestData::get().s32;
	}
	static const std::u32string& get_i()	{
		return TestData::get().s32i;
	}
	static const std::string name()	{
		return "std::u32string";
	}
	static size_t size()	{
		return get().size();
	}
};

template<> struct Data<std::wstring>	{
	static const std::wstring& get()	{
		return TestData::get().ws;
	}
	static const std::wstring& get_i()	{
		return TestData::get().wsi;
	}
	static const std::string name()	{
		return "std::wstring";
	}
	static size_t size()	{
		return get().size();
	}
};
*/

template<typename Cont, typename T= typename Cont::value_type>	
Cont create_container()	{
	Cont cont(Data<T>::get(),Data<T>::size());
	return cont;
}

template<typename Cont, typename T= typename Cont::value_type>	
Cont create_container_inv()	{
	Cont cont(Data<T>::get_i(),Data<T>::size());
	return cont;
}

template<> struct Data<char>	{
	static const char* get()	{
		return TestData::get().s8.c_str();
	}
	static const char* get_i()	{
		return TestData::get().s8i.c_str();
	}
	
	static const std::string name()	{
		//return "char";
		return TypeInfo<char>::name();
	}
	static size_t size()	{
		return TestData::get().s8.size();
	}
};

template<> struct Data<char16_t>	{
	static const char16_t* get()	{
		return TestData::get().s16.c_str();
	}
	static const char16_t* get_i()	{
		return TestData::get().s16i.c_str();
	}
	static const std::string name()	{
		return "char16_t";
	}
	static size_t size()	{
		return TestData::get().s16.size();
	}
};

template<> struct Data<char32_t>	{
	static const char32_t* get()	{
		return TestData::get().s32.c_str();
	}
	static const char32_t* get_i()	{
		return TestData::get().s32i.c_str();
	}
	static const std::string name()	{
		return "char32_t";
	}
	static size_t size()	{
		return TestData::get().s32.size();
	}
};

template<> struct Data<wchar_t>	{
	static const wchar_t* get()	{
		return TestData::get().ws.c_str();
	}
	static const wchar_t* get_i()	{
		return TestData::get().wsi.c_str();
	}
	static const std::string name()	{
		return "wchar_t";
	}
	static size_t size()	{
		return TestData::get().ws.size();
	}
	
};



}

#endif // TESTDATA_H
