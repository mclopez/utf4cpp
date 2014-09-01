

 /*
->S0 Other->S1 CR->S2 LF->S3 Control->S3 Extend->S1 Regional_Indicator->S4 SpacingMark->S1 L->S5 V->S6 T->S7 LV->S6 LVT->S7 
  S1 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S1 Regional_Indicator->S8 SpacingMark->S1 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S2 Other->S8 CR->S8 LF->S3 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S3 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S4 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S1 Regional_Indicator->S4 SpacingMark->S1 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S5 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S1 Regional_Indicator->S8 SpacingMark->S1 L->S5 V->S6 T->S8 LV->S6 LVT->S7 +
  S6 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S1 Regional_Indicator->S8 SpacingMark->S1 L->S8 V->S6 T->S7 LV->S8 LVT->S8 +
  S7 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S1 Regional_Indicator->S8 SpacingMark->S1 L->S8 V->S8 T->S7 LV->S8 LVT->S8 +
  S8 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 

*/

static const size_t grapheme_dfa_length = 13;
static const int grapheme_dfa[][13] { 
{1, 2, 3, 3, 1, 4, 1, 5, 6, 7, 6, 7, 0},
{8, 8, 8, 8, 1, 8, 1, 8, 8, 8, 8, 8, 1},
{8, 8, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
{8, 8, 8, 8, 1, 4, 1, 8, 8, 8, 8, 8, 1},
{8, 8, 8, 8, 1, 8, 1, 5, 6, 8, 6, 7, 1},
{8, 8, 8, 8, 1, 8, 1, 8, 6, 7, 8, 8, 1},
{8, 8, 8, 8, 1, 8, 1, 8, 8, 7, 8, 8, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0},
};
static const size_t grapheme_dfa_pit_state = 8;


 /*
->S0 Other->S1 CR->S1 LF->S2 Control->S1 Extend->S3 Regional_Indicator->S4 SpacingMark->S3 L->S5 V->S6 T->S7 LV->S5 LVT->S5 
  S1 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S2 Other->S8 CR->S1 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S3 Other->S1 CR->S8 LF->S8 Control->S8 Extend->S3 Regional_Indicator->S4 SpacingMark->S3 L->S5 V->S6 T->S7 LV->S5 LVT->S5 +
  S4 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S4 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 +
  S5 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S5 V->S8 T->S8 LV->S8 LVT->S8 +
  S6 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S5 V->S6 T->S8 LV->S5 LVT->S8 +
  S7 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S6 T->S7 LV->S5 LVT->S5 +
  S8 Other->S8 CR->S8 LF->S8 Control->S8 Extend->S8 Regional_Indicator->S8 SpacingMark->S8 L->S8 V->S8 T->S8 LV->S8 LVT->S8 

*/

static const size_t grapheme_backwards_dfa_length = 13;
static const int grapheme_backwards_dfa[][13] { 
{1, 1, 2, 1, 3, 4, 3, 5, 6, 7, 5, 5, 0},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
{8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
{1, 8, 8, 8, 3, 4, 3, 5, 6, 7, 5, 5, 1},
{8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 1},
{8, 8, 8, 8, 8, 8, 8, 5, 8, 8, 8, 8, 1},
{8, 8, 8, 8, 8, 8, 8, 5, 6, 8, 5, 8, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 6, 7, 5, 5, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0},
};
static const size_t grapheme_backwards_dfa_pit_state = 8;
