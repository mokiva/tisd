#include <stdio.h>

#include "defs.h"
#include "text.h"
#include "adt.h"
#include "list.h"
#include "arr.h"
#include "my_time.h"

int main(void)
{
    int option = -1;

    list_t *stack_list = NULL;
    array_t stack_arr = {.arr = NULL, .len = 0};
    int max_stack_list_len = 0;
    int max_stack_arr_len = 0;
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

            if (!expression_result_list(&result))
                printf("\n  Результат вычисления выражения: %d", result);
        }

        if (option == 6)
        {
            if (!add_elem_arr(&stack_arr, &max_stack_arr_len))
                puts("\n  Элемент успешно добавлен");
        }

        if (option == 7)
        {
            if (!pop_arr(&stack_arr))
                puts("\n  Элемент удален");
        }

        if (option == 8)
            print_arr(&stack_arr);

        if (option == 9)
        {
            int result;

            if(!expression_result_arr(&result))
                printf("\n  Результат вычисления выражения: %d", result);

        }

        if (option == 10)
            time_counting();
    }

    if (stack_list)
    {
        free_list(&stack_list);
    }

    return SUCCESS;
}