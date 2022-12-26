#ifndef __EXPR_H__
#define __EXPR_H__

#include "adt.h"

int read_expression(expression_t *expression);

int check_operation(char ch);

int translate_operation(char ch);

int check_priority(int ch);

int read_num_from_arr_char(char *ch, int *ind);

#endif // __EXPR_H__