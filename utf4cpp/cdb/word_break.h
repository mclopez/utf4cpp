#ifndef WORD_BREAK_H
#define WORD_BREAK_H

#define WORD_TABLE_N3

#ifdef WORD_TABLE_N3
	#include "word_break_table_3levels_auto.h"
	namespace unicpp { namespace cdb { namespace wordbreak {
		using namespace ::unicpp::cdb::wordbreak::table_3levels;
	}}}
#else
	#include "word_break_table_2levels_auto.h"	
	namespace unicpp { namespace cdb { namespace wordbreak {
		using namespace ::unicpp::cdb::wordbreak::table_2levels;
	}}}
#endif



#endif
