#ifndef __ARR_H__
#define __ARR_H__

#include "adt.h"

int add_elem_arr(array_t *array, int *max_len);

void push_arr(array_t *array, int num);

int pop_arr(array_t *stack_arr);

void print_arr(array_t *stack_arr);

int expression_result_arr(int *res);

int calculate_arr(expression_t expression);

int check_arr_stack(array_t stack);

void count_operation(array_t *num_stack, array_t *sign_stack);

int top_arr(array_t array);

#endif // __ARR_H__