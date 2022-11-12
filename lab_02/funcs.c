#include <stdio.h>
#include <ctype.h>

#include "defines.h"
#include "funcs.h"

void print_main_message(void)
{
    printf("    Выберите пункт меню:\n\n"
           "    0. Выход из программы\n"
           "    1. Загрузка таблицы из файла\n"
           "    2. Добавление записи в конец таблицы\n"
           "    3. Удаление записи таблицы по значению количества страниц\n"
           "    4. Просмотр отсортированной таблицы ключей\n"
           "    5. Вывод упорядоченной исходной таблицы\n"
           "    6. Вывод упорядоченной исходной таблицы, используя упорядоченную таблицу ключей\n"
           "    7. Вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и в таблице ключей\n"
           "    8. Вывод результатов использования различных алгоритмов сортировок для таблицы ключей\n"
           "    9. Вывод результатов использования различных алгоритмов сортировок для исходной таблицы\n\n");
}

int get_choice(int *choice)
{
    int ch;
    int count = 0;
    int digit = '\0';

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (count == 0)
            digit = ch;

        ++count;
    }

    ++count;

    if (count != 2)
        return BAD_GETCHAR_COUNT;

    if (isdigit(digit) == 0)
        return BAD_CHOICE_VALUE;

    *choice = digit;

    return SUCCESS;
}