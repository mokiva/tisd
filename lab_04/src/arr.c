#include <stdlib.h>
#include <stdio.h>

#include "arr.h"
#include "defs.h"
#include "expr.h"

void push_arr(array_t *array, int num)
{
    *(array -> arr++) = num;
    array -> len++;
}

int add_elem_arr(array_t *array, int *max_len)
{
    if (*max_len == 0)
    {
        printf("  Введите максимально возможный размер стека (не больше 1000): ");

        int rc = scanf("%d", max_len);

        if ((rc != 1) || (*max_len < 0) || (*max_len > 10000))
        {
            puts("\n  Размер задан некорректно");
            setbuf(stdin, NULL);
            return BAD_STACK_MAX_LEN;
        }

        int *tmp = malloc(*max_len * sizeof(int));

        if (!tmp)
            return BAD_MALLOC;

        array -> arr = tmp;
    }

    if (array -> len + 1 > *max_len)
    {
        puts("\n  Стек переполнен");
        setbuf(stdin, NULL);
        return STACK_OVERFLOW;
    }

    printf("\n  Введите число: ");
    int num;

    int rc = scanf("%d", &num);

    if (rc != 1)
    {
        puts("\n  Неверно введен элемент для добавления");
        setbuf(stdin, NULL);
        return BAD_ELEM_INP;
    }

    push_arr(array, num);

    return SUCCESS;
}

int pop_arr(array_t *stack_arr)
{
    if (stack_arr -> len == 0)
    {
        puts("\n  Стек пуст");
        return EMPTY_STACK;
    }

    stack_arr -> arr--;
    stack_arr -> len--;

    return SUCCESS;
}

void print_arr(array_t *stack_arr)
{
    if (stack_arr -> len == 0)
    {
        printf("\n  Стек пуст");
        return;
    }

    int *tmp = stack_arr -> arr;
    int len = stack_arr -> len;

    while (len > 0)
    {
        printf("%d\n", *(--tmp));
        len--;
    }
}

int top_arr(array_t array)
{
    return *(array.arr - 1);
}

int check_arr_stack(array_t stack)
{
    return (stack.len == 0) ? EMPTY : NOT_EMPTY;
}

void count_operation(array_t *num_stack, array_t *sign_stack)
{
    int num1 = top_arr(*num_stack);
    pop_arr(num_stack);

    int num2 = top_arr(*num_stack);
    pop_arr(num_stack);

    int sign_op = top_arr(*sign_stack);
    pop_arr(sign_stack);

    int result;

    if (sign_op == 1)
    {
        result = num2 + num1;
    }
    else if (sign_op == 2)
    {
        result = num2 - num1;
    }
    else if (sign_op == 3)
    {
        result = num2 * num1;
    }
    else if (sign_op == 4)
    {
        result = (int)(num2 / num1);
    }

    push_arr(num_stack, result);
}

int calculate_arr(expression_t expression)
{
    array_t num_stack = {.len = 0};
    array_t sym_stack = {.len = 0};

    int *tmp = malloc(expression.len * sizeof(int));

    if (!tmp)
        return BAD_MALLOC;

    num_stack.arr = tmp;

    tmp = malloc(expression.len * sizeof(int));

    if (!tmp)
        return BAD_MALLOC;

    sym_stack.arr = tmp;

    for (int i = 0; i < expression.len; i++)
    {
        if (check_operation(expression.sym[i]))
        {
            int sign = translate_operation(expression.sym[i]);

            if (!check_arr_stack(sym_stack))
                push_arr(&sym_stack, sign);

            else
            {
                int level_cur = check_priority(sign);
                int level_prev = check_priority(top_arr(sym_stack));

                if (level_cur > level_prev)
                    push_arr(&sym_stack, sign);

                else if (level_cur <= level_prev)
                {
                    count_operation(&num_stack, &sym_stack);
                    i--;
                }
            }
        }
        else
        {
            int num = read_num_from_arr_char(expression.sym, &i);
            i -= 1;

            push_arr(&num_stack, num);

            if (i + 1 == expression.len)
            {
                while (check_arr_stack(sym_stack))
                {
                    count_operation(&num_stack, &sym_stack);
                }
            }
        }
    }

    return top_arr(num_stack);
}

int expression_result_arr(int *res)
{
    expression_t expression;

    int rc = read_expression(&expression); // read expression in char array

    if (rc != SUCCESS)
        return rc;

    *res = calculate_arr(expression);

    return SUCCESS;
}