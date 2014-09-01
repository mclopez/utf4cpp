

 /*
->S0 Other->S1 CR->S2 LF->S3 Extend->S1 Sep->S3 Format->S1 Sp->S1 Lower->S1 Upper->S4 OLetter->S1 Numeric->S1 ATerm->S5 STerm->S6 Close->S1 SContinue->S1 +
  S1 Other->S1 CR->S3 LF->S3 Extend->S1 Sep->S3 Format->S1 Sp->S1 Lower->S1 Upper->S4 OLetter->S1 Numeric->S1 ATerm->S5 STerm->S6 Close->S1 SContinue->S1 +
  S2 Other->S7 CR->S7 LF->S3 Extend->S7 Sep->S7 Format->S7 Sp->S7 Lower->S7 Upper->S7 OLetter->S7 Numeric->S7 ATerm->S7 STerm->S7 Close->S7 SContinue->S7 +
  S3 Other->S7 CR->S7 LF->S7 Extend->S7 Sep->S7 Format->S7 Sp->S7 Lower->S7 Upper->S7 OLetter->S7 Numeric->S7 ATerm->S7 STerm->S7 Close->S7 SContinue->S7 +
  S4 Other->S1 CR->S3 LF->S3 Extend->S4 Sep->S3 Format->S4 Sp->S1 Lower->S1 Upper->S4 OLetter->S1 Numeric->S1 ATerm->S8 STerm->S6 Close->S1 SContinue->S1 +
  S5 Other->S9 CR->S3 LF->S3 Extend->S5 Sep->S3 Format->S5 Sp->S10 Lower->S1 Upper->S7 OLetter->S7 Numeric->S1 ATerm->S1 STerm->S1 Close->S11 SContinue->S1 +
  S6 Other->S7 CR->S3 LF->S3 Extend->S6 Sep->S3 Format->S6 Sp->S12 Lower->S7 Upper->S7 OLetter->S7 Numeric->S7 ATerm->S1 STerm->S1 Close->S6 SContinue->S1 +
  S7 Other->S7 CR->S7 LF->S7 Extend->S7 Sep->S7 Format->S7 Sp->S7 Lower->S7 Upper->S7 OLetter->S7 Numeric->S7 ATerm->S7 STerm->S7 Close->S7 SContinue->S7 
  S8 Other->S9 CR->S3 LF->S3 Extend->S8 Sep->S3 Format->S8 Sp->S10 Lower->S1 Upper->S4 OLetter->S7 Numeric->S1 ATerm->S1 STerm->S1 Close->S11 SContinue->S1 +
  S9 Other->S9 CR->S7 LF->S7 Extend->S9 Sep->S7 Format->S9 Sp->S9 Lower->S1 Upper->S7 OLetter->S7 Numeric->S9 ATerm->S7 STerm->S7 Close->S9 SContinue->S9 
  S10 Other->S9 CR->S3 LF->S3 Extend->S10 Sep->S3 Format->S10 Sp->S10 Lower->S1 Upper->S7 OLetter->S7 Numeric->S9 ATerm->S1 STerm->S1 Close->S9 SContinue->S1 +
  S11 Other->S9 CR->S3 LF->S3 Extend->S11 Sep->S3 Format->S11 Sp->S10 Lower->S1 Upper->S7 OLetter->S7 Numeric->S9 ATerm->S1 STerm->S1 Close->S11 SContinue->S1 +
  S12 Other->S7 CR->S3 LF->S3 Extend->S12 Sep->S3 Format->S12 Sp->S12 Lower->S7 Upper->S7 OLetter->S7 Numeric->S7 ATerm->S1 STerm->S1 Close->S7 SContinue->S1 +

*/

static const size_t sentence_dfa_length = 16;
static const int sentence_dfa[][16] { 
{1, 2, 3, 1, 3, 1, 1, 1, 4, 1, 1, 5, 6, 1, 1, 1},
{1, 3, 3, 1, 3, 1, 1, 1, 4, 1, 1, 5, 6, 1, 1, 1},
{7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1},
{1, 3, 3, 4, 3, 4, 1, 1, 4, 1, 1, 8, 6, 1, 1, 1},
{9, 3, 3, 5, 3, 5, 10, 1, 7, 7, 1, 1, 1, 11, 1, 1},
{7, 3, 3, 6, 3, 6, 12, 7, 7, 7, 7, 1, 1, 6, 1, 1},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0},
{9, 3, 3, 8, 3, 8, 10, 1, 4, 7, 1, 1, 1, 11, 1, 1},
{9, 7, 7, 9, 7, 9, 9, 1, 7, 7, 9, 7, 7, 9, 9, 0},
{9, 3, 3, 10, 3, 10, 10, 1, 7, 7, 9, 1, 1, 9, 1, 1},
{9, 3, 3, 11, 3, 11, 10, 1, 7, 7, 9, 1, 1, 11, 1, 1},
{7, 3, 3, 12, 3, 12, 12, 7, 7, 7, 7, 1, 1, 7, 1, 1},
};
static const size_t sentence_dfa_pit_state = 7;


 /*
->S0 Other->S1 CR->S2 LF->S3 Extend->S2 Sep->S2 Format->S2 Sp->S2 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S2 STerm->S2 Close->S7 SContinue->S2 +
  S1 Other->S1 CR->S8 LF->S8 Extend->S1 Sep->S8 Format->S1 Sp->S1 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S9 STerm->S9 Close->S1 SContinue->S2 +
  S2 Other->S1 CR->S8 LF->S8 Extend->S2 Sep->S8 Format->S2 Sp->S2 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S2 STerm->S2 Close->S7 SContinue->S2 +
  S3 Other->S1 CR->S14 LF->S8 Extend->S2 Sep->S8 Format->S2 Sp->S2 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S2 STerm->S2 Close->S7 SContinue->S2 +
  S4 Other->S4 CR->S8 LF->S8 Extend->S4 Sep->S8 Format->S4 Sp->S4 Lower->S4 Upper->S5 OLetter->S1 Numeric->S4 ATerm->S2 STerm->S9 Close->S4 SContinue->S10 +
  S5 Other->S1 CR->S8 LF->S8 Extend->S5 Sep->S8 Format->S5 Sp->S1 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S11 STerm->S9 Close->S1 SContinue->S2 +
  S6 Other->S1 CR->S8 LF->S8 Extend->S6 Sep->S8 Format->S6 Sp->S1 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S2 STerm->S9 Close->S1 SContinue->S2 +
  S7 Other->S1 CR->S8 LF->S8 Extend->S7 Sep->S8 Format->S7 Sp->S1 Lower->S4 Upper->S5 OLetter->S1 Numeric->S6 ATerm->S2 STerm->S2 Close->S7 SContinue->S2 +
  S8 Other->S8 CR->S8 LF->S8 Extend->S8 Sep->S8 Format->S8 Sp->S8 Lower->S8 Upper->S8 OLetter->S8 Numeric->S8 ATerm->S8 STerm->S8 Close->S8 SContinue->S8 
  S9 Other->S8 CR->S8 LF->S8 Extend->S9 Sep->S8 Format->S9 Sp->S9 Lower->S8 Upper->S8 OLetter->S8 Numeric->S8 ATerm->S1 STerm->S1 Close->S12 SContinue->S8 
  S10 Other->S4 CR->S8 LF->S8 Extend->S10 Sep->S8 Format->S10 Sp->S10 Lower->S4 Upper->S5 OLetter->S1 Numeric->S4 ATerm->S2 STerm->S2 Close->S13 SContinue->S10 +
  S11 Other->S8 CR->S8 LF->S8 Extend->S11 Sep->S8 Format->S11 Sp->S9 Lower->S8 Upper->S5 OLetter->S8 Numeric->S8 ATerm->S1 STerm->S1 Close->S12 SContinue->S8 
  S12 Other->S8 CR->S8 LF->S8 Extend->S12 Sep->S8 Format->S12 Sp->S8 Lower->S8 Upper->S8 OLetter->S8 Numeric->S8 ATerm->S1 STerm->S1 Close->S12 SContinue->S8 
  S13 Other->S4 CR->S8 LF->S8 Extend->S13 Sep->S8 Format->S13 Sp->S4 Lower->S4 Upper->S5 OLetter->S1 Numeric->S4 ATerm->S2 STerm->S2 Close->S13 SContinue->S10 +
  S14 Other->S8 CR->S8 LF->S8 Extend->S8 Sep->S8 Format->S8 Sp->S8 Lower->S8 Upper->S8 OLetter->S8 Numeric->S8 ATerm->S8 STerm->S8 Close->S8 SContinue->S8 +

*/

static const size_t sentence_backwards_dfa_length = 16;
static const int sentence_backwards_dfa[][16] { 
{1, 2, 3, 2, 2, 2, 2, 4, 5, 1, 6, 2, 2, 7, 2, 1},
{1, 8, 8, 1, 8, 1, 1, 4, 5, 1, 6, 9, 9, 1, 2, 1},
{1, 8, 8, 2, 8, 2, 2, 4, 5, 1, 6, 2, 2, 7, 2, 1},
{1, 14, 8, 2, 8, 2, 2, 4, 5, 1, 6, 2, 2, 7, 2, 1},
{4, 8, 8, 4, 8, 4, 4, 4, 5, 1, 4, 2, 9, 4, 10, 1},
{1, 8, 8, 5, 8, 5, 1, 4, 5, 1, 6, 11, 9, 1, 2, 1},
{1, 8, 8, 6, 8, 6, 1, 4, 5, 1, 6, 2, 9, 1, 2, 1},
{1, 8, 8, 7, 8, 7, 1, 4, 5, 1, 6, 2, 2, 7, 2, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0},
{8, 8, 8, 9, 8, 9, 9, 8, 8, 8, 8, 1, 1, 12, 8, 0},
{4, 8, 8, 10, 8, 10, 10, 4, 5, 1, 4, 2, 2, 13, 10, 1},
{8, 8, 8, 11, 8, 11, 9, 8, 5, 8, 8, 1, 1, 12, 8, 0},
{8, 8, 8, 12, 8, 12, 8, 8, 8, 8, 8, 1, 1, 12, 8, 0},
{4, 8, 8, 13, 8, 13, 4, 4, 5, 1, 4, 2, 2, 13, 10, 1},
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
};
static const size_t sentence_backwards_dfa_pit_state = 8;
