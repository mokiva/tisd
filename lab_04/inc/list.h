#ifndef __LIST_H__
#define __LIST_H__

#include "adt.h"

list_t* create_node(int num);

int push_node(list_t **list, int num);

int add_elem_stack_list(list_t **list, int *max_len);

void clear_address(array_clear_t *arr, int ind);

void del_address(array_clear_t *arr, list_t *list);

void add_address(array_clear_t *arr, list_t *list);

int pop_elem_stack_list(list_t **list);

void print_list(list_t *list);

void print_addresses(array_clear_t arr);

int calculate_expression(expression_t expression);

int expression_result(int *result);

#endif // __LIST_H__