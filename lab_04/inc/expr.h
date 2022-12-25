#ifndef __EXPR_H__
#define __EXPR_H__

#include "adt.h"

int read_expression(expression_t *expression);

int check_operation(char ch);

int translate_operation(char ch);

#endif // __EXPR_H__