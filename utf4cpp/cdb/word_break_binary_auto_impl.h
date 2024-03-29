
#include "word_break_binary_auto.h"
#include <algorithm>

namespace unicpp { namespace cdb { namespace wordbreak { namespace binary { 

const int values_size = 944;

typedef PropertyValue PV;

const RangePropertyValue values[] = {
	{0xa, 0xa, PV::LF }   , 
	{0xb, 0xc, PV::Newline }   , 
	{0xd, 0xd, PV::CR }   , 
	{0x22, 0x22, PV::Double_Quote }   , 
	{0x27, 0x27, PV::Single_Quote }   , 
	{0x2c, 0x2c, PV::MidNum }   , 
	{0x2e, 0x2e, PV::MidNumLet }   , 
	{0x30, 0x39, PV::Numeric }   , 
	{0x3a, 0x3a, PV::MidLetter }   , 
	{0x3b, 0x3b, PV::MidNum }   , 
	{0x41, 0x5a, PV::ALetter }   , 
	{0x5f, 0x5f, PV::ExtendNumLet }   , 
	{0x61, 0x7a, PV::ALetter }   , 
	{0x85, 0x85, PV::Newline }   , 
	{0xaa, 0xaa, PV::ALetter }   , 
	{0xad, 0xad, PV::Format }   , 
	{0xb5, 0xb5, PV::ALetter }   , 
	{0xb7, 0xb7, PV::MidLetter }   , 
	{0xba, 0xba, PV::ALetter }   , 
	{0xc0, 0xd6, PV::ALetter }   , 
	{0xd8, 0xf6, PV::ALetter }   , 
	{0xf8, 0x1ba, PV::ALetter }   , 
	{0x1bb, 0x1bb, PV::ALetter }   , 
	{0x1bc, 0x1bf, PV::ALetter }   , 
	{0x1c0, 0x1c3, PV::ALetter }   , 
	{0x1c4, 0x293, PV::ALetter }   , 
	{0x294, 0x294, PV::ALetter }   , 
	{0x295, 0x2af, PV::ALetter }   , 
	{0x2b0, 0x2c1, PV::ALetter }   , 
	{0x2c6, 0x2d1, PV::ALetter }   , 
	{0x2d7, 0x2d7, PV::MidLetter }   , 
	{0x2e0, 0x2e4, PV::ALetter }   , 
	{0x2ec, 0x2ec, PV::ALetter }   , 
	{0x2ee, 0x2ee, PV::ALetter }   , 
	{0x300, 0x36f, PV::Extend }   , 
	{0x370, 0x373, PV::ALetter }   , 
	{0x374, 0x374, PV::ALetter }   , 
	{0x376, 0x377, PV::ALetter }   , 
	{0x37a, 0x37a, PV::ALetter }   , 
	{0x37b, 0x37d, PV::ALetter }   , 
	{0x37e, 0x37e, PV::MidNum }   , 
	{0x386, 0x386, PV::ALetter }   , 
	{0x387, 0x387, PV::MidLetter }   , 
	{0x388, 0x38a, PV::ALetter }   , 
	{0x38c, 0x38c, PV::ALetter }   , 
	{0x38e, 0x3a1, PV::ALetter }   , 
	{0x3a3, 0x3f5, PV::ALetter }   , 
	{0x3f7, 0x481, PV::ALetter }   , 
	{0x483, 0x487, PV::Extend }   , 
	{0x488, 0x489, PV::Extend }   , 
	{0x48a, 0x527, PV::ALetter }   , 
	{0x531, 0x556, PV::ALetter }   , 
	{0x559, 0x559, PV::ALetter }   , 
	{0x561, 0x587, PV::ALetter }   , 
	{0x589, 0x589, PV::MidNum }   , 
	{0x591, 0x5bd, PV::Extend }   , 
	{0x5bf, 0x5bf, PV::Extend }   , 
	{0x5c1, 0x5c2, PV::Extend }   , 
	{0x5c4, 0x5c5, PV::Extend }   , 
	{0x5c7, 0x5c7, PV::Extend }   , 
	{0x5d0, 0x5ea, PV::Hebrew_Letter }   , 
	{0x5f0, 0x5f2, PV::Hebrew_Letter }   , 
	{0x5f3, 0x5f3, PV::ALetter }   , 
	{0x5f4, 0x5f4, PV::MidLetter }   , 
	{0x600, 0x604, PV::Format }   , 
	{0x60c, 0x60d, PV::MidNum }   , 
	{0x610, 0x61a, PV::Extend }   , 
	{0x61c, 0x61c, PV::Format }   , 
	{0x620, 0x63f, PV::ALetter }   , 
	{0x640, 0x640, PV::ALetter }   , 
	{0x641, 0x64a, PV::ALetter }   , 
	{0x64b, 0x65f, PV::Extend }   , 
	{0x660, 0x669, PV::Numeric }   , 
	{0x66b, 0x66b, PV::Numeric }   , 
	{0x66c, 0x66c, PV::MidNum }   , 
	{0x66e, 0x66f, PV::ALetter }   , 
	{0x670, 0x670, PV::Extend }   , 
	{0x671, 0x6d3, PV::ALetter }   , 
	{0x6d5, 0x6d5, PV::ALetter }   , 
	{0x6d6, 0x6dc, PV::Extend }   , 
	{0x6dd, 0x6dd, PV::Format }   , 
	{0x6df, 0x6e4, PV::Extend }   , 
	{0x6e5, 0x6e6, PV::ALetter }   , 
	{0x6e7, 0x6e8, PV::Extend }   , 
	{0x6ea, 0x6ed, PV::Extend }   , 
	{0x6ee, 0x6ef, PV::ALetter }   , 
	{0x6f0, 0x6f9, PV::Numeric }   , 
	{0x6fa, 0x6fc, PV::ALetter }   , 
	{0x6ff, 0x6ff, PV::ALetter }   , 
	{0x70f, 0x70f, PV::Format }   , 
	{0x710, 0x710, PV::ALetter }   , 
	{0x711, 0x711, PV::Extend }   , 
	{0x712, 0x72f, PV::ALetter }   , 
	{0x730, 0x74a, PV::Extend }   , 
	{0x74d, 0x7a5, PV::ALetter }   , 
	{0x7a6, 0x7b0, PV::Extend }   , 
	{0x7b1, 0x7b1, PV::ALetter }   , 
	{0x7c0, 0x7c9, PV::Numeric }   , 
	{0x7ca, 0x7ea, PV::ALetter }   , 
	{0x7eb, 0x7f3, PV::Extend }   , 
	{0x7f4, 0x7f5, PV::ALetter }   , 
	{0x7f8, 0x7f8, PV::MidNum }   , 
	{0x7fa, 0x7fa, PV::ALetter }   , 
	{0x800, 0x815, PV::ALetter }   , 
	{0x816, 0x819, PV::Extend }   , 
	{0x81a, 0x81a, PV::ALetter }   , 
	{0x81b, 0x823, PV::Extend }   , 
	{0x824, 0x824, PV::ALetter }   , 
	{0x825, 0x827, PV::Extend }   , 
	{0x828, 0x828, PV::ALetter }   , 
	{0x829, 0x82d, PV::Extend }   , 
	{0x840, 0x858, PV::ALetter }   , 
	{0x859, 0x85b, PV::Extend }   , 
	{0x8a0, 0x8a0, PV::ALetter }   , 
	{0x8a2, 0x8ac, PV::ALetter }   , 
	{0x8e4, 0x8fe, PV::Extend }   , 
	{0x900, 0x902, PV::Extend }   , 
	{0x903, 0x903, PV::Extend }   , 
	{0x904, 0x939, PV::ALetter }   , 
	{0x93a, 0x93a, PV::Extend }   , 
	{0x93b, 0x93b, PV::Extend }   , 
	{0x93c, 0x93c, PV::Extend }   , 
	{0x93d, 0x93d, PV::ALetter }   , 
	{0x93e, 0x940, PV::Extend }   , 
	{0x941, 0x948, PV::Extend }   , 
	{0x949, 0x94c, PV::Extend }   , 
	{0x94d, 0x94d, PV::Extend }   , 
	{0x94e, 0x94f, PV::Extend }   , 
	{0x950, 0x950, PV::ALetter }   , 
	{0x951, 0x957, PV::Extend }   , 
	{0x958, 0x961, PV::ALetter }   , 
	{0x962, 0x963, PV::Extend }   , 
	{0x966, 0x96f, PV::Numeric }   , 
	{0x971, 0x971, PV::ALetter }   , 
	{0x972, 0x977, PV::ALetter }   , 
	{0x979, 0x97f, PV::ALetter }   , 
	{0x981, 0x981, PV::Extend }   , 
	{0x982, 0x983, PV::Extend }   , 
	{0x985, 0x98c, PV::ALetter }   , 
	{0x98f, 0x990, PV::ALetter }   , 
	{0x993, 0x9a8, PV::ALetter }   , 
	{0x9aa, 0x9b0, PV::ALetter }   , 
	{0x9b2, 0x9b2, PV::ALetter }   , 
	{0x9b6, 0x9b9, PV::ALetter }   , 
	{0x9bc, 0x9bc, PV::Extend }   , 
	{0x9bd, 0x9bd, PV::ALetter }   , 
	{0x9be, 0x9c0, PV::Extend }   , 
	{0x9c1, 0x9c4, PV::Extend }   , 
	{0x9c7, 0x9c8, PV::Extend }   , 
	{0x9cb, 0x9cc, PV::Extend }   , 
	{0x9cd, 0x9cd, PV::Extend }   , 
	{0x9ce, 0x9ce, PV::ALetter }   , 
	{0x9d7, 0x9d7, PV::Extend }   , 
	{0x9dc, 0x9dd, PV::ALetter }   , 
	{0x9df, 0x9e1, PV::ALetter }   , 
	{0x9e2, 0x9e3, PV::Extend }   , 
	{0x9e6, 0x9ef, PV::Numeric }   , 
	{0x9f0, 0x9f1, PV::ALetter }   , 
	{0xa01, 0xa02, PV::Extend }   , 
	{0xa03, 0xa03, PV::Extend }   , 
	{0xa05, 0xa0a, PV::ALetter }   , 
	{0xa0f, 0xa10, PV::ALetter }   , 
	{0xa13, 0xa28, PV::ALetter }   , 
	{0xa2a, 0xa30, PV::ALetter }   , 
	{0xa32, 0xa33, PV::ALetter }   , 
	{0xa35, 0xa36, PV::ALetter }   , 
	{0xa38, 0xa39, PV::ALetter }   , 
	{0xa3c, 0xa3c, PV::Extend }   , 
	{0xa3e, 0xa40, PV::Extend }   , 
	{0xa41, 0xa42, PV::Extend }   , 
	{0xa47, 0xa48, PV::Extend }   , 
	{0xa4b, 0xa4d, PV::Extend }   , 
	{0xa51, 0xa51, PV::Extend }   , 
	{0xa59, 0xa5c, PV::ALetter }   , 
	{0xa5e, 0xa5e, PV::ALetter }   , 
	{0xa66, 0xa6f, PV::Numeric }   , 
	{0xa70, 0xa71, PV::Extend }   , 
	{0xa72, 0xa74, PV::ALetter }   , 
	{0xa75, 0xa75, PV::Extend }   , 
	{0xa81, 0xa82, PV::Extend }   , 
	{0xa83, 0xa83, PV::Extend }   , 
	{0xa85, 0xa8d, PV::ALetter }   , 
	{0xa8f, 0xa91, PV::ALetter }   , 
	{0xa93, 0xaa8, PV::ALetter }   , 
	{0xaaa, 0xab0, PV::ALetter }   , 
	{0xab2, 0xab3, PV::ALetter }   , 
	{0xab5, 0xab9, PV::ALetter }   , 
	{0xabc, 0xabc, PV::Extend }   , 
	{0xabd, 0xabd, PV::ALetter }   , 
	{0xabe, 0xac0, PV::Extend }   , 
	{0xac1, 0xac5, PV::Extend }   , 
	{0xac7, 0xac8, PV::Extend }   , 
	{0xac9, 0xac9, PV::Extend }   , 
	{0xacb, 0xacc, PV::Extend }   , 
	{0xacd, 0xacd, PV::Extend }   , 
	{0xad0, 0xad0, PV::ALetter }   , 
	{0xae0, 0xae1, PV::ALetter }   , 
	{0xae2, 0xae3, PV::Extend }   , 
	{0xae6, 0xaef, PV::Numeric }   , 
	{0xb01, 0xb01, PV::Extend }   , 
	{0xb02, 0xb03, PV::Extend }   , 
	{0xb05, 0xb0c, PV::ALetter }   , 
	{0xb0f, 0xb10, PV::ALetter }   , 
	{0xb13, 0xb28, PV::ALetter }   , 
	{0xb2a, 0xb30, PV::ALetter }   , 
	{0xb32, 0xb33, PV::ALetter }   , 
	{0xb35, 0xb39, PV::ALetter }   , 
	{0xb3c, 0xb3c, PV::Extend }   , 
	{0xb3d, 0xb3d, PV::ALetter }   , 
	{0xb3e, 0xb3e, PV::Extend }   , 
	{0xb3f, 0xb3f, PV::Extend }   , 
	{0xb40, 0xb40, PV::Extend }   , 
	{0xb41, 0xb44, PV::Extend }   , 
	{0xb47, 0xb48, PV::Extend }   , 
	{0xb4b, 0xb4c, PV::Extend }   , 
	{0xb4d, 0xb4d, PV::Extend }   , 
	{0xb56, 0xb56, PV::Extend }   , 
	{0xb57, 0xb57, PV::Extend }   , 
	{0xb5c, 0xb5d, PV::ALetter }   , 
	{0xb5f, 0xb61, PV::ALetter }   , 
	{0xb62, 0xb63, PV::Extend }   , 
	{0xb66, 0xb6f, PV::Numeric }   , 
	{0xb71, 0xb71, PV::ALetter }   , 
	{0xb82, 0xb82, PV::Extend }   , 
	{0xb83, 0xb83, PV::ALetter }   , 
	{0xb85, 0xb8a, PV::ALetter }   , 
	{0xb8e, 0xb90, PV::ALetter }   , 
	{0xb92, 0xb95, PV::ALetter }   , 
	{0xb99, 0xb9a, PV::ALetter }   , 
	{0xb9c, 0xb9c, PV::ALetter }   , 
	{0xb9e, 0xb9f, PV::ALetter }   , 
	{0xba3, 0xba4, PV::ALetter }   , 
	{0xba8, 0xbaa, PV::ALetter }   , 
	{0xbae, 0xbb9, PV::ALetter }   , 
	{0xbbe, 0xbbf, PV::Extend }   , 
	{0xbc0, 0xbc0, PV::Extend }   , 
	{0xbc1, 0xbc2, PV::Extend }   , 
	{0xbc6, 0xbc8, PV::Extend }   , 
	{0xbca, 0xbcc, PV::Extend }   , 
	{0xbcd, 0xbcd, PV::Extend }   , 
	{0xbd0, 0xbd0, PV::ALetter }   , 
	{0xbd7, 0xbd7, PV::Extend }   , 
	{0xbe6, 0xbef, PV::Numeric }   , 
	{0xc01, 0xc03, PV::Extend }   , 
	{0xc05, 0xc0c, PV::ALetter }   , 
	{0xc0e, 0xc10, PV::ALetter }   , 
	{0xc12, 0xc28, PV::ALetter }   , 
	{0xc2a, 0xc33, PV::ALetter }   , 
	{0xc35, 0xc39, PV::ALetter }   , 
	{0xc3d, 0xc3d, PV::ALetter }   , 
	{0xc3e, 0xc40, PV::Extend }   , 
	{0xc41, 0xc44, PV::Extend }   , 
	{0xc46, 0xc48, PV::Extend }   , 
	{0xc4a, 0xc4d, PV::Extend }   , 
	{0xc55, 0xc56, PV::Extend }   , 
	{0xc58, 0xc59, PV::ALetter }   , 
	{0xc60, 0xc61, PV::ALetter }   , 
	{0xc62, 0xc63, PV::Extend }   , 
	{0xc66, 0xc6f, PV::Numeric }   , 
	{0xc82, 0xc83, PV::Extend }   , 
	{0xc85, 0xc8c, PV::ALetter }   , 
	{0xc8e, 0xc90, PV::ALetter }   , 
	{0xc92, 0xca8, PV::ALetter }   , 
	{0xcaa, 0xcb3, PV::ALetter }   , 
	{0xcb5, 0xcb9, PV::ALetter }   , 
	{0xcbc, 0xcbc, PV::Extend }   , 
	{0xcbd, 0xcbd, PV::ALetter }   , 
	{0xcbe, 0xcbe, PV::Extend }   , 
	{0xcbf, 0xcbf, PV::Extend }   , 
	{0xcc0, 0xcc4, PV::Extend }   , 
	{0xcc6, 0xcc6, PV::Extend }   , 
	{0xcc7, 0xcc8, PV::Extend }   , 
	{0xcca, 0xccb, PV::Extend }   , 
	{0xccc, 0xccd, PV::Extend }   , 
	{0xcd5, 0xcd6, PV::Extend }   , 
	{0xcde, 0xcde, PV::ALetter }   , 
	{0xce0, 0xce1, PV::ALetter }   , 
	{0xce2, 0xce3, PV::Extend }   , 
	{0xce6, 0xcef, PV::Numeric }   , 
	{0xcf1, 0xcf2, PV::ALetter }   , 
	{0xd02, 0xd03, PV::Extend }   , 
	{0xd05, 0xd0c, PV::ALetter }   , 
	{0xd0e, 0xd10, PV::ALetter }   , 
	{0xd12, 0xd3a, PV::ALetter }   , 
	{0xd3d, 0xd3d, PV::ALetter }   , 
	{0xd3e, 0xd40, PV::Extend }   , 
	{0xd41, 0xd44, PV::Extend }   , 
	{0xd46, 0xd48, PV::Extend }   , 
	{0xd4a, 0xd4c, PV::Extend }   , 
	{0xd4d, 0xd4d, PV::Extend }   , 
	{0xd4e, 0xd4e, PV::ALetter }   , 
	{0xd57, 0xd57, PV::Extend }   , 
	{0xd60, 0xd61, PV::ALetter }   , 
	{0xd62, 0xd63, PV::Extend }   , 
	{0xd66, 0xd6f, PV::Numeric }   , 
	{0xd7a, 0xd7f, PV::ALetter }   , 
	{0xd82, 0xd83, PV::Extend }   , 
	{0xd85, 0xd96, PV::ALetter }   , 
	{0xd9a, 0xdb1, PV::ALetter }   , 
	{0xdb3, 0xdbb, PV::ALetter }   , 
	{0xdbd, 0xdbd, PV::ALetter }   , 
	{0xdc0, 0xdc6, PV::ALetter }   , 
	{0xdca, 0xdca, PV::Extend }   , 
	{0xdcf, 0xdd1, PV::Extend }   , 
	{0xdd2, 0xdd4, PV::Extend }   , 
	{0xdd6, 0xdd6, PV::Extend }   , 
	{0xdd8, 0xddf, PV::Extend }   , 
	{0xdf2, 0xdf3, PV::Extend }   , 
	{0xe31, 0xe31, PV::Extend }   , 
	{0xe34, 0xe3a, PV::Extend }   , 
	{0xe47, 0xe4e, PV::Extend }   , 
	{0xe50, 0xe59, PV::Numeric }   , 
	{0xeb1, 0xeb1, PV::Extend }   , 
	{0xeb4, 0xeb9, PV::Extend }   , 
	{0xebb, 0xebc, PV::Extend }   , 
	{0xec8, 0xecd, PV::Extend }   , 
	{0xed0, 0xed9, PV::Numeric }   , 
	{0xf00, 0xf00, PV::ALetter }   , 
	{0xf18, 0xf19, PV::Extend }   , 
	{0xf20, 0xf29, PV::Numeric }   , 
	{0xf35, 0xf35, PV::Extend }   , 
	{0xf37, 0xf37, PV::Extend }   , 
	{0xf39, 0xf39, PV::Extend }   , 
	{0xf3e, 0xf3f, PV::Extend }   , 
	{0xf40, 0xf47, PV::ALetter }   , 
	{0xf49, 0xf6c, PV::ALetter }   , 
	{0xf71, 0xf7e, PV::Extend }   , 
	{0xf7f, 0xf7f, PV::Extend }   , 
	{0xf80, 0xf84, PV::Extend }   , 
	{0xf86, 0xf87, PV::Extend }   , 
	{0xf88, 0xf8c, PV::ALetter }   , 
	{0xf8d, 0xf97, PV::Extend }   , 
	{0xf99, 0xfbc, PV::Extend }   , 
	{0xfc6, 0xfc6, PV::Extend }   , 
	{0x102b, 0x102c, PV::Extend }   , 
	{0x102d, 0x1030, PV::Extend }   , 
	{0x1031, 0x1031, PV::Extend }   , 
	{0x1032, 0x1037, PV::Extend }   , 
	{0x1038, 0x1038, PV::Extend }   , 
	{0x1039, 0x103a, PV::Extend }   , 
	{0x103b, 0x103c, PV::Extend }   , 
	{0x103d, 0x103e, PV::Extend }   , 
	{0x1040, 0x1049, PV::Numeric }   , 
	{0x1056, 0x1057, PV::Extend }   , 
	{0x1058, 0x1059, PV::Extend }   , 
	{0x105e, 0x1060, PV::Extend }   , 
	{0x1062, 0x1064, PV::Extend }   , 
	{0x1067, 0x106d, PV::Extend }   , 
	{0x1071, 0x1074, PV::Extend }   , 
	{0x1082, 0x1082, PV::Extend }   , 
	{0x1083, 0x1084, PV::Extend }   , 
	{0x1085, 0x1086, PV::Extend }   , 
	{0x1087, 0x108c, PV::Extend }   , 
	{0x108d, 0x108d, PV::Extend }   , 
	{0x108f, 0x108f, PV::Extend }   , 
	{0x1090, 0x1099, PV::Numeric }   , 
	{0x109a, 0x109c, PV::Extend }   , 
	{0x109d, 0x109d, PV::Extend }   , 
	{0x10a0, 0x10c5, PV::ALetter }   , 
	{0x10c7, 0x10c7, PV::ALetter }   , 
	{0x10cd, 0x10cd, PV::ALetter }   , 
	{0x10d0, 0x10fa, PV::ALetter }   , 
	{0x10fc, 0x10fc, PV::ALetter }   , 
	{0x10fd, 0x1248, PV::ALetter }   , 
	{0x124a, 0x124d, PV::ALetter }   , 
	{0x1250, 0x1256, PV::ALetter }   , 
	{0x1258, 0x1258, PV::ALetter }   , 
	{0x125a, 0x125d, PV::ALetter }   , 
	{0x1260, 0x1288, PV::ALetter }   , 
	{0x128a, 0x128d, PV::ALetter }   , 
	{0x1290, 0x12b0, PV::ALetter }   , 
	{0x12b2, 0x12b5, PV::ALetter }   , 
	{0x12b8, 0x12be, PV::ALetter }   , 
	{0x12c0, 0x12c0, PV::ALetter }   , 
	{0x12c2, 0x12c5, PV::ALetter }   , 
	{0x12c8, 0x12d6, PV::ALetter }   , 
	{0x12d8, 0x1310, PV::ALetter }   , 
	{0x1312, 0x1315, PV::ALetter }   , 
	{0x1318, 0x135a, PV::ALetter }   , 
	{0x135d, 0x135f, PV::Extend }   , 
	{0x1380, 0x138f, PV::ALetter }   , 
	{0x13a0, 0x13f4, PV::ALetter }   , 
	{0x1401, 0x166c, PV::ALetter }   , 
	{0x166f, 0x167f, PV::ALetter }   , 
	{0x1681, 0x169a, PV::ALetter }   , 
	{0x16a0, 0x16ea, PV::ALetter }   , 
	{0x16ee, 0x16f0, PV::ALetter }   , 
	{0x1700, 0x170c, PV::ALetter }   , 
	{0x170e, 0x1711, PV::ALetter }   , 
	{0x1712, 0x1714, PV::Extend }   , 
	{0x1720, 0x1731, PV::ALetter }   , 
	{0x1732, 0x1734, PV::Extend }   , 
	{0x1740, 0x1751, PV::ALetter }   , 
	{0x1752, 0x1753, PV::Extend }   , 
	{0x1760, 0x176c, PV::ALetter }   , 
	{0x176e, 0x1770, PV::ALetter }   , 
	{0x1772, 0x1773, PV::Extend }   , 
	{0x17b4, 0x17b5, PV::Extend }   , 
	{0x17b6, 0x17b6, PV::Extend }   , 
	{0x17b7, 0x17bd, PV::Extend }   , 
	{0x17be, 0x17c5, PV::Extend }   , 
	{0x17c6, 0x17c6, PV::Extend }   , 
	{0x17c7, 0x17c8, PV::Extend }   , 
	{0x17c9, 0x17d3, PV::Extend }   , 
	{0x17dd, 0x17dd, PV::Extend }   , 
	{0x17e0, 0x17e9, PV::Numeric }   , 
	{0x180b, 0x180d, PV::Extend }   , 
	{0x180e, 0x180e, PV::Format }   , 
	{0x1810, 0x1819, PV::Numeric }   , 
	{0x1820, 0x1842, PV::ALetter }   , 
	{0x1843, 0x1843, PV::ALetter }   , 
	{0x1844, 0x1877, PV::ALetter }   , 
	{0x1880, 0x18a8, PV::ALetter }   , 
	{0x18a9, 0x18a9, PV::Extend }   , 
	{0x18aa, 0x18aa, PV::ALetter }   , 
	{0x18b0, 0x18f5, PV::ALetter }   , 
	{0x1900, 0x191c, PV::ALetter }   , 
	{0x1920, 0x1922, PV::Extend }   , 
	{0x1923, 0x1926, PV::Extend }   , 
	{0x1927, 0x1928, PV::Extend }   , 
	{0x1929, 0x192b, PV::Extend }   , 
	{0x1930, 0x1931, PV::Extend }   , 
	{0x1932, 0x1932, PV::Extend }   , 
	{0x1933, 0x1938, PV::Extend }   , 
	{0x1939, 0x193b, PV::Extend }   , 
	{0x1946, 0x194f, PV::Numeric }   , 
	{0x19b0, 0x19c0, PV::Extend }   , 
	{0x19c8, 0x19c9, PV::Extend }   , 
	{0x19d0, 0x19d9, PV::Numeric }   , 
	{0x1a00, 0x1a16, PV::ALetter }   , 
	{0x1a17, 0x1a18, PV::Extend }   , 
	{0x1a19, 0x1a1a, PV::Extend }   , 
	{0x1a1b, 0x1a1b, PV::Extend }   , 
	{0x1a55, 0x1a55, PV::Extend }   , 
	{0x1a56, 0x1a56, PV::Extend }   , 
	{0x1a57, 0x1a57, PV::Extend }   , 
	{0x1a58, 0x1a5e, PV::Extend }   , 
	{0x1a60, 0x1a60, PV::Extend }   , 
	{0x1a61, 0x1a61, PV::Extend }   , 
	{0x1a62, 0x1a62, PV::Extend }   , 
	{0x1a63, 0x1a64, PV::Extend }   , 
	{0x1a65, 0x1a6c, PV::Extend }   , 
	{0x1a6d, 0x1a72, PV::Extend }   , 
	{0x1a73, 0x1a7c, PV::Extend }   , 
	{0x1a7f, 0x1a7f, PV::Extend }   , 
	{0x1a80, 0x1a89, PV::Numeric }   , 
	{0x1a90, 0x1a99, PV::Numeric }   , 
	{0x1b00, 0x1b03, PV::Extend }   , 
	{0x1b04, 0x1b04, PV::Extend }   , 
	{0x1b05, 0x1b33, PV::ALetter }   , 
	{0x1b34, 0x1b34, PV::Extend }   , 
	{0x1b35, 0x1b35, PV::Extend }   , 
	{0x1b36, 0x1b3a, PV::Extend }   , 
	{0x1b3b, 0x1b3b, PV::Extend }   , 
	{0x1b3c, 0x1b3c, PV::Extend }   , 
	{0x1b3d, 0x1b41, PV::Extend }   , 
	{0x1b42, 0x1b42, PV::Extend }   , 
	{0x1b43, 0x1b44, PV::Extend }   , 
	{0x1b45, 0x1b4b, PV::ALetter }   , 
	{0x1b50, 0x1b59, PV::Numeric }   , 
	{0x1b6b, 0x1b73, PV::Extend }   , 
	{0x1b80, 0x1b81, PV::Extend }   , 
	{0x1b82, 0x1b82, PV::Extend }   , 
	{0x1b83, 0x1ba0, PV::ALetter }   , 
	{0x1ba1, 0x1ba1, PV::Extend }   , 
	{0x1ba2, 0x1ba5, PV::Extend }   , 
	{0x1ba6, 0x1ba7, PV::Extend }   , 
	{0x1ba8, 0x1ba9, PV::Extend }   , 
	{0x1baa, 0x1baa, PV::Extend }   , 
	{0x1bab, 0x1bab, PV::Extend }   , 
	{0x1bac, 0x1bad, PV::Extend }   , 
	{0x1bae, 0x1baf, PV::ALetter }   , 
	{0x1bb0, 0x1bb9, PV::Numeric }   , 
	{0x1bba, 0x1be5, PV::ALetter }   , 
	{0x1be6, 0x1be6, PV::Extend }   , 
	{0x1be7, 0x1be7, PV::Extend }   , 
	{0x1be8, 0x1be9, PV::Extend }   , 
	{0x1bea, 0x1bec, PV::Extend }   , 
	{0x1bed, 0x1bed, PV::Extend }   , 
	{0x1bee, 0x1bee, PV::Extend }   , 
	{0x1bef, 0x1bf1, PV::Extend }   , 
	{0x1bf2, 0x1bf3, PV::Extend }   , 
	{0x1c00, 0x1c23, PV::ALetter }   , 
	{0x1c24, 0x1c2b, PV::Extend }   , 
	{0x1c2c, 0x1c33, PV::Extend }   , 
	{0x1c34, 0x1c35, PV::Extend }   , 
	{0x1c36, 0x1c37, PV::Extend }   , 
	{0x1c40, 0x1c49, PV::Numeric }   , 
	{0x1c4d, 0x1c4f, PV::ALetter }   , 
	{0x1c50, 0x1c59, PV::Numeric }   , 
	{0x1c5a, 0x1c77, PV::ALetter }   , 
	{0x1c78, 0x1c7d, PV::ALetter }   , 
	{0x1cd0, 0x1cd2, PV::Extend }   , 
	{0x1cd4, 0x1ce0, PV::Extend }   , 
	{0x1ce1, 0x1ce1, PV::Extend }   , 
	{0x1ce2, 0x1ce8, PV::Extend }   , 
	{0x1ce9, 0x1cec, PV::ALetter }   , 
	{0x1ced, 0x1ced, PV::Extend }   , 
	{0x1cee, 0x1cf1, PV::ALetter }   , 
	{0x1cf2, 0x1cf3, PV::Extend }   , 
	{0x1cf4, 0x1cf4, PV::Extend }   , 
	{0x1cf5, 0x1cf6, PV::ALetter }   , 
	{0x1d00, 0x1d2b, PV::ALetter }   , 
	{0x1d2c, 0x1d6a, PV::ALetter }   , 
	{0x1d6b, 0x1d77, PV::ALetter }   , 
	{0x1d78, 0x1d78, PV::ALetter }   , 
	{0x1d79, 0x1d9a, PV::ALetter }   , 
	{0x1d9b, 0x1dbf, PV::ALetter }   , 
	{0x1dc0, 0x1de6, PV::Extend }   , 
	{0x1dfc, 0x1dff, PV::Extend }   , 
	{0x1e00, 0x1f15, PV::ALetter }   , 
	{0x1f18, 0x1f1d, PV::ALetter }   , 
	{0x1f20, 0x1f45, PV::ALetter }   , 
	{0x1f48, 0x1f4d, PV::ALetter }   , 
	{0x1f50, 0x1f57, PV::ALetter }   , 
	{0x1f59, 0x1f59, PV::ALetter }   , 
	{0x1f5b, 0x1f5b, PV::ALetter }   , 
	{0x1f5d, 0x1f5d, PV::ALetter }   , 
	{0x1f5f, 0x1f7d, PV::ALetter }   , 
	{0x1f80, 0x1fb4, PV::ALetter }   , 
	{0x1fb6, 0x1fbc, PV::ALetter }   , 
	{0x1fbe, 0x1fbe, PV::ALetter }   , 
	{0x1fc2, 0x1fc4, PV::ALetter }   , 
	{0x1fc6, 0x1fcc, PV::ALetter }   , 
	{0x1fd0, 0x1fd3, PV::ALetter }   , 
	{0x1fd6, 0x1fdb, PV::ALetter }   , 
	{0x1fe0, 0x1fec, PV::ALetter }   , 
	{0x1ff2, 0x1ff4, PV::ALetter }   , 
	{0x1ff6, 0x1ffc, PV::ALetter }   , 
	{0x200c, 0x200d, PV::Extend }   , 
	{0x200e, 0x200f, PV::Format }   , 
	{0x2018, 0x2018, PV::MidNumLet }   , 
	{0x2019, 0x2019, PV::MidNumLet }   , 
	{0x2024, 0x2024, PV::MidNumLet }   , 
	{0x2027, 0x2027, PV::MidLetter }   , 
	{0x2028, 0x2028, PV::Newline }   , 
	{0x2029, 0x2029, PV::Newline }   , 
	{0x202a, 0x202e, PV::Format }   , 
	{0x203f, 0x2040, PV::ExtendNumLet }   , 
	{0x2044, 0x2044, PV::MidNum }   , 
	{0x2054, 0x2054, PV::ExtendNumLet }   , 
	{0x2060, 0x2064, PV::Format }   , 
	{0x2066, 0x206f, PV::Format }   , 
	{0x2071, 0x2071, PV::ALetter }   , 
	{0x207f, 0x207f, PV::ALetter }   , 
	{0x2090, 0x209c, PV::ALetter }   , 
	{0x20d0, 0x20dc, PV::Extend }   , 
	{0x20dd, 0x20e0, PV::Extend }   , 
	{0x20e1, 0x20e1, PV::Extend }   , 
	{0x20e2, 0x20e4, PV::Extend }   , 
	{0x20e5, 0x20f0, PV::Extend }   , 
	{0x2102, 0x2102, PV::ALetter }   , 
	{0x2107, 0x2107, PV::ALetter }   , 
	{0x210a, 0x2113, PV::ALetter }   , 
	{0x2115, 0x2115, PV::ALetter }   , 
	{0x2119, 0x211d, PV::ALetter }   , 
	{0x2124, 0x2124, PV::ALetter }   , 
	{0x2126, 0x2126, PV::ALetter }   , 
	{0x2128, 0x2128, PV::ALetter }   , 
	{0x212a, 0x212d, PV::ALetter }   , 
	{0x212f, 0x2134, PV::ALetter }   , 
	{0x2135, 0x2138, PV::ALetter }   , 
	{0x2139, 0x2139, PV::ALetter }   , 
	{0x213c, 0x213f, PV::ALetter }   , 
	{0x2145, 0x2149, PV::ALetter }   , 
	{0x214e, 0x214e, PV::ALetter }   , 
	{0x2160, 0x2182, PV::ALetter }   , 
	{0x2183, 0x2184, PV::ALetter }   , 
	{0x2185, 0x2188, PV::ALetter }   , 
	{0x24b6, 0x24e9, PV::ALetter }   , 
	{0x2c00, 0x2c2e, PV::ALetter }   , 
	{0x2c30, 0x2c5e, PV::ALetter }   , 
	{0x2c60, 0x2c7b, PV::ALetter }   , 
	{0x2c7c, 0x2c7d, PV::ALetter }   , 
	{0x2c7e, 0x2ce4, PV::ALetter }   , 
	{0x2ceb, 0x2cee, PV::ALetter }   , 
	{0x2cef, 0x2cf1, PV::Extend }   , 
	{0x2cf2, 0x2cf3, PV::ALetter }   , 
	{0x2d00, 0x2d25, PV::ALetter }   , 
	{0x2d27, 0x2d27, PV::ALetter }   , 
	{0x2d2d, 0x2d2d, PV::ALetter }   , 
	{0x2d30, 0x2d67, PV::ALetter }   , 
	{0x2d6f, 0x2d6f, PV::ALetter }   , 
	{0x2d7f, 0x2d7f, PV::Extend }   , 
	{0x2d80, 0x2d96, PV::ALetter }   , 
	{0x2da0, 0x2da6, PV::ALetter }   , 
	{0x2da8, 0x2dae, PV::ALetter }   , 
	{0x2db0, 0x2db6, PV::ALetter }   , 
	{0x2db8, 0x2dbe, PV::ALetter }   , 
	{0x2dc0, 0x2dc6, PV::ALetter }   , 
	{0x2dc8, 0x2dce, PV::ALetter }   , 
	{0x2dd0, 0x2dd6, PV::ALetter }   , 
	{0x2dd8, 0x2dde, PV::ALetter }   , 
	{0x2de0, 0x2dff, PV::Extend }   , 
	{0x2e2f, 0x2e2f, PV::ALetter }   , 
	{0x3005, 0x3005, PV::ALetter }   , 
	{0x302a, 0x302d, PV::Extend }   , 
	{0x302e, 0x302f, PV::Extend }   , 
	{0x3031, 0x3035, PV::Katakana }   , 
	{0x303b, 0x303b, PV::ALetter }   , 
	{0x303c, 0x303c, PV::ALetter }   , 
	{0x3099, 0x309a, PV::Extend }   , 
	{0x309b, 0x309c, PV::Katakana }   , 
	{0x30a0, 0x30a0, PV::Katakana }   , 
	{0x30a1, 0x30fa, PV::Katakana }   , 
	{0x30fc, 0x30fe, PV::Katakana }   , 
	{0x30ff, 0x30ff, PV::Katakana }   , 
	{0x3105, 0x312d, PV::ALetter }   , 
	{0x3131, 0x318e, PV::ALetter }   , 
	{0x31a0, 0x31ba, PV::ALetter }   , 
	{0x31f0, 0x31ff, PV::Katakana }   , 
	{0x32d0, 0x32fe, PV::Katakana }   , 
	{0x3300, 0x3357, PV::Katakana }   , 
	{0xa000, 0xa014, PV::ALetter }   , 
	{0xa015, 0xa015, PV::ALetter }   , 
	{0xa016, 0xa48c, PV::ALetter }   , 
	{0xa4d0, 0xa4f7, PV::ALetter }   , 
	{0xa4f8, 0xa4fd, PV::ALetter }   , 
	{0xa500, 0xa60b, PV::ALetter }   , 
	{0xa60c, 0xa60c, PV::ALetter }   , 
	{0xa610, 0xa61f, PV::ALetter }   , 
	{0xa620, 0xa629, PV::Numeric }   , 
	{0xa62a, 0xa62b, PV::ALetter }   , 
	{0xa640, 0xa66d, PV::ALetter }   , 
	{0xa66e, 0xa66e, PV::ALetter }   , 
	{0xa66f, 0xa66f, PV::Extend }   , 
	{0xa670, 0xa672, PV::Extend }   , 
	{0xa674, 0xa67d, PV::Extend }   , 
	{0xa67f, 0xa67f, PV::ALetter }   , 
	{0xa680, 0xa697, PV::ALetter }   , 
	{0xa69f, 0xa69f, PV::Extend }   , 
	{0xa6a0, 0xa6e5, PV::ALetter }   , 
	{0xa6e6, 0xa6ef, PV::ALetter }   , 
	{0xa6f0, 0xa6f1, PV::Extend }   , 
	{0xa717, 0xa71f, PV::ALetter }   , 
	{0xa722, 0xa76f, PV::ALetter }   , 
	{0xa770, 0xa770, PV::ALetter }   , 
	{0xa771, 0xa787, PV::ALetter }   , 
	{0xa788, 0xa788, PV::ALetter }   , 
	{0xa78b, 0xa78e, PV::ALetter }   , 
	{0xa790, 0xa793, PV::ALetter }   , 
	{0xa7a0, 0xa7aa, PV::ALetter }   , 
	{0xa7f8, 0xa7f9, PV::ALetter }   , 
	{0xa7fa, 0xa7fa, PV::ALetter }   , 
	{0xa7fb, 0xa801, PV::ALetter }   , 
	{0xa802, 0xa802, PV::Extend }   , 
	{0xa803, 0xa805, PV::ALetter }   , 
	{0xa806, 0xa806, PV::Extend }   , 
	{0xa807, 0xa80a, PV::ALetter }   , 
	{0xa80b, 0xa80b, PV::Extend }   , 
	{0xa80c, 0xa822, PV::ALetter }   , 
	{0xa823, 0xa824, PV::Extend }   , 
	{0xa825, 0xa826, PV::Extend }   , 
	{0xa827, 0xa827, PV::Extend }   , 
	{0xa840, 0xa873, PV::ALetter }   , 
	{0xa880, 0xa881, PV::Extend }   , 
	{0xa882, 0xa8b3, PV::ALetter }   , 
	{0xa8b4, 0xa8c3, PV::Extend }   , 
	{0xa8c4, 0xa8c4, PV::Extend }   , 
	{0xa8d0, 0xa8d9, PV::Numeric }   , 
	{0xa8e0, 0xa8f1, PV::Extend }   , 
	{0xa8f2, 0xa8f7, PV::ALetter }   , 
	{0xa8fb, 0xa8fb, PV::ALetter }   , 
	{0xa900, 0xa909, PV::Numeric }   , 
	{0xa90a, 0xa925, PV::ALetter }   , 
	{0xa926, 0xa92d, PV::Extend }   , 
	{0xa930, 0xa946, PV::ALetter }   , 
	{0xa947, 0xa951, PV::Extend }   , 
	{0xa952, 0xa953, PV::Extend }   , 
	{0xa960, 0xa97c, PV::ALetter }   , 
	{0xa980, 0xa982, PV::Extend }   , 
	{0xa983, 0xa983, PV::Extend }   , 
	{0xa984, 0xa9b2, PV::ALetter }   , 
	{0xa9b3, 0xa9b3, PV::Extend }   , 
	{0xa9b4, 0xa9b5, PV::Extend }   , 
	{0xa9b6, 0xa9b9, PV::Extend }   , 
	{0xa9ba, 0xa9bb, PV::Extend }   , 
	{0xa9bc, 0xa9bc, PV::Extend }   , 
	{0xa9bd, 0xa9c0, PV::Extend }   , 
	{0xa9cf, 0xa9cf, PV::ALetter }   , 
	{0xa9d0, 0xa9d9, PV::Numeric }   , 
	{0xaa00, 0xaa28, PV::ALetter }   , 
	{0xaa29, 0xaa2e, PV::Extend }   , 
	{0xaa2f, 0xaa30, PV::Extend }   , 
	{0xaa31, 0xaa32, PV::Extend }   , 
	{0xaa33, 0xaa34, PV::Extend }   , 
	{0xaa35, 0xaa36, PV::Extend }   , 
	{0xaa40, 0xaa42, PV::ALetter }   , 
	{0xaa43, 0xaa43, PV::Extend }   , 
	{0xaa44, 0xaa4b, PV::ALetter }   , 
	{0xaa4c, 0xaa4c, PV::Extend }   , 
	{0xaa4d, 0xaa4d, PV::Extend }   , 
	{0xaa50, 0xaa59, PV::Numeric }   , 
	{0xaa7b, 0xaa7b, PV::Extend }   , 
	{0xaab0, 0xaab0, PV::Extend }   , 
	{0xaab2, 0xaab4, PV::Extend }   , 
	{0xaab7, 0xaab8, PV::Extend }   , 
	{0xaabe, 0xaabf, PV::Extend }   , 
	{0xaac1, 0xaac1, PV::Extend }   , 
	{0xaae0, 0xaaea, PV::ALetter }   , 
	{0xaaeb, 0xaaeb, PV::Extend }   , 
	{0xaaec, 0xaaed, PV::Extend }   , 
	{0xaaee, 0xaaef, PV::Extend }   , 
	{0xaaf2, 0xaaf2, PV::ALetter }   , 
	{0xaaf3, 0xaaf4, PV::ALetter }   , 
	{0xaaf5, 0xaaf5, PV::Extend }   , 
	{0xaaf6, 0xaaf6, PV::Extend }   , 
	{0xab01, 0xab06, PV::ALetter }   , 
	{0xab09, 0xab0e, PV::ALetter }   , 
	{0xab11, 0xab16, PV::ALetter }   , 
	{0xab20, 0xab26, PV::ALetter }   , 
	{0xab28, 0xab2e, PV::ALetter }   , 
	{0xabc0, 0xabe2, PV::ALetter }   , 
	{0xabe3, 0xabe4, PV::Extend }   , 
	{0xabe5, 0xabe5, PV::Extend }   , 
	{0xabe6, 0xabe7, PV::Extend }   , 
	{0xabe8, 0xabe8, PV::Extend }   , 
	{0xabe9, 0xabea, PV::Extend }   , 
	{0xabec, 0xabec, PV::Extend }   , 
	{0xabed, 0xabed, PV::Extend }   , 
	{0xabf0, 0xabf9, PV::Numeric }   , 
	{0xac00, 0xd7a3, PV::ALetter }   , 
	{0xd7b0, 0xd7c6, PV::ALetter }   , 
	{0xd7cb, 0xd7fb, PV::ALetter }   , 
	{0xfb00, 0xfb06, PV::ALetter }   , 
	{0xfb13, 0xfb17, PV::ALetter }   , 
	{0xfb1d, 0xfb1d, PV::Hebrew_Letter }   , 
	{0xfb1e, 0xfb1e, PV::Extend }   , 
	{0xfb1f, 0xfb28, PV::Hebrew_Letter }   , 
	{0xfb2a, 0xfb36, PV::Hebrew_Letter }   , 
	{0xfb38, 0xfb3c, PV::Hebrew_Letter }   , 
	{0xfb3e, 0xfb3e, PV::Hebrew_Letter }   , 
	{0xfb40, 0xfb41, PV::Hebrew_Letter }   , 
	{0xfb43, 0xfb44, PV::Hebrew_Letter }   , 
	{0xfb46, 0xfb4f, PV::Hebrew_Letter }   , 
	{0xfb50, 0xfbb1, PV::ALetter }   , 
	{0xfbd3, 0xfd3d, PV::ALetter }   , 
	{0xfd50, 0xfd8f, PV::ALetter }   , 
	{0xfd92, 0xfdc7, PV::ALetter }   , 
	{0xfdf0, 0xfdfb, PV::ALetter }   , 
	{0xfe00, 0xfe0f, PV::Extend }   , 
	{0xfe10, 0xfe10, PV::MidNum }   , 
	{0xfe13, 0xfe13, PV::MidLetter }   , 
	{0xfe14, 0xfe14, PV::MidNum }   , 
	{0xfe20, 0xfe26, PV::Extend }   , 
	{0xfe33, 0xfe34, PV::ExtendNumLet }   , 
	{0xfe4d, 0xfe4f, PV::ExtendNumLet }   , 
	{0xfe50, 0xfe50, PV::MidNum }   , 
	{0xfe52, 0xfe52, PV::MidNumLet }   , 
	{0xfe54, 0xfe54, PV::MidNum }   , 
	{0xfe55, 0xfe55, PV::MidLetter }   , 
	{0xfe70, 0xfe74, PV::ALetter }   , 
	{0xfe76, 0xfefc, PV::ALetter }   , 
	{0xfeff, 0xfeff, PV::Format }   , 
	{0xff07, 0xff07, PV::MidNumLet }   , 
	{0xff0c, 0xff0c, PV::MidNum }   , 
	{0xff0e, 0xff0e, PV::MidNumLet }   , 
	{0xff1a, 0xff1a, PV::MidLetter }   , 
	{0xff1b, 0xff1b, PV::MidNum }   , 
	{0xff21, 0xff3a, PV::ALetter }   , 
	{0xff3f, 0xff3f, PV::ExtendNumLet }   , 
	{0xff41, 0xff5a, PV::ALetter }   , 
	{0xff66, 0xff6f, PV::Katakana }   , 
	{0xff70, 0xff70, PV::Katakana }   , 
	{0xff71, 0xff9d, PV::Katakana }   , 
	{0xff9e, 0xff9f, PV::Extend }   , 
	{0xffa0, 0xffbe, PV::ALetter }   , 
	{0xffc2, 0xffc7, PV::ALetter }   , 
	{0xffca, 0xffcf, PV::ALetter }   , 
	{0xffd2, 0xffd7, PV::ALetter }   , 
	{0xffda, 0xffdc, PV::ALetter }   , 
	{0xfff9, 0xfffb, PV::Format }   , 
	{0x10000, 0x1000b, PV::ALetter }   , 
	{0x1000d, 0x10026, PV::ALetter }   , 
	{0x10028, 0x1003a, PV::ALetter }   , 
	{0x1003c, 0x1003d, PV::ALetter }   , 
	{0x1003f, 0x1004d, PV::ALetter }   , 
	{0x10050, 0x1005d, PV::ALetter }   , 
	{0x10080, 0x100fa, PV::ALetter }   , 
	{0x10140, 0x10174, PV::ALetter }   , 
	{0x101fd, 0x101fd, PV::Extend }   , 
	{0x10280, 0x1029c, PV::ALetter }   , 
	{0x102a0, 0x102d0, PV::ALetter }   , 
	{0x10300, 0x1031e, PV::ALetter }   , 
	{0x10330, 0x10340, PV::ALetter }   , 
	{0x10341, 0x10341, PV::ALetter }   , 
	{0x10342, 0x10349, PV::ALetter }   , 
	{0x1034a, 0x1034a, PV::ALetter }   , 
	{0x10380, 0x1039d, PV::ALetter }   , 
	{0x103a0, 0x103c3, PV::ALetter }   , 
	{0x103c8, 0x103cf, PV::ALetter }   , 
	{0x103d1, 0x103d5, PV::ALetter }   , 
	{0x10400, 0x1044f, PV::ALetter }   , 
	{0x10450, 0x1049d, PV::ALetter }   , 
	{0x104a0, 0x104a9, PV::Numeric }   , 
	{0x10800, 0x10805, PV::ALetter }   , 
	{0x10808, 0x10808, PV::ALetter }   , 
	{0x1080a, 0x10835, PV::ALetter }   , 
	{0x10837, 0x10838, PV::ALetter }   , 
	{0x1083c, 0x1083c, PV::ALetter }   , 
	{0x1083f, 0x10855, PV::ALetter }   , 
	{0x10900, 0x10915, PV::ALetter }   , 
	{0x10920, 0x10939, PV::ALetter }   , 
	{0x10980, 0x109b7, PV::ALetter }   , 
	{0x109be, 0x109bf, PV::ALetter }   , 
	{0x10a00, 0x10a00, PV::ALetter }   , 
	{0x10a01, 0x10a03, PV::Extend }   , 
	{0x10a05, 0x10a06, PV::Extend }   , 
	{0x10a0c, 0x10a0f, PV::Extend }   , 
	{0x10a10, 0x10a13, PV::ALetter }   , 
	{0x10a15, 0x10a17, PV::ALetter }   , 
	{0x10a19, 0x10a33, PV::ALetter }   , 
	{0x10a38, 0x10a3a, PV::Extend }   , 
	{0x10a3f, 0x10a3f, PV::Extend }   , 
	{0x10a60, 0x10a7c, PV::ALetter }   , 
	{0x10b00, 0x10b35, PV::ALetter }   , 
	{0x10b40, 0x10b55, PV::ALetter }   , 
	{0x10b60, 0x10b72, PV::ALetter }   , 
	{0x10c00, 0x10c48, PV::ALetter }   , 
	{0x11000, 0x11000, PV::Extend }   , 
	{0x11001, 0x11001, PV::Extend }   , 
	{0x11002, 0x11002, PV::Extend }   , 
	{0x11003, 0x11037, PV::ALetter }   , 
	{0x11038, 0x11046, PV::Extend }   , 
	{0x11066, 0x1106f, PV::Numeric }   , 
	{0x11080, 0x11081, PV::Extend }   , 
	{0x11082, 0x11082, PV::Extend }   , 
	{0x11083, 0x110af, PV::ALetter }   , 
	{0x110b0, 0x110b2, PV::Extend }   , 
	{0x110b3, 0x110b6, PV::Extend }   , 
	{0x110b7, 0x110b8, PV::Extend }   , 
	{0x110b9, 0x110ba, PV::Extend }   , 
	{0x110bd, 0x110bd, PV::Format }   , 
	{0x110d0, 0x110e8, PV::ALetter }   , 
	{0x110f0, 0x110f9, PV::Numeric }   , 
	{0x11100, 0x11102, PV::Extend }   , 
	{0x11103, 0x11126, PV::ALetter }   , 
	{0x11127, 0x1112b, PV::Extend }   , 
	{0x1112c, 0x1112c, PV::Extend }   , 
	{0x1112d, 0x11134, PV::Extend }   , 
	{0x11136, 0x1113f, PV::Numeric }   , 
	{0x11180, 0x11181, PV::Extend }   , 
	{0x11182, 0x11182, PV::Extend }   , 
	{0x11183, 0x111b2, PV::ALetter }   , 
	{0x111b3, 0x111b5, PV::Extend }   , 
	{0x111b6, 0x111be, PV::Extend }   , 
	{0x111bf, 0x111c0, PV::Extend }   , 
	{0x111c1, 0x111c4, PV::ALetter }   , 
	{0x111d0, 0x111d9, PV::Numeric }   , 
	{0x11680, 0x116aa, PV::ALetter }   , 
	{0x116ab, 0x116ab, PV::Extend }   , 
	{0x116ac, 0x116ac, PV::Extend }   , 
	{0x116ad, 0x116ad, PV::Extend }   , 
	{0x116ae, 0x116af, PV::Extend }   , 
	{0x116b0, 0x116b5, PV::Extend }   , 
	{0x116b6, 0x116b6, PV::Extend }   , 
	{0x116b7, 0x116b7, PV::Extend }   , 
	{0x116c0, 0x116c9, PV::Numeric }   , 
	{0x12000, 0x1236e, PV::ALetter }   , 
	{0x12400, 0x12462, PV::ALetter }   , 
	{0x13000, 0x1342e, PV::ALetter }   , 
	{0x16800, 0x16a38, PV::ALetter }   , 
	{0x16f00, 0x16f44, PV::ALetter }   , 
	{0x16f50, 0x16f50, PV::ALetter }   , 
	{0x16f51, 0x16f7e, PV::Extend }   , 
	{0x16f8f, 0x16f92, PV::Extend }   , 
	{0x16f93, 0x16f9f, PV::ALetter }   , 
	{0x1b000, 0x1b000, PV::Katakana }   , 
	{0x1d165, 0x1d166, PV::Extend }   , 
	{0x1d167, 0x1d169, PV::Extend }   , 
	{0x1d16d, 0x1d172, PV::Extend }   , 
	{0x1d173, 0x1d17a, PV::Format }   , 
	{0x1d17b, 0x1d182, PV::Extend }   , 
	{0x1d185, 0x1d18b, PV::Extend }   , 
	{0x1d1aa, 0x1d1ad, PV::Extend }   , 
	{0x1d242, 0x1d244, PV::Extend }   , 
	{0x1d400, 0x1d454, PV::ALetter }   , 
	{0x1d456, 0x1d49c, PV::ALetter }   , 
	{0x1d49e, 0x1d49f, PV::ALetter }   , 
	{0x1d4a2, 0x1d4a2, PV::ALetter }   , 
	{0x1d4a5, 0x1d4a6, PV::ALetter }   , 
	{0x1d4a9, 0x1d4ac, PV::ALetter }   , 
	{0x1d4ae, 0x1d4b9, PV::ALetter }   , 
	{0x1d4bb, 0x1d4bb, PV::ALetter }   , 
	{0x1d4bd, 0x1d4c3, PV::ALetter }   , 
	{0x1d4c5, 0x1d505, PV::ALetter }   , 
	{0x1d507, 0x1d50a, PV::ALetter }   , 
	{0x1d50d, 0x1d514, PV::ALetter }   , 
	{0x1d516, 0x1d51c, PV::ALetter }   , 
	{0x1d51e, 0x1d539, PV::ALetter }   , 
	{0x1d53b, 0x1d53e, PV::ALetter }   , 
	{0x1d540, 0x1d544, PV::ALetter }   , 
	{0x1d546, 0x1d546, PV::ALetter }   , 
	{0x1d54a, 0x1d550, PV::ALetter }   , 
	{0x1d552, 0x1d6a5, PV::ALetter }   , 
	{0x1d6a8, 0x1d6c0, PV::ALetter }   , 
	{0x1d6c2, 0x1d6da, PV::ALetter }   , 
	{0x1d6dc, 0x1d6fa, PV::ALetter }   , 
	{0x1d6fc, 0x1d714, PV::ALetter }   , 
	{0x1d716, 0x1d734, PV::ALetter }   , 
	{0x1d736, 0x1d74e, PV::ALetter }   , 
	{0x1d750, 0x1d76e, PV::ALetter }   , 
	{0x1d770, 0x1d788, PV::ALetter }   , 
	{0x1d78a, 0x1d7a8, PV::ALetter }   , 
	{0x1d7aa, 0x1d7c2, PV::ALetter }   , 
	{0x1d7c4, 0x1d7cb, PV::ALetter }   , 
	{0x1d7ce, 0x1d7ff, PV::Numeric }   , 
	{0x1ee00, 0x1ee03, PV::ALetter }   , 
	{0x1ee05, 0x1ee1f, PV::ALetter }   , 
	{0x1ee21, 0x1ee22, PV::ALetter }   , 
	{0x1ee24, 0x1ee24, PV::ALetter }   , 
	{0x1ee27, 0x1ee27, PV::ALetter }   , 
	{0x1ee29, 0x1ee32, PV::ALetter }   , 
	{0x1ee34, 0x1ee37, PV::ALetter }   , 
	{0x1ee39, 0x1ee39, PV::ALetter }   , 
	{0x1ee3b, 0x1ee3b, PV::ALetter }   , 
	{0x1ee42, 0x1ee42, PV::ALetter }   , 
	{0x1ee47, 0x1ee47, PV::ALetter }   , 
	{0x1ee49, 0x1ee49, PV::ALetter }   , 
	{0x1ee4b, 0x1ee4b, PV::ALetter }   , 
	{0x1ee4d, 0x1ee4f, PV::ALetter }   , 
	{0x1ee51, 0x1ee52, PV::ALetter }   , 
	{0x1ee54, 0x1ee54, PV::ALetter }   , 
	{0x1ee57, 0x1ee57, PV::ALetter }   , 
	{0x1ee59, 0x1ee59, PV::ALetter }   , 
	{0x1ee5b, 0x1ee5b, PV::ALetter }   , 
	{0x1ee5d, 0x1ee5d, PV::ALetter }   , 
	{0x1ee5f, 0x1ee5f, PV::ALetter }   , 
	{0x1ee61, 0x1ee62, PV::ALetter }   , 
	{0x1ee64, 0x1ee64, PV::ALetter }   , 
	{0x1ee67, 0x1ee6a, PV::ALetter }   , 
	{0x1ee6c, 0x1ee72, PV::ALetter }   , 
	{0x1ee74, 0x1ee77, PV::ALetter }   , 
	{0x1ee79, 0x1ee7c, PV::ALetter }   , 
	{0x1ee7e, 0x1ee7e, PV::ALetter }   , 
	{0x1ee80, 0x1ee89, PV::ALetter }   , 
	{0x1ee8b, 0x1ee9b, PV::ALetter }   , 
	{0x1eea1, 0x1eea3, PV::ALetter }   , 
	{0x1eea5, 0x1eea9, PV::ALetter }   , 
	{0x1eeab, 0x1eebb, PV::ALetter }   , 
	{0x1f1e6, 0x1f1ff, PV::Regional_Indicator }   , 
	{0xe0001, 0xe0001, PV::Format }   , 
	{0xe0020, 0xe007f, PV::Format }   , 
	{0xe0100, 0xe01ef, PV::Extend }   };

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

 }  }  }  } // namespace ::unicpp::cdb::wordbreak::binary
