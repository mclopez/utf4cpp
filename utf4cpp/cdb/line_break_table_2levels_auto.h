#ifndef UTF4CPP_CDB_LINEBREAK_TABLE_2LEVELS_H
#define UTF4CPP_CDB_LINEBREAK_TABLE_2LEVELS_H

#include <string> 
#include <ostream> 

namespace unicpp { namespace cdb { namespace linebreak { namespace table_2levels { 

enum class PropertyValue : unsigned char {
	Other
};

inline
std::ostream& operator <<(std::ostream& os, PropertyValue v)	{
 switch(v)	{
		case PropertyValue::Other: os << "Other"; break;
		default:
			os << "unknown";
	}
	return os;
}


PropertyValue get_value(char32_t cp);

 }  }  }  } // namespace ::unicpp::cdb::linebreak::table_2levels
#endif
