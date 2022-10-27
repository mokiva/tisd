#ifndef __STRUCT_H__
#define __STRUCT_H__

#include "defines.h"

struct big_double
{
    char sign;
    int order[MAX_ORDER_LEN];
    int mantissa[MAX_MANT_LEN];
};

typedef struct big_double big_double;

#endif  // __STRUCT_H__
