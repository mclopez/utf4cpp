#ifndef UNICPP_CDB_SENTENCEBREAK_BINARY_H
#define UNICPP_CDB_SENTENCEBREAK_BINARY_H
#include <string>
#include <ostream>

namespace unicpp { namespace cdb { namespace sentencebreak { namespace binary { 

enum class PropertyValue : unsigned short {
	Other, 
	CR, 
	LF, 
	Extend, 
	Sep, 
	Format, 
	Sp, 
	Lower, 
	Upper, 
	OLetter, 
	Numeric, 
	ATerm, 
	STerm, 
	Close, 
	SContinue
};

inline
std::ostream& operator <<(std::ostream& os, PropertyValue v)	{
 switch(v)	{
		case PropertyValue::Other: os << "Other"; break;
		case PropertyValue::CR: os << "CR"; break;
		case PropertyValue::LF: os << "LF"; break;
		case PropertyValue::Extend: os << "Extend"; break;
		case PropertyValue::Sep: os << "Sep"; break;
		case PropertyValue::Format: os << "Format"; break;
		case PropertyValue::Sp: os << "Sp"; break;
		case PropertyValue::Lower: os << "Lower"; break;
		case PropertyValue::Upper: os << "Upper"; break;
		case PropertyValue::OLetter: os << "OLetter"; break;
		case PropertyValue::Numeric: os << "Numeric"; break;
		case PropertyValue::ATerm: os << "ATerm"; break;
		case PropertyValue::STerm: os << "STerm"; break;
		case PropertyValue::Close: os << "Close"; break;
		case PropertyValue::SContinue: os << "SContinue"; break;
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

 }  }  }  } // namespace ::unicpp::cdb::sentencebreak::binary
#endif
