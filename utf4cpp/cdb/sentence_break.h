#ifndef SENTENCE_BREAK_H
#define SENTENCE_BREAK_H

#define SENTENCE_TABLE_N3

#ifdef SENTENCE_TABLE_N3
	#include "sentence_break_table_3levels_auto.h"
	namespace unicpp { namespace cdb { namespace sentencebreak {
		using namespace ::unicpp::cdb::sentencebreak::table_3levels;
	}}}
#else
	#include "sentence_break_table_2levels_auto.h"	
	namespace unicpp { namespace cdb { namespace sentencebreak {
		using namespace ::unicpp::cdb::sentencebreak::table_2levels;
	}}}
#endif

#endif // SENTENCE_BREAK_H
