#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "defines.h"
#include "funcs.h"
#include "structs.h"

void print_main_message(void)
{
    printf("\n    0. Выход из программы\n"
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

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (count == 0)
            *choice = ch;

        ++count;
    }

    if (count != 1 || isdigit(*choice) == 0)
        return FAILURE;

    return SUCCESS;
}

int load_table(table *tab)
{
    FILE *file = fopen(FILE_WITH_TABLE, "r");

    if (file == NULL || getc(file) == EOF)
        return BAD_FILE;

    fclose(file);

    file = fopen(FILE_WITH_TABLE, "r");

    int size = 0;

    if (fscanf(file, "%d", &size) != 1)
        return BAD_SIZE_IN_FILE;

    if (size <= 0)
        return BAD_SIZE_IN_FILE;

    tab -> fields_count = size;

    for (int i = 0; i < size; ++i)
    {
        // заполнение поля фамилии автора
        int ch;
        int j = 0;
        char buffer_author_surname[BUFFER_LENGTH + 1] = { '\0' };

        getc(file); // съедает лишний '\n' перед новой строкой

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_author_surname[j] = (char) ch;
            ++j;
        }

        strncpy(tab -> literatures_instances[i].author_surname, buffer_author_surname, BUFFER_LENGTH + 1);

        // заполнение поля названия книги
        j = 0;

        char buffer_book_title[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_book_title[j] = (char) ch;
            ++j;
        }

        strncpy(tab -> literatures_instances[i].book_title, buffer_book_title, BUFFER_LENGTH + 1);

        // заполнение поля издателя книги
        j = 0;
        char buffer_publisher_name[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_publisher_name[j] = (char) ch;
            ++j;
        }

        strncpy(tab -> literatures_instances[i].publisher_name, buffer_publisher_name, BUFFER_LENGTH + 1);

        // заполнение количества страниц
        j = 0;
        char buffer_number_of_pages[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_number_of_pages[j] = (char) ch;
            ++j;
        }

        for (int k = 0; k < j; ++k)
        {
            if (isdigit(buffer_number_of_pages[k]) == 0)
            {
                return BAD_DIGIT;
            }
        }
        int digit = (int) strtol(buffer_number_of_pages, NULL, 10);
        if (digit > 99999 || digit <= 0 || errno == ERANGE)
            return BAD_CONVERSION_TO_DIGIT;

        tab -> literatures_instances[i].number_of_pages = digit;
        tab -> key_instances[i].key_value = digit;
        tab -> key_instances[i].key_index = i;

        // заполнение вида литературы
        j = 0;
        char buffer_book_type[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_book_type[j] = (char) ch;
            ++j;
        }

        for (int k = 0; k < j; ++k)
        {
            if (isdigit(buffer_book_type[k]) == 0)
            {
                return BAD_DIGIT;
            }
        }
        digit = (int) strtol(buffer_book_type, NULL, 10);
        if (digit != 1 && digit != 2 && digit != 3)
            return BAD_LIT_TYPE;

        tab -> literatures_instances[i].int_type = digit;

        // если литература техническая
        if (digit == 1)
        {
            // заполнение сферы литературы
            j = 0;

            char buffer_sphere_name[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_sphere_name[j] = (char) ch;
                ++j;
            }

            strncpy(tab -> literatures_instances[i].type.technical_type.sphere, buffer_sphere_name, BUFFER_LENGTH + 1);

            // заполнение отечественная или переводная
            j = 0;
            char buffer_domestic_or_translated[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_domestic_or_translated[j] = (char) ch;
                ++j;
            }

            for (int k = 0; k < j; ++k)
            {
                if (isdigit(buffer_domestic_or_translated[k]) == 0)
                {
                    return BAD_DIGIT;
                }
            }
            digit = (int) strtol(buffer_domestic_or_translated, NULL, 10);
            if (digit != 1 && digit != 2)
                return BAD_LIT_TYPE;

            tab -> literatures_instances[i].type.technical_type.domestic_or_translated = digit;

            //заполнение года издания
            j = 0;
            char buffer_year_of_publication[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_year_of_publication[j] = (char) ch;
                ++j;
            }

            for (int k = 0; k < j; ++k)
            {
                if (isdigit(buffer_year_of_publication[k]) == 0)
                {
                    return BAD_DIGIT;
                }
            }

            digit = (int) strtol(buffer_year_of_publication, NULL, 10);
            if (digit > 2022 || digit <= 0 || errno == ERANGE)
                return BAD_LIT_TYPE;

            tab -> literatures_instances[i].type.technical_type.year_of_publication = digit;

        }
        else if (digit == 2) // если литература художественная
        {
            j = 0;
            char buffer_artistic_type[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_artistic_type[j] = (char) ch;
                ++j;
            }

            for (int k = 0; k < j; ++k)
            {
                if (isdigit(buffer_artistic_type[k]) == 0)
                {
                    return BAD_DIGIT;
                }
            }
            digit = (int) strtol(buffer_artistic_type, NULL, 10);
            if (digit != 1 && digit != 2 && digit != 3)
                return BAD_LIT_TYPE;

            tab -> literatures_instances[i].type.artistic_type.artistic_type = digit;
        }
        else if (digit == 3) // если литература детская
        {
            j = 0;
            char buffer_children_type[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_children_type[j] = (char) ch;
                ++j;
            }

            for (int k = 0; k < j; ++k)
            {
                if (isdigit(buffer_children_type[k]) == 0)
                {
                    return BAD_DIGIT;
                }
            }
            digit = (int) strtol(buffer_children_type, NULL, 10);
            if (digit != 1 && digit != 2)
                return BAD_LIT_TYPE;

            tab -> literatures_instances[i].type.children_type.children_type = digit;
        }
    }

    fclose(file);
    return SUCCESS;
}

