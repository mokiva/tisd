#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>

#include "structs.h"

// вывод главного сообщения меню
void print_main_message(void);

// ввод значения для выбора пункта меню
int get_choice(int *choice);

// проверка корректности таблицы в файле
int load_table(table *tab);

#endif