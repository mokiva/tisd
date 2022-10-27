#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

#include "defines.h"
#include "funcs.h"
#include "struct.h"

int main(void)
{
    // вывод описания программы при её вызове
    printf("\n----> Программа моделирует операцию умножения целого числа\n");
    printf("----> длиной до 30 десятичных цифр на действительное число\n");
    printf("----> с сумарной длиной мантиссы до 30 значащих цифр,\n");
    printf("----> а также длиной порядка до 5 цифр (см. подробности в отчёте)\n\n");

    // ввод и проверка валидности первого числа
    printf("----> Введите целое число: ");

    char integer_digit[INP_INT_LEN + 1] = { '\0' };

    size_t rc_inp = input_str(integer_digit, INP_INT_LEN);
    size_t rc_ilen = check_int_len(integer_digit, rc_inp);

    if (rc_inp == 0)
    {
        printf("\n----> Ошибка! Пустой ввод\n\n");
        return INP_INT_ZERO;
    }

    if (rc_inp > INP_INT_LEN || rc_ilen == FALSE)
    {
        printf("\n----> Ошибка! Длинный ввод\n\n");
        return INP_INT_OVERSIZE;
    }

    size_t rc_icont = check_int_content(integer_digit, rc_inp);
    if (rc_icont == FALSE)
    {
        printf("\n----> Ошибка! Некорректный ввод\n\n");
        return INP_INT_INCOR;
    }

    // ввод и проверка валидности второго числа
    printf("----> Введите вещественное число: ");

    char double_digit[INP_DBL_LEN + 1] = { '\0' };

    rc_inp = input_str(double_digit, INP_DBL_LEN);

    char *dyn_ptr = double_digit;
    double temp_dbl = strtod(double_digit, &dyn_ptr);

    if (rc_inp == 0)
    {
        printf("\n----> Ошибка! Пустой ввод\n\n");
        return INP_DBL_ZERO;
    }

    if (rc_inp > INP_DBL_LEN)
    {
        printf("\n----> Ошибка! Длинный ввод\n\n");
        return INP_DBL_OVERSIZE;
    }

    // проверка корректности записи вещественного числа с помощью работы функции strtod из stdlib.h
    if (((temp_dbl < 0 + 0.00001 && temp_dbl > 0 - 0.00001) && dyn_ptr == double_digit) || *dyn_ptr != '\0' || isspace(double_digit[0]))
    {
        printf("\n----> Ошибка! Некорректный ввод\n\n");
        return INP_DBL_INCOR;
    }

    size_t rc_olen = check_order(double_digit, rc_inp);

    if (rc_olen > 5)
    {
        printf("\n----> Ошибка! Слишком длинный по модулю порядок\n\n");
        return INP_DBL_ORDER_OVERSIZE;
    }

    size_t rc_mlen = check_mantissa(double_digit, rc_inp);
    printf("%ld", rc_mlen);
    if (rc_mlen > 30)
    {
        printf("\n----> Ошибка! Слишком длинная мантисса\n\n");
        return INP_DBL_MANTISSA;
    }

    size_t rc_zero = check_zeros(double_digit);
    if (rc_zero == FALSE)
    {
        printf("\n----> Ошибка! Некорректный ввод\n\n");
        return INP_DBL_FZERO;
    }

    // TODO реализация
    big_double first_digit;
    big_double second_digit;

    parse_sign(integer_digit, &first_digit);
    parse_sign(double_digit, &second_digit);

    printf("%c\n", first_digit.sign);
    printf("%c\n", second_digit.sign);

    return OK;
}
