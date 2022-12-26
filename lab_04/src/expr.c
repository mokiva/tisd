#include <stdio.h>

#include "expr.h"

int check_operation(char ch)
{
    if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/'))
        return RIGHT;
    else
        return UNRIGHT;
}

int read_expression(expression_t *expression)
{
    puts("\n  Введите выражение в следующем формате без пробелов: число|знак|число...|знак|число"
         "\n  Доступные операции: + - * /\n");

    char sym;
    int rc;
    int i = 0;

    printf("  ");
    scanf("%c", &sym);

    while (((rc = scanf("%c", &sym)) == 1) && (sym != '\n'))
    {
        if ((sym > '9') || (sym < '0'))
        {
            if (!check_operation(sym))
            {
                puts("  Неверный символ в выражении");
                setbuf(stdin, NULL);
                return WRONG_SYMBOL;
            }
        }

        if (check_operation(sym))
        {
            if ((expression -> sym[i - 1] == '+') || (expression -> sym[i - 1] == '-'))
            {
                puts("  Не может быть введено несколько знаков подряд");
                setbuf(stdin, NULL);
                return WRONG_SYMBOL;
            }
        }

        expression -> sym[i++] = sym;
    }

    expression -> sym[i] = '\0';

    if (check_operation(expression -> sym[0]))
    {
        puts("  Первым должно быть введено число");
        return FIRST_SIGN;
    }

    if (check_operation(expression -> sym[i - 1]))
    {
        puts("  Последним должно быть введено число");
        return LAST_SIGN;
    }

    printf("  Выражение: %s\n", expression -> sym);

    expression -> len = i;

    return SUCCESS;
}

int translate_operation(char ch)
{
    if (ch == '+')
        return 1;

    if (ch == '-')
        return 2;

    if (ch == '*')
        return 3;

    return 4;
}

int check_priority(int ch)
{
    if (ch == 1 || ch == 2)
        return 1;

    return 2;
}

int read_num_from_arr_char(char *ch, int *ind)
{
    char num[150];
    int i = 0;

    while (ch[*ind] >= '0' && ch[*ind] <= '9')
    {
        num[i] = ch[*ind];
        i++;
        *ind += 1;
    }

    num[i] = '\0';

    int number;
    sscanf(num, "%d", &number);

    return number;
}