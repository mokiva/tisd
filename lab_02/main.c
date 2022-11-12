#include <stdio.h>

#include "defines.h"
#include "funcs.h"

int main(void)
{
    int choice = 1;

    while (choice != EXIT)
    {
        print_main_message();
        printf("    Выберите пункт меню: ");
        int rc = get_choice(&choice);
        if (rc)
        {
            printf("\n    Неверный ввод\n");
            continue;
        }
    }

    return SUCCESS;
}