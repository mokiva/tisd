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

// Сортировка таблицы qsort
int qsort_table(table *tab);

// Сортировка таблицы ключей qsort
int qsort_key_table(table *tab);

// Компаратор для обычной таблицы
int table_comparator(const void *first, const void *second);

// Компаратор для таблицы ключей
int key_table_comparator(const void *first, const void *second);

// Функция сравнения времени для разных сортировок для разных таблиц
void analysis(table *tab);

// Поиск списка отечественной технической литературы по указанной отрасли указанного года
int search_domestic(table tab);

// Пересобрать заново таблицу ключей
void collect_new_key_table(table *tab);

#endif