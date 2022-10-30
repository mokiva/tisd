#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <stdio.h>

#include "defines.h"

struct big_double
{
    char sign;
    int order;
    int mantissa[MAX_MANT_LEN];
    size_t n_sign_value;
};

typedef struct big_double big_double;

#endif  // __STRUCT_H__
