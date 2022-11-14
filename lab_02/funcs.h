#ifndef FUNCS_H
#define FUNCS_H

#include "structs.h"

// вывод главного сообщения меню
void print_main_message(void);

// ввод значения для выбора пункта меню
int get_choice(int *choice);

// проверка корректности таблицы в файле
int load_table(table *tab);

// добавление в таблицу записи
int append_record(table *tab);

// Печать таблицы
void print_table(table tab);

// Удаление из таблицы по количеству страниц
int delete_record(table *tab);

// Сортировка таблицы ключей
int sort_key_table(table *tab);

// Печать таблицы ключей
void print_key_table(table tab);

// Сортировка таблицы
int sort_table(table *tab);

// Печать отсортированной таблицы по отсортированной таблице ключей
void print_sort_table_by_key(table tab);

#endif