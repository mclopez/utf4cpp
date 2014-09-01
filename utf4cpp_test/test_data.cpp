/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "test_data.h"

namespace test
{

struct Utf8	{
	//Utf8(int length, const char* buffer):length(length), buffer(*buffer){}
	const int length;
	const char buffer[4];
};

struct Utf16	{
	const int length;
	const char16_t buffer[2];
};

struct	CodePoint	{
	const char32_t code_point;
	const Utf8 utf8;
	const Utf16 utf16;
};

const CodePoint code_points[] = {

/*	{0x010384, {4, {'\xf0','\x90','\x8e','\x84'}}, 2, {0xd800, 0xdf84}}, 
	{0x000000, {1, {'\x00','\x00','\x00','\x00'}}, 1, {0x0000, 0x0000}},  // END
*/	
	
	{0x000041, {1, {'\x41','\x00','\x00','\x00'}}, {1, {0x0041, 0x0000}}}, 
	{0x0003a9, {2, {'\xce','\xa9','\x00','\x00'}}, {1, {0x03a9, 0x0000}}}, 

	{0x008a9e, {3, {'\xe8','\xaa','\x9e','\x00'}}, {1, {0x8a9e, 0x0000}}}, 
	{0x010384, {4, {'\xf0','\x90','\x8e','\x84'}}, {2, {0xd800, 0xdf84}}}, 
	{0x00007f, {1, {'\x7f','\x00','\x00','\x00'}}, {1, {0x007f, 0x0000}}}, 
	{0x000080, {2, {'\xc2','\x80','\x00','\x00'}}, {1, {0x0080, 0x0000}}}, 
	{0x0007ff, {2, {'\xdf','\xbf','\x00','\x00'}}, {1, {0x07ff, 0x0000}}}, 

	{0x000800, {3, {'\xe0','\xa0','\x80','\x00'}}, {1, {0x0800, 0x0000}}}, 



	{0x010000, {4, {'\xf0','\x90','\x80','\x80'}}, {2, {0xd800, 0xdc00}}}, 
	{0x10ffff, {4, {'\xf4','\x8f','\xbf','\xbf'}}, {2, {0xdbff, 0xdfff}}},  



	{0x000001, {1, {'\x01','\x00','\x00','\x00'}}, {1, {0x0001, 0x0000}}},  


	{0x000002, {1, {'\x02','\x00','\x00','\x00'}}, {1, {0x0002, 0x0000}}},  
	{0x000004, {1, {'\x04','\x00','\x00','\x00'}}, {1, {0x0004, 0x0000}}},  
	{0x000008, {1, {'\x08','\x00','\x00','\x00'}}, {1, {0x0008, 0x0000}}},  
	{0x000010, {1, {'\x10','\x00','\x00','\x00'}}, {1, {0x0010, 0x0000}}},  
	{0x000020, {1, {'\x20','\x00','\x00','\x00'}}, {1, {0x0020, 0x0000}}},  
	{0x000040, {1, {'\x40','\x00','\x00','\x00'}}, {1, {0x0040, 0x0000}}},  
	{0x000080, {2, {'\xc2','\x80','\x01','\x00'}}, {1, {0x0080, 0x0000}}},  
	{0x000100, {2, {'\xc4','\x80','\x00','\x00'}}, {1, {0x0100, 0x0000}}},  
	{0x000200, {2, {'\xc8','\x80','\x00','\x00'}}, {1, {0x0200, 0x0000}}},  
	{0x000400, {2, {'\xd0','\x80','\x00','\x00'}}, {1, {0x0400, 0x0000}}},  
	{0x000800, {3, {'\xe0','\xa0','\x80','\x00'}}, {1, {0x0800, 0x0000}}},  
	{0x001000, {3, {'\xe1','\x80','\x80','\x00'}}, {1, {0x1000, 0x0000}}},  
	{0x002000, {3, {'\xe2','\x80','\x80','\x00'}}, {1, {0x2000, 0x0000}}},  
	{0x004000, {3, {'\xe4','\x80','\x80','\x00'}}, {1, {0x4000, 0x0000}}},  
	{0x008000, {3, {'\xe8','\x80','\x80','\x00'}}, {1, {0x8000, 0x0000}}},  
	{0x010000, {4, {'\xf0','\x90','\x80','\x80'}}, {2, {0xd800, 0xdc00}}},  
	{0x020000, {4, {'\xf0','\xa0','\x80','\x80'}}, {2, {0xd840, 0xdc00}}},  
	{0x040000, {4, {'\xf1','\x80','\x80','\x80'}}, {2, {0xd8C0, 0xdc00}}},  
	{0x080000, {4, {'\xf2','\x80','\x80','\x80'}}, {2, {0xd9C0, 0xdc00}}},   
	{0x100000, {4, {'\xf4','\x80','\x80','\x80'}}, {2, {0xdbC0, 0xdc00}}},  

	{0x000000, {1, {'\x00','\x00','\x00','\x00'}}, {1, {0x0000, 0x0000}}},  // END
	{0x000000, {1, {'\x00','\x00','\x00','\x00'}}, {1, {0x0000, 0x0000}}} 
	
};
int code_points_count = 50;




TestData* TestData::_instance=0;

	
TestData::TestData()
{
	const CodePoint* cp;
	for(cp=code_points; cp!=code_points+code_points_count;++cp)	{
		if (cp->code_point==0)	break;
		
		s32.push_back(cp->code_point);
		s16.insert(s16.end(), cp->utf16.buffer, cp->utf16.buffer+cp->utf16.length);
		s8.insert(s8.end(), cp->utf8.buffer, cp->utf8.buffer+cp->utf8.length);

#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
		ws.push_back(cp->code_point);
#elif __SIZEOF_WCHAR_T__ == 2 
		ws.insert(ws.end(), cp->utf16.buffer, cp->utf16.buffer+cp->utf16.length);
#endif

	}

	for(const CodePoint*cp2=--cp; cp!=code_points-1;--cp)	{
		if (cp->code_point==0)	break;
		
		s32i.push_back(cp->code_point);
		s16i.insert(s16i.end(), cp->utf16.buffer, cp->utf16.buffer+cp->utf16.length);
		s8i.insert(s8i.end(), cp->utf8.buffer, cp->utf8.buffer+cp->utf8.length);

#if __SIZEOF_WCHAR_T__ == 4 || __WCHAR_MAX__ > 0x10000
		wsi.push_back(cp->code_point);
#elif __SIZEOF_WCHAR_T__ == 2 
		wsi.insert(wsi.end(), cp->utf16.buffer, cp->utf16.buffer+cp->utf16.length);
#endif

	}
	
}

TestData::~TestData()
{
}

}

