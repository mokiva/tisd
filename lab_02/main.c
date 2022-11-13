#include <stdio.h>

#include "defines.h"
#include "funcs.h"
#include "structs.h"

int main(void)
{
    int choice = 1;
    table tab;
    tab.fields_count = 0;

    // Цикл выбора главного меню программы
    while (choice != EXIT)
    {
        print_main_message();
        printf("    Выберите пункт меню: ");

        // выбор пункта меню
        int rc = get_choice(&choice);
        if (rc)
        {
            printf("\n    Неверный ввод\n");
            continue;
        }

        switch (choice)
        {
            case '1':
                rc = load_table(&tab);
                if (rc)
                {
                    printf("\n    Ошибка загрузки таблицы из файла\n");
                    break;
                }
                else
                {
                    printf("\n    Таблицы загружена успешно\n");
                    print_table(tab);
                    break;
                }
            case '2':
                rc = append_record(&tab);
                if (rc)
                {
                    printf("\n    Ошибка добавления структуры\n");
                    break;
                }
                else
                {
                    printf("\n    Структура добавлена успешно\n");
                    print_table(tab);
                    break;
                }
            case '3':
                rc = delete_record(&tab);
                if (rc)
                {
                    printf("\n    Ошибка удаления записи(ей) структуры\n");
                    break;
                }
                else
                {
                    printf("\n    Все записи по данному значению поля удалены успешно\n");
                    print_table(tab);
                    break;
                }
            case '4':
                rc = sort_key_table(&tab);
                if (rc)
                {
                    printf("\n    Таблицы ключей пустая\n");
                    break;
                }
                else
                {
                    printf("\n    Таблица ключей отсортирована\n");
                    print_key_table(tab);
                    break;
                }

        }
    }

    return SUCCESS;
}