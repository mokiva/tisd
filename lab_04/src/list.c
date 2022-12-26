#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "list.h"
#include "expr.h"

list_t* create_node(int num)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node)
        return NULL;

    node -> num = num;
    node -> ind = 0;
    node -> next = NULL;

    return node;
}

int push_node(list_t **list, int num)
{
    list_t *node = create_node(num);

    if (!node)
        return BAD_MALLOC;

    node -> ind = (*list) -> ind + 1;
    node -> next = *list;

    *list = node;

    return SUCCESS;
}

int pop_list(list_t **list)
{
    if (!*list)
    {
        puts("\n  Стек пуст");
        return EMPTY_STACK;
    }

    list_t *tmp = (*list)->next;

    free(*list);

    *list = tmp;

    return SUCCESS;
}

int add_elem_stack_list(list_t **list, int *max_len)
{
    if (*max_len == 0)
    {
        puts("");
        printf("  Введите максимально возможный размер стека (не больше 1000): ");

        int rc = scanf("%d", max_len);

        if ((rc != 1) || (*max_len <= 0) || (*max_len > 1000))
        {
            puts("\n  Размер задан некорректно");
            setbuf(stdin, NULL);
            return BAD_STACK_MAX_LEN;
        }
    }

    if (*list)
    {
        if ((*list) -> ind + 2 > *max_len)
        {
            puts("\n  Стек переполнен");
            setbuf(stdin, NULL);
            return STACK_OVERFLOW;
        }
    }

    int num;

    printf("\n  Введите число: ");

    int rc = scanf("%d", &num);

    if (rc != 1)
    {
        puts("\n  Неверно введен элемент для добавления");
        setbuf(stdin, NULL);
        return BAD_ELEM_INP;
    }

    if (!(*list))
        *list = create_node(num);
    else
    {
        rc = push_node(list, num);

        if (rc != SUCCESS)
            return rc;
    }

    return SUCCESS;
}

void clear_address(array_clear_t *arr, int ind)
{
    for (int i = ind; i < arr -> len - 1; i++)
    {
        list_t *tmp = arr -> arr_clear[i];
        arr -> arr_clear[i] = arr -> arr_clear[i + 1];
        arr -> arr_clear[i + 1] = tmp;
    }
}

void del_address(array_clear_t *arr, list_t *list)
{
    if (!list)
        return;

    list_t *tmp = list;
    int len = tmp -> ind;

    for (int i = 0; i < arr -> len; i++)
    {
        tmp = list;

        for (int j = len; j >= 0; j--)
        {
            if (arr -> arr_clear[i] == tmp)
            {
                clear_address(arr, i);
                arr -> len -= 1;
                i--;
            }

            tmp = tmp -> next;
        }
    }
}

void add_address(array_clear_t *arr, list_t *list)
{
    if (!list)
        return;

    int ind = arr -> len;
    arr -> arr_clear[ind] = list;
    arr -> len += 1;
}

int pop_elem_stack_list(list_t **list)
{
    if (!(*list))
    {
        puts("\n  Стек пуст");
        return EMPTY_STACK;
    }

    list_t *tmp = (*list) -> next;
    free(*list);
    *list = tmp;

    return SUCCESS;
}

void print_list(list_t *list)
{
    if (!list)
    {
        puts("\n  Стек пуст");
        return;
    }

    puts("\n  Стек в виде списка");

    int len = list -> ind;

    while (len >= 0)
    {
        printf("  %d --- %p\n", list -> num, (void*) list);
        list = list -> next;

        len--;
    }
}

void print_addresses(array_clear_t arr)
{
    if (arr.len == 0)
    {
        puts("\n  Массив освободившихся адресов пуст");
        return;
    }

    int len = arr.len;

    puts("\n  Массив освободившихся адресов");

    for (int i = 0; i < len; i++)
        printf("  %p\n", (void*) arr.arr_clear[i]);
}

void count_operation_list(list_t **num_stack, list_t **sign_stack)
{
    int num1 = top_list(*num_stack);
    pop_list(num_stack);

    int num2 = top_list(*num_stack);
    pop_list(num_stack);

    int sign_op = top_list(*sign_stack);
    pop_list(sign_stack);

    int result;

    if (sign_op == 1)
        result = num2 + num1;

    if (sign_op == 2)
        result = num2 - num1;

    if (sign_op == 3)
        result = num2 * num1;

    if (sign_op == 4)
        result = (int) (num2 / num1);

    if (!check_stack(*num_stack))
        *num_stack = create_node(result);

    else
        push_node(num_stack, result);
}

int check_stack(list_t *list)
{
    return (!list) ? EMPTY : NOT_EMPTY;
}

int top_list(list_t *list)
{
    return (list -> num);
}

int calculate_expression(expression_t expression)
{
    list_t *num_stack = NULL;
    list_t *sym_stack = NULL;

    for (int i = 0; i < expression.len; i++)
    {
        if (check_operation(expression.sym[i]))
        {
            int sign = translate_operation(expression.sym[i]);

            if (!check_stack(sym_stack))
                sym_stack = create_node(sign);

            else
            {
                int level_cur = check_priority(sign);
                int level_prev = check_priority(top_list(sym_stack));

                if (level_cur > level_prev)
                    push_node(&sym_stack, sign);

                if (level_cur <= level_prev)
                {
                    count_operation_list(&num_stack, &sym_stack);
                    i--;
                }
            }
        }
        else
        {
            int num = read_num_from_arr_char(expression.sym, &i);
            i -= 1;

            if (!check_stack(num_stack))
                num_stack = create_node(num);

            else
                push_node(&num_stack, num);

            if (i + 1 == expression.len)
            {
                while (check_stack(sym_stack))
                    count_operation_list(&num_stack, &sym_stack);
            }
        }
    }

    return top_list(num_stack);
}

int expression_result_list(int *result)
{
    expression_t expression;

    int rc = read_expression(&expression);

    if (rc != SUCCESS)
        return rc;

    *result = calculate_expression(expression);

    return SUCCESS;
}

void free_list(list_t **list)
{
    int len = (*list)->ind;

    while (len >= 0)
    {
        pop_list(list);

        len--;
    }
}