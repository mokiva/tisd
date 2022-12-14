#include <stdio.h>

#include "defines.h"
#include "funcs.h"
#include "structs.h"

int main(void)
{
    int choice = 1;
    int flag = 0;
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
                    flag = 0;
                    printf("\n    Таблица загружена успешно\n");
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
                    break;
                }
            case '3':
                if (tab.fields_count == 0)
                {
                    printf("\n    Таблица пустая\n");
                    break;
                }

                if (!flag)
                {
                    rc = delete_record(&tab);
                    if (rc)
                    {
                        printf("\n    Ошибка удаления записи(ей) структуры\n");
                        break;
                    }
                    else
                    {
                        printf("\n    Все записи по данному значению поля удалены успешно\n");
                        break;
                    }
                }
                else
                {
                    collect_new_key_table(&tab);
                    rc = delete_record(&tab);
                    if (rc)
                    {
                        printf("\n    Ошибка удаления записи(ей) структуры\n");
                        break;
                    }
                    else
                    {
                        sort_key_table(&tab);
                        printf("\n    Все записи по данному значению поля удалены успешно\n");
                        break;
                    }
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
                    printf("\n    Таблицы ключей успешно отсортирована\n");
                    flag = 1;
                    break;
                }
            case '5':
                rc = sort_table(&tab);
                if (rc)
                {
                    printf("\n    Таблица пустая\n");
                    break;
                }
                else
                {
                    printf("\n    Таблица успешно отсортирована\n");
                    collect_new_key_table(&tab);
                    break;
                }
            case '6':
                rc = sort_key_table(&tab);
                if (rc)
                {
                    printf("\n    Таблицы ключей пустая\n");
                    break;
                }
                else
                {
                    print_sort_table_by_key(tab);
                    flag = 1;
                    break;
                }
            case '7':
                analysis(&tab);
                break;
            case '8':
                if (tab.fields_count > 0)
                {
                    print_table(tab);
                    print_key_table(tab);
                    break;
                }
                else
                {
                    printf("\n    Таблицы пустые\n");
                    break;
                }
            case '9':
                rc = search_domestic(tab);
                if (rc)
                {
                    printf("\n    Ошибка поиска\n");
                    break;
                }
                break;
        }
    }

    return SUCCESS;
}