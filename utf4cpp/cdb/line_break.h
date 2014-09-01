#ifndef LINE_TABLE_H
#define LINE_TABLE_H

//#define LINE_TABLE_N3

#ifdef LINE_TABLE_N3
	#include "line_break_table_3levels_auto.h"
	namespace unicpp { namespace cdb { namespace linebreak {
		using namespace ::unicpp::cdb::linebreak::table_3levels;
	}}}
#else
	#include "line_break_table_2levels_auto.h"	
	namespace unicpp { namespace cdb { namespace linebreak {
		using namespace ::unicpp::cdb::linebreak::table_2levels;
	}}}
#endif

#include "line_break_table_data.h"

#endif
