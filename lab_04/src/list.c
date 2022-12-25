#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "list.h"

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

int expression_result(int *result)
{
    expression_t expression;

    int rc = read_expression(&exp);

    if (rc != NO_MISTAKES)
    {
        return rc;
    }

    *res = calculate_list(exp);

    return OK_COUNT
}