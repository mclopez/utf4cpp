
#include "line_break_binary_auto.h"
#include <algorithm>

namespace unicpp { namespace cdb { namespace linebreak { namespace binary { 

const int values_size = 0;

typedef PropertyValue PV;

const RangePropertyValue values[] = {
};

PV get_value(char32_t cp)	{
	const RangePropertyValue* end = values + values_size;
	RangePropertyValue v;
	v.begin = cp;
	v.end = cp;
	const RangePropertyValue* it = std::lower_bound(values, end, v);
	if (it!=end && v.begin>= it->begin && v.end<=it->end)	{
		return it->value;
	}
	return PV::Other;
}

 }  }  }  } // namespace ::unicpp::cdb::linebreak::binary
