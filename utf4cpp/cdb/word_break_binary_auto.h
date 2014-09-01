#ifndef UNICPP_CDB_WORDBREAK_BINARY_H
#define UNICPP_CDB_WORDBREAK_BINARY_H
#include <string>
#include <ostream>

namespace unicpp { namespace cdb { namespace wordbreak { namespace binary { 

enum class PropertyValue : unsigned short {
	Other, 
	Double_Quote, 
	Single_Quote, 
	Hebrew_Letter, 
	CR, 
	LF, 
	Newline, 
	Extend, 
	Regional_Indicator, 
	Format, 
	Katakana, 
	ALetter, 
	MidLetter, 
	MidNum, 
	MidNumLet, 
	Numeric, 
	ExtendNumLet
};

inline
std::ostream& operator <<(std::ostream& os, PropertyValue v)	{
 switch(v)	{
		case PropertyValue::Other: os << "Other"; break;
		case PropertyValue::Double_Quote: os << "Double_Quote"; break;
		case PropertyValue::Single_Quote: os << "Single_Quote"; break;
		case PropertyValue::Hebrew_Letter: os << "Hebrew_Letter"; break;
		case PropertyValue::CR: os << "CR"; break;
		case PropertyValue::LF: os << "LF"; break;
		case PropertyValue::Newline: os << "Newline"; break;
		case PropertyValue::Extend: os << "Extend"; break;
		case PropertyValue::Regional_Indicator: os << "Regional_Indicator"; break;
		case PropertyValue::Format: os << "Format"; break;
		case PropertyValue::Katakana: os << "Katakana"; break;
		case PropertyValue::ALetter: os << "ALetter"; break;
		case PropertyValue::MidLetter: os << "MidLetter"; break;
		case PropertyValue::MidNum: os << "MidNum"; break;
		case PropertyValue::MidNumLet: os << "MidNumLet"; break;
		case PropertyValue::Numeric: os << "Numeric"; break;
		case PropertyValue::ExtendNumLet: os << "ExtendNumLet"; break;
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

 }  }  }  } // namespace ::unicpp::cdb::wordbreak::binary
#endif
