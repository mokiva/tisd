#ifndef __FUNCS_H__
#define __FUNCS_H__

#include <stdio.h>

#include "struct.h"

// заголовок функции, реализующей ввод строки
size_t input_str(char *buffer, size_t len);

// заголовок функции, реализующей проверку корректности длины введённого целого числа
size_t check_int_len(char *buffer, size_t len);

// заголовок функции, реализующей проверку корректности содержимого введённого целого числа
size_t check_int_content(char *buffer, size_t len);

// заголовок функции, реализующий проверку длины порядка
size_t check_order(char *buffer, size_t len);

// заголовок функции, реализующей проверку длины мантиссы
size_t check_mantissa(char *buffer, size_t len);

// заголовок функции, реализующей проверку нескольких нулей в начале целой части вещественного числа
size_t check_zeros(char *buffer);

// заголовок функции, парсящей знак числа в поле структуры
void parse_sign(char *buffer, big_double *value);

// заголовок функции, заполняющей поле мантиссы целого числа в стуктуре
void parse_mantissa_from_int(char *buffer, big_double *value, size_t mant_len);

// заголовок функции, печатающей массив
void print_array(int *arr, size_t len);

// заголовок функции, заполняющей поле порядка целого числа в структуре
void parse_order_from_int(big_double *value, size_t mant_len);

// заголовок функции, заполняющей поле мантиссы вещественного числа в структуре
void parse_mantissa_from_dbl(char *buffer, big_double *value, size_t mant_len);

// заголовок функции, возвращающей порядок при e
int parse_e_order(char *buffer, size_t len);

// заголовок функции, возвращающей порядок действительной части числа
int parse_root_order(char *buffer, size_t mant_len);

// заголовок функции, реализующей умножение чисел, записанных в двух массивах и записывающей результат в третий
void give_multy(int *arr1, int *arr2, int *res, size_t len1, size_t len2, size_t rlen);

// заголовок функции, реализующей округление числа
void res_round(int *res);

#endif  // __FUNCS_H__
