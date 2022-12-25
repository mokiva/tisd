#include <stdio.h>

#include "defs.h"
#include "text.h"
#include "adt.h"
#include "list.h"

int main(void)
{
    int option = -1;

    list_t *stack_list = NULL;
    int max_stack_list_len = 0;
    array_clear_t clear_arr = { .len = 0 };

    while (option != 0)
    {
        print_menu();

        int rc = scanf("%d", &option);

        if ((rc != 1) || (option < 0) || (option > 10))
        {
            puts("");
            puts("  Ошибка выбора пункта меню");
            setbuf(stdin, NULL);
            continue;
        }

        if (option == 0)
            break;

        if (option == 1)
        {
            if (!add_elem_stack_list(&stack_list, &max_stack_list_len))
            {
                puts("\n  Элемент успешно добавлен");
                del_address(&clear_arr, stack_list);
            }
        }

        if (option == 2)
        {
            add_address(&clear_arr, stack_list);

            if (!pop_elem_stack_list(&stack_list))
                puts("\n  Элемент удален");
        }

        if (option == 3)
            print_list(stack_list);

        if (option == 4)
            print_addresses(clear_arr);

        if (option == 5)
        {
            int result;

            if (!expression_result(&result))
                ;
        }
    }

    // free elems;

    return SUCCESS;
}