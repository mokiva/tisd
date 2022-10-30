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

// заголовок функции, заполняющей поле мантиссы в стуктуре
void parse_mantissa_from_int(char *buffer, big_double *value, size_t mant_len);

// заголовок функции, печатающей массив
void print_array(int arr[], int len);

// заголовок функции, заполняющей поле порядка в структуре
void parse_order_from_int(big_double *value, size_t mant_len);

#endif  // __FUNCS_H__




















