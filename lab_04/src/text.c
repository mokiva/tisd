#include <stdio.h>

#include "text.h"

void print_menu(void)
{
    puts("");
    puts("  Меню\n");

    puts("  0. Выход\n");

    puts("  Реализация стека списком");
    puts("  1. Добавить элемент в стек");
    puts("  2. Удалить элемент из стека");
    puts("  3. Вывести текущее состояние стека");
    puts("  4. Вывести массив освободившихся адресов");
    puts("  5. Вычислить значение выражения\n");

    puts("  Реализация стека массивом");
    puts("  6. Добавить элемент в стек");
    puts("  7. Удалить элемент из стека");
    puts("  8. Вывести текущее состояние стека");
    puts("  9. Вычислить значение выражения\n");

    puts("  10. Произвести замеры времени и используемой памяти\n");

    printf("  Введите пункт меню: ");
}