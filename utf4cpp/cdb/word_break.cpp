
#include "word_break.h"




#ifdef WORD_TABLE_N3
#include "word_break_table_3levels_auto_impl.h"
#else
#include "word_break_table_2levels_auto_impl.h"	
#endif
