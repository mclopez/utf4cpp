#ifndef UTF4CPP_CDB_LINEBREAK_BINARY_H
#define UTF4CPP_CDB_LINEBREAK_BINARY_H
#include <string>
#include <ostream>


namespace unicpp { namespace cdb { namespace linebreak { namespace binary { 

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

struct RangePropertyValue	{
	char32_t begin;
	char32_t end;
	PropertyValue value;
};

inline
bool operator<(const RangePropertyValue& p1, const RangePropertyValue& p2)	{
		return p1.end < p2.end;
}

PropertyValue get_value(char32_t cp);

 }  }  }  } // namespace ::unicpp::cdb::linebreak::binary
#endif
