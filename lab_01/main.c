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
    printf("----> с суммарной длиной значащих цифр мантиссы до 30 значащих цифр,\n");
    printf("----> а также длиной порядка до 5 цифр (см. подробности в отчёте)\n\n");

    // ввод и проверка валидности первого числа
    printf("                           ------------------------------- (31 знак)\n");
    printf("----> Введите целое число: ");

    char integer_digit[INP_INT_LEN + 1] = { '\0' };

    size_t rc_inp_i = input_str(integer_digit, INP_INT_LEN);
    size_t rc_ilen = check_int_len(integer_digit, rc_inp_i);

    if (rc_inp_i == 0)
    {
        printf("\n----> Ошибка! Пустой ввод\n\n");
        return INP_INT_ZERO;
    }

    if (rc_inp_i > INP_INT_LEN)
    {
        printf("\n----> Ошибка! Длинный ввод\n\n");
        return INP_INT_OVERSIZE;
    }

    if (rc_ilen == FALSE)
    {
        printf("\n----> Ошибка! Слишком много десятичных цифр\n\n");
        return INP_INT_VAL_OVERSIZE;
    }

    size_t rc_icont = check_int_content(integer_digit, rc_inp_i);
    if (rc_icont == FALSE)
    {
        printf("\n----> Ошибка! Некорректный ввод\n\n");
        return INP_INT_INCOR;
    }

    // ввод и проверка валидности второго числа
    printf("\n                                  ---------------------------------------- (40 знаков)\n");
    printf("----> Введите вещественное число: ");

    char double_digit[INP_DBL_LEN + 1] = { '\0' };

    size_t rc_inp_d = input_str(double_digit, INP_DBL_LEN);

    char *dyn_ptr = double_digit;
    double temp_dbl = strtod(double_digit, &dyn_ptr);

    if (rc_inp_d == 0)
    {
        printf("\n----> Ошибка! Пустой ввод\n\n");
        return INP_DBL_ZERO;
    }

    if (rc_inp_d > INP_DBL_LEN)
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

    size_t rc_olen = check_order(double_digit, rc_inp_d);

    if (rc_olen > 5)
    {
        printf("\n----> Ошибка! Слишком длинный по модулю порядок\n\n");
        return INP_DBL_ORDER_OVERSIZE;
    }

    size_t rc_mlen = check_mantissa(double_digit, rc_inp_d);
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

    // реализация

    // обработка и приведение к структурному типу целого числа
    big_double first_digit;

    parse_sign(integer_digit, &first_digit);

    size_t sign_digits = check_mantissa(integer_digit, rc_inp_i);
    first_digit.n_sign_value = sign_digits;

    parse_mantissa_from_int(integer_digit, &first_digit, first_digit.n_sign_value);

    if (integer_digit[0] == '+' || integer_digit[0] == '-')
        --rc_inp_i;
    parse_order_from_int(&first_digit, rc_inp_i);

    // обработка и приведение к структурному типу вещественного числа
    big_double second_digit;

    parse_sign(double_digit, &second_digit);

    second_digit.n_sign_value = rc_mlen;

    parse_mantissa_from_dbl(double_digit, &second_digit, rc_mlen);

    int e_order = parse_e_order(double_digit, rc_inp_d);
    int root_order = parse_root_order(double_digit, rc_inp_d);

    int order = e_order + root_order;

    second_digit.order = order;

    // Умножение двух чисел
    if (first_digit.n_sign_value == 0 || second_digit.n_sign_value == 0)
    {
        printf("\n----> Результат = 0\n\n");
        return OK;
    }

    int result[MAX_MANT_LEN + MAX_MANT_LEN] = { 0 };

    give_multy(first_digit.mantissa, second_digit.mantissa, result, MAX_MANT_LEN, MAX_MANT_LEN, MAX_MULTY_LEN);

    res_round(result);

    int addit_order;
    if (result[0] != 0)
        addit_order = 60;
    else
        addit_order = 59;

    int based_order = first_digit.order + second_digit.order + addit_order;
    if (based_order > 99999 || based_order < -99999)
    {
        printf("\n----> Слишком большой порядок в ответе!\n\n");
        return RES_ORDER_OVERSIZE;
    }

    printf("\n----> Результат = ");
    if ((first_digit.sign == '+' && second_digit.sign == '+') || (first_digit.sign == '-' && second_digit.sign == '-'))
        printf("0.");
    else
        printf("-0.");
    print_array(result, MAX_MANT_LEN);
    printf("e");
    printf("%d", based_order);
    printf("\n\n");

    return OK;
}
