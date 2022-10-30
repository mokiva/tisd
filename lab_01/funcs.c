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

// функция, заполняющая поле мантиссы в стуктуре
void parse_mantissa_from_int(char *buffer, big_double *value, size_t mant_len)
{
    if (buffer[0] == '-')
    {
        for (size_t i = 0; i < mant_len; ++i)
        {
            value -> mantissa[i] = buffer[i + 1] - '0';
        }
    }
    else
    {
        for (size_t i = 0; i < mant_len; ++i)
        {
            value -> mantissa[i] = buffer[i] - '0';
        }
    }

    for (size_t i = mant_len; i < MAX_MANT_LEN; ++i)
    {
        value -> mantissa[i] = 0;
    }
}

// функция, печатающая массив
void print_array(int arr[], int len)
{
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// функция, заполняющая поле порядка в структуре
void parse_order_from_int(big_double *value, size_t mant_len)
{
    value -> order = mant_len - 30;
}













