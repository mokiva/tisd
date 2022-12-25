#ifndef __ADT_H__
#define __ADT_H__

#include "defs.h"

typedef struct list list_t;

struct list
{
    int num;
    int ind;
    list_t *next;
};

typedef struct
{
    int *arr;
    int len;
} array_t;

typedef struct
{
    char sym[N + 1];
    int len;
} expression_t;

typedef struct
{
    list_t *arr_clear[N];
    int len;
} array_clear_t;

#endif // __ADT_H__