int append_field(table *tab)
{
    // заполнения поля фамилии автора
    printf("\n    Введите имя автора книги: ");
    char buffer_author_surname[BUFFER_LENGTH + 1] = { '\0' };
    int ch;
    int count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_author_surname[count] = (char) ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    int index = tab -> fields_count;
    strncpy(tab -> literatures_instances[index].author_surname, buffer_author_surname, BUFFER_LENGTH + 1);

    // заполнение поля названия книги
    printf("\n    Введите название книги: ");
    char buffer_book_title[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_book_title[count] = (char) ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    strncpy(tab -> literatures_instances[index].book_title, buffer_book_title, BUFFER_LENGTH + 1);

    // заполнение поля названия издательства
    printf("\n    Введите название издательства: ");
    char buffer_publisher_name[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_publisher_name[count] = (char) ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    strncpy(tab -> literatures_instances[index].publisher_name, buffer_publisher_name, BUFFER_LENGTH + 1);

    // заполнение поля количества страниц в книге
    printf("\n    Введите количество страниц в книге: ");
    char buffer_number_of_pages[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_number_of_pages[count] = (char) ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_number_of_pages[i]) == 0)
            return BAD_DIGIT;

    int digit = (int) strtol(buffer_number_of_pages, NULL, 10);
    if (digit <= 0 || digit > 99999 || errno == ERANGE)
        return BAD_CONVERSION_TO_DIGIT;

    tab -> literatures_instances[index].number_of_pages = digit;
    tab -> key_instances[index].key_value = digit;
    tab -> key_instances[index].key_index = index;

    // заполнение поля типа литературы
    printf("\n    1. Техническая\n"
           "    2. Художественная\n"
           "    3. Детская\n\n");

    printf("    Выберите пункт меню: ");

    char buffer_int_type[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_int_type[count] = (char) ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_int_type[i]) == 0)
            return BAD_DIGIT;

    digit = (int) strtol(buffer_int_type, NULL, 10);
    if (digit != 1 && digit != 2 && digit != 3)
        return BAD_CONVERSION_TO_DIGIT;

    tab -> literatures_instances[index].int_type = digit;

    tab -> fields_count += 1;
    return SUCCESS;
}