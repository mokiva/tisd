#include <stdio.h>

#include "defines.h"
#include "funcs.h"

int main(void)
{
    int choice = 1;

    while (choice != EXIT)
    {
        print_main_message();
        get_choice(&choice);
    }

    return SUCCESS;
}