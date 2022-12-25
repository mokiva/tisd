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
        puts("\n  Стек пуст");

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

int check_stack(list_t *list)
{
    return (!list) ? EMPTY : NOT_EMPTY;
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

                if (level_cur > level_prev) // if priority is higher
                {
                    LOG_DEBUG("PUSH IT: c = %d, p = %d", level_cur, level_prev);
                    push_node(&sym_stack, sign); // push in stack
                }
                else if (level_cur <= level_prev)// if priority is equal or lower
                {
                    count_operation_list(&num_stack, &sym_stack); // take 2 nums from stack and prev sign -> result in num_stack
                    i--;
                }
            }
        } // end sign parse
        else
        {
            //printf("\n###in num parse###\n");
            int num = read_num_from_arr_char(exp.sym, &i); // get num from stack
            i -= 1;

            //printf("\nnum = %d\n", num);

            if (!check_clear_stack_list(num_stack))
            {
                num_stack = create_node(num);
            }
            else
            {
                push_node(&num_stack, num);
            }

            if (i + 1 == exp.len)
            {
                while (check_clear_stack_list(sym_stack)) // if operations are left after loop
                {
                    count_operation_list(&num_stack, &sym_stack);
                }
            }
        } // end num parse

        // puts("Stack nums now");
        // print_list(num_stack);


        // puts("Stack sign now");
        // print_list(sym_stack);

        // puts("");
    }

    return top_list(num_stack);
}

int expression_result(int *result)
{
    expression_t expression;

    int rc = read_expression(&expression);

    if (rc != SUCCESS)
        return rc;

    *result = calculate_expression(expression);

    return SUCCESS;
}