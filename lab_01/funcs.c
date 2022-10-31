#include <stdio.h>
#include <ctype.h>

#include "funcs.h"
#include "defines.h"
#include "struct.h"

// функция, реализуюащя ввод строки
size_t input_str(char *buffer, size_t len)
{
    int ch;
    size_t count = 0;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (count < len)
            buffer[count] = ch;

        ++count;
    }

    return count;
}

// функция, реализующая проверку корректности длины введённого целого числа
size_t check_int_len(char *buffer, size_t len)
{
    size_t flag = TRUE;

    if (buffer[0] != '-' && buffer[0] != '+' && len > 30)
        flag = FALSE;

    return flag;
}

// функция, реализующая проверку корректности содержимого введённого целого числа
size_t check_int_content(char *buffer, size_t len)
{
    int ch;
    size_t flag = TRUE;

    for (size_t i = 0; i < len; ++i)
    {
        if (i == 0 && buffer[i] != '+' && buffer[i] != '-' && (ch = isdigit(buffer[i])) == 0)
            flag = FALSE;

        if (i > 0 && (ch = isdigit(buffer[i])) == 0)
            flag = FALSE;
    }

    if (len == 1 && (buffer[0] == '+' || buffer[0] == '-'))
        flag = FALSE;

    if ((buffer[0] == '+' || buffer[0] == '-') && buffer[1] == '0')
        flag = FALSE;

    if (buffer[0] == '0' && buffer[1] == '0')
        flag = FALSE;

    return flag;
}

// функция, реализующая проверку длины порядка
size_t check_order(char *buffer, size_t len)
{
    size_t count = 0;
    size_t flag = FALSE;
    int ch;

    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i] == 'e' || buffer[i] == 'E')
            flag = TRUE;

        if (flag && (ch = isdigit(buffer[i])))
            ++count;
    }

    return count;
}

// функция, реализующая проверку длины мантиссы
size_t check_mantissa(char *buffer, size_t len)
{
    int ch;
    size_t count = 0;
    size_t flag = FALSE;
    size_t flag_e = FALSE;

    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i] == 'e' || buffer[i] == 'E')
            flag_e = TRUE;

        if ((ch = isdigit(buffer[i])) != 0 && buffer[i] != '0')
            flag = TRUE;

        if (flag && (ch = isdigit(buffer[i])) != 0 && flag_e == FALSE)
            ++count;
    }

    if (count == 0)
        return count;

    size_t i = len - 1;

    if (flag_e)
    {
        while (i >= 0 && i <= len - 1 && buffer[i] != 'e' && buffer[i] != 'E')
            --i;

        --i;

        while (i >= 0 && i <= len - 1 && buffer[i] == '0')
        {
            --count;
            --i;
        }

        if (i >= 0 && i <= len - 1 && buffer[i] == '.')
        {
            --i;

            while (i >= 0 && i <= len - 1 && buffer[i] == '0')
            {
                --count;
                --i;
            }
        }
    }

    if (flag_e == FALSE)
    {
        while (i >= 0 && i <= len - 1 && buffer[i] == '0')
        {
            --count;
            --i;
        }

        if (i >= 0 && i <= len - 1 && buffer[i] == '.')
        {
            --i;

            while (i >= 0 && i <= len - 1 && buffer[i] == '0')
            {
                --count;
                --i;
            }
        }
    }

    return count;
}

// функция, реализующая проверку нескольких нулей в начале целой части вещественного числа
size_t check_zeros(char *buffer)
{
    size_t flag = TRUE;

    if ((buffer[0] == '-' || buffer[0] == '+') && (buffer[1] == '0' && buffer[2] != '.'))
        flag = FALSE;

    if (buffer[0] == '0' && (buffer[1] != '.' && buffer[1] != '\0'))
        flag = FALSE;

    return flag;
}

// функция, парсящей знак числа в поле структуры
void parse_sign(char *buffer, big_double *value)
{
    if (buffer[0] == '-')
       value -> sign = '-';
    else
        value -> sign = '+';
}

// функция, заполняющая поле мантиссы в стуктуре для целого числа
void parse_mantissa_from_int(char *buffer, big_double *value, size_t mant_len)
{
    if (buffer[0] == '-' || buffer[0] == '+')
    {
        for (size_t i = 0; i < mant_len; ++i)
            value -> mantissa[i] = buffer[i + 1] - '0';
    }
    else
    {
        for (size_t i = 0; i < mant_len; ++i)
            value -> mantissa[i] = buffer[i] - '0';
    }

    for (size_t i = mant_len; i < MAX_MANT_LEN; ++i)
        value -> mantissa[i] = 0;
}

