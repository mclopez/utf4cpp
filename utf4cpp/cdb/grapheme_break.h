#ifndef GRAPHEME_TABLE_H
#define GRAPHEME_TABLE_H

//#define GRAPHEME_TABLE_N3

#ifdef GRAPHEME_TABLE_N3
	#include "grapheme_break_table_3levels_auto.h"
	namespace unicpp { namespace cdb { namespace graphemebreak {
		using namespace ::unicpp::cdb::graphemebreak::table_3levels;
	}}}
#else
	#include "grapheme_break_table_2levels_auto.h"	
	namespace unicpp { namespace cdb { namespace graphemebreak {
		using namespace ::unicpp::cdb::graphemebreak::table_2levels;
	}}}
#endif



#endif
