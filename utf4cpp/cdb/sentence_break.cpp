#include "sentence_break.h"


#ifdef SENTENCE_TABLE_N3
#include "sentence_break_table_3levels_auto_impl.h"
#else
#include "sentence_break_table_2levels_auto_impl.h"	
#endif

