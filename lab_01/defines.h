#ifndef __DEFINES_H__
#define __DEFINES_H__

// коды ошибок
#define OK                     0
#define INP_INT_OVERSIZE       1  // код ошибки, если ввод в поле целого числа слишком длинный
#define INP_INT_ZERO           2  // код ошибки, если ввод в поле целого числа пустой
#define INP_INT_INCOR          3  // код ошибки, если ввод в поле целого числа некорректный
#define INP_DBL_OVERSIZE       4  // код ошибки, если ввод в поле вещественного числа слишком длинный
#define INP_DBL_ZERO           5  // код ошибки, если ввод в поле вещественного числа пустой
#define INP_DBL_INCOR          6  // код ошибки, если ввод в поле вещественного числа некорректный
#define INP_DBL_ORDER_OVERSIZE 7  // код ошибки, если длина порядка слишком длинная
#define INP_DBL_MANTISSA       8  // код ошибки, если длина мантиссы слишком длинная
#define INP_DBL_FZERO          9  // код ошибки, если в целая часть вещественного числа начинается с нескольких нулей
#define INP_INT_VAL_OVERSIZE  10  // код ошикби, если в поле целого числа введено более 30 десятичных цифр

// размеры
#define INP_INT_LEN   31  // размер ввода целого числа (знак + 30 значащих цифр)
#define INP_DBL_LEN   40  // размер ввода вещественного числа (знак + 0 + . + 30 значащих цифр мантиссы + e + знак + 5 значащих цифр порядка)
#define MAX_MANT_LEN  30  // максимальная длина значащих цифр мантиссы

// константы
#define TRUE  1
#define FALSE 0

#endif  // __DEFINES_H__
