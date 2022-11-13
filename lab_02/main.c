#include <stdio.h>

#include "defines.h"
#include "funcs.h"
#include "structs.h"

int main(void)
{
    int choice = 1;
    table tab;

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
                printf("\n-----------%d--------\n", rc);
                if (rc)
                {
                    printf("\n    Ошибка загрузки таблицы из файла\n");
                    break;
                }
        }
    }

    return SUCCESS;
}