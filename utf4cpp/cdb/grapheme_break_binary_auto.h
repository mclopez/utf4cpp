#ifndef UNICPP_CDB_GRAPHEMEBREAK_BINARY_H
#define UNICPP_CDB_GRAPHEMEBREAK_BINARY_H
#include <string>
#include <ostream>

namespace unicpp { namespace cdb { namespace graphemebreak { namespace binary { 

enum class PropertyValue : unsigned short {
	Other, 
	CR, 
	LF, 
	Control, 
	Extend, 
	Regional_Indicator, 
	SpacingMark, 
	L, 
	V, 
	T, 
	LV, 
	LVT
};

inline
std::ostream& operator <<(std::ostream& os, PropertyValue v)	{
 switch(v)	{
		case PropertyValue::Other: os << "Other"; break;
		case PropertyValue::CR: os << "CR"; break;
		case PropertyValue::LF: os << "LF"; break;
		case PropertyValue::Control: os << "Control"; break;
		case PropertyValue::Extend: os << "Extend"; break;
		case PropertyValue::Regional_Indicator: os << "Regional_Indicator"; break;
		case PropertyValue::SpacingMark: os << "SpacingMark"; break;
		case PropertyValue::L: os << "L"; break;
		case PropertyValue::V: os << "V"; break;
		case PropertyValue::T: os << "T"; break;
		case PropertyValue::LV: os << "LV"; break;
		case PropertyValue::LVT: os << "LVT"; break;
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

 }  }  }  } // namespace ::unicpp::cdb::graphemebreak::binary
#endif