// функция, печатающая массив
void print_array(int *arr, size_t len)
{
    size_t count = 0;

    for (int i = len - 1; i >= 0; --i)
    {
        if (arr[i] != 0)
            break;

        ++count;
    }

    for (size_t i = 0; i < len - count; ++i)
    {
        if (arr[i] == 0 && i == 0)
            continue;

        printf("%d", arr[i]);
    }
}

// функция, заполняющая поле порядка целого числа в структуре
void parse_order_from_int(big_double *value, size_t mant_len)
{
    value -> order = mant_len - MAX_MANT_LEN;
}

// функция, заполняющая поле мантиссы вещественного числа в структуре
void parse_mantissa_from_dbl(char *buffer, big_double *value, size_t mant_len)
{
    int ch;
    size_t i = 0;
    size_t k = 0;
    size_t flag = FALSE;

    while (i < mant_len)
    {
        if ((ch = isdigit(buffer[k])) != 0 && buffer[k] != '0')
            flag = TRUE;

        if (flag && buffer[k] != '.')
        {
            value -> mantissa[i] = buffer[k] - '0';
            ++i;
        }

        ++k;
    }

    for (size_t p = i; p < MAX_MANT_LEN; ++p)
        value -> mantissa[p] = 0;
}

// функция, возвращающая порядок мантиссы при e
int parse_e_order(char *buffer, size_t len)
{
    int order;
    size_t order_index;
    size_t index;
    size_t flag = FALSE;
    char order_string[MAX_ORDER_LEN + 1] = { '\0' };

    for (size_t i = 0; i < len; ++i)
    {
        if (buffer[i] == 'e' || buffer[i] == 'E')
        {
            flag = TRUE;
            index = i;
        }
    }

    order_index = 0;

    if (flag)
    {
        for (size_t i = index + 1; buffer[i] != '\0'; ++i)
        {
            order_string[order_index] = buffer[i];
            ++order_index;
        }

        sscanf(order_string, "%d", &order);
    }
    else
        order = 0;

    return order;
}

// функция, возвращающая порядок действительной части числа
int parse_root_order(char *buffer, size_t mant_len)
{
    int order = 0;
    size_t count = 0;

    for (size_t i = 0; buffer[i] != 'e' && buffer[i] != 'E' && buffer[i] != '\0'; ++i)
    {
        if (buffer[i] == '.')
            break;

        if (buffer[i] != '+' && buffer[i] != '-')
            ++count;
    }

    order = count - MAX_MANT_LEN;

    if ((buffer[0] == '+' || buffer[0] == '-') && buffer[1] == '0' && buffer[2] == '.')
        order = -MAX_MANT_LEN;

    if (buffer[0] == '0' && buffer[1] == '.')
        order = -MAX_MANT_LEN;

    if (order == -MAX_MANT_LEN)
    {
        size_t dot_flag = 0;
        for (size_t i = 0; buffer[i] != 'e' && buffer[i] != 'E' && buffer[i] != '\0'; ++i)
        {
            if (buffer[i] == '.')
            {
                dot_flag = TRUE;
                continue;
            }

            if (dot_flag && buffer[i] == '0')
                --order;

            if (dot_flag && buffer[i] != '0')
                dot_flag = FALSE;
        }
    }

    return order;
}

// функция, реализующая умножение чисел, записанных в двух массивах и записывающая результат в третий
void give_multy(int *arr1, int *arr2, int *res, size_t len1, size_t len2, size_t rlen)
{
    for (int i = len1 - 1; i >= 0; --i)
    {
        for (int j = len2 - 1; j >= 0; --j)
        {
            res[i + j + 1] += arr1[i] * arr2[j];
        }
    }

    for (size_t i = rlen - 1; i > 0; --i)
    {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
}

// функция, реализующая округление числа
size_t res_round(int *res, size_t rlen)
{
    size_t flag = TRUE;

    for (size_t i = MAX_MANT_LEN + 1; i > 0; --i)
    {
        if (res[i] >= 5)
        {
            if (i == 1 && res[0] == 9)
                flag = FALSE;

            res[i - 1] += 1;
        }
        else
            break;
    }

    return flag;
}

















