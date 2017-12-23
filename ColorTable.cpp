/*
 * ColorTable.cpp
 *
 *  Created on: 23 ���. 2016 �.
 *      Author: Kreyl
 */

#include "ColorTable.h"

#ifndef countof
#define countof(A)  (sizeof(A)/sizeof(A[0]))
#endif

#if COLOR_TABLE_SHORT
static const Color_t __ColorTable[] = {
        {255,0,0},
        {255,64,0},
        {255,128,0},
        {255,192,0},
        {255,255,0},
        {192,255,0},
        {128,255,0},
        {64,255,0},
        {0,255,0},
        {0,255,64},
        {0,255,128},
        {0,255,192},
        {0,255,255},
        {0,192,255},
        {0,128,255},
        {0,64,255},
        {0,0,255},
        {64,0,255},
        {128,0,255},
        {192,0,255},
        {255,0,255},
        {255,0,192},
        {255,0,128},
        {255,0,64},
        {64,64,64},
        {128,128,128},
        {255,255,255},
//        {0,0,0},
};
#else
static const Color_t __ColorTable[] = {
        {255,0,0},
        {255,24,0},
        {255,48,0},
        {255,71,0},
        {255,94,0},
        {255,117,0},
        {255,138,0},
        {255,158,0},
        {255,177,0},
        {255,195,0},
        {255,210,0},
        {255,224,0},
        {255,235,0},
        {255,244,0},
        {255,250,0},
        {255,254,0},
        {254,255,0},
        {250,255,0},
        {241,255,0},
        {228,255,0},
        {212,255,0},
        {193,255,0},
        {172,255,0},
        {150,255,0},
        {127,255,0},
        {104,255,0},
        {82,255,0},
        {61,255,0},
        {42,255,0},
        {26,255,0},
        {13,255,0},
        {4,255,0},
        {0,255,0},
        {0,255,1},
        {0,255,7},
        {0,255,17},
        {0,255,31},
        {0,255,48},
        {0,255,68},
        {0,255,89},
        {0,255,112},
        {0,255,135},
        {0,255,157},
        {0,255,179},
        {0,255,199},
        {0,255,217},
        {0,255,233},
        {0,255,244},
        {0,255,252},
        {0,255,255},
        {0,252,255},
        {0,244,255},
        {0,233,255},
        {0,217,255},
        {0,199,255},
        {0,179,255},
        {0,157,255},
        {0,135,255},
        {0,112,255},
        {0,89,255},
        {0,68,255},
        {0,48,255},
        {0,31,255},
        {0,17,255},
        {0,7,255},
        {0,1,255},
        {0,0,255},
        {4,0,255},
        {13,0,255},
        {26,0,255},
        {42,0,255},
        {61,0,255},
        {82,0,255},
        {104,0,255},
        {127,0,255},
        {150,0,255},
        {172,0,255},
        {193,0,255},
        {212,0,255},
        {228,0,255},
        {241,0,255},
        {250,0,255},
        {254,0,255},
        {255,0,254},
        {255,0,251},
        {255,0,245},
        {255,0,237},
        {255,0,227},
        {255,0,215},
        {255,0,201},
        {255,0,186},
        {255,0,169},
        {255,0,151},
        {255,0,131},
        {255,0,111},
        {255,0,90},
        {255,0,68},
        {255,0,45},
        {255,0,22},
        {255,0,0}
};
#endif

#define COLOR_TABLE_SZ  countof(__ColorTable)

ColorTable_t ColorTable {__ColorTable, COLOR_TABLE_SZ};
