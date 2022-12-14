#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "defines.h"
#include "funcs.h"
#include "structs.h"

void print_main_message(void)
{
    printf("\n    0. Выход из программы\n"
           "    1. Загрузка таблицы из файла\n"
           "    2. Добавление записи в конец таблицы\n"
           "    3. Удаление записи таблицы по значению количества страниц\n"
           "    4. Сортировка таблицы ключей\n"
           "    5. Сортировка исходной таблицы\n"
           "    6. Вывод сортировки исходной таблицы, используя отсортированную таблицу ключей\n"
           "    7. Вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и в таблице ключей\n"
           "    8. Вывод таблицы и таблицы ключей\n"
           "    9. Поиск списка отечественной технической литературы по указанной отрасли указанного года\n\n");
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
    if (tab -> fields_count > MAX_FIELDS)
        return BAD_FIELDS_COUNT;

    for (int i = 0; i < tab -> fields_count; ++i)
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

        if (buffer_author_surname[0] == '\n' || buffer_author_surname[0] == '\0' || buffer_author_surname[0] == ' ')
            return EMPTY_FIELD;

        strncpy(tab -> literatures_instances[i].author_surname, buffer_author_surname, BUFFER_LENGTH + 1);

        // заполнение поля названия книги
        j = 0;

        char buffer_book_title[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_book_title[j] = (char) ch;
            ++j;
        }

        if (buffer_book_title[0] == '\n' || buffer_book_title[0] == '\0' || buffer_book_title[0] == ' ')
            return EMPTY_FIELD;

        strncpy(tab -> literatures_instances[i].book_title, buffer_book_title, BUFFER_LENGTH + 1);

        // заполнение поля издателя книги
        j = 0;
        char buffer_publisher_name[BUFFER_LENGTH + 1] = { '\0' };

        while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
        {
            buffer_publisher_name[j] = (char) ch;
            ++j;
        }

        if (buffer_publisher_name[0] == '\n' || buffer_publisher_name[0] == '\0' || buffer_publisher_name[0] == ' ')
            return EMPTY_FIELD;

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

        if (buffer_book_type[0] == '\n' || buffer_book_type[0] == '\0' || buffer_book_type[0] == ' ')
            return EMPTY_FIELD;

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

            if (buffer_sphere_name[0] == '\n' || buffer_sphere_name[0] == '\0' || buffer_sphere_name[0] == ' ')
                return EMPTY_FIELD;

            strncpy(tab -> literatures_instances[i].type.technical_type.sphere, buffer_sphere_name, BUFFER_LENGTH + 1);

            // заполнение отечественная или переводная
            j = 0;
            char buffer_domestic_or_translated[BUFFER_LENGTH + 1] = { '\0' };

            while ((ch = getc(file)) != ';' && j < BUFFER_LENGTH)
            {
                buffer_domestic_or_translated[j] = (char) ch;
                ++j;
            }

            if (buffer_domestic_or_translated[0] == '\n' || buffer_domestic_or_translated[0] == '\0' || buffer_domestic_or_translated[0] == ' ')
                return EMPTY_FIELD;

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

            if (buffer_year_of_publication[0] == '\n' || buffer_year_of_publication[0] == '\0' || buffer_year_of_publication[0] == ' ')
                return EMPTY_FIELD;

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

            if (buffer_artistic_type[0] == '\n' || buffer_artistic_type[0] == '\0' || buffer_artistic_type[0] == ' ')
                return EMPTY_FIELD;

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

            if (buffer_children_type[0] == '\n' || buffer_children_type[0] == '\0' || buffer_children_type[0] == ' ')
                return EMPTY_FIELD;

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

int append_record(table *tab)
{
    if (tab -> fields_count >= MAX_FIELDS)
        return BAD_FIELDS_COUNT;
    // заполнения поля фамилии автора
    printf("\n    Введите имя автора книги: ");
    char buffer_author_surname[BUFFER_LENGTH + 1] = { '\0' };
    int ch;
    int count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_author_surname[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_author_surname[0] == '\n' || buffer_author_surname[0] == '\0' || buffer_author_surname[0] == ' ')
        return EMPTY_FIELD;

    int index = tab->fields_count;
    strncpy(tab->literatures_instances[index].author_surname, buffer_author_surname, BUFFER_LENGTH + 1);

    // заполнение поля названия книги
    printf("\n    Введите название книги: ");
    char buffer_book_title[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_book_title[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_book_title[0] == '\n' || buffer_book_title[0] == '\0' || buffer_book_title[0] == ' ')
        return EMPTY_FIELD;

    strncpy(tab->literatures_instances[index].book_title, buffer_book_title, BUFFER_LENGTH + 1);

    // заполнение поля названия издательства
    printf("\n    Введите название издательства: ");
    char buffer_publisher_name[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_publisher_name[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_publisher_name[0] == '\n' || buffer_publisher_name[0] == '\0' || buffer_publisher_name[0] == ' ')
        return EMPTY_FIELD;

    strncpy(tab->literatures_instances[index].publisher_name, buffer_publisher_name, BUFFER_LENGTH + 1);

    // заполнение поля количества страниц в книге
    printf("\n    Введите количество страниц в книге: ");
    char buffer_number_of_pages[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_number_of_pages[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_number_of_pages[0] == '\n' || buffer_number_of_pages[0] == '\0' || buffer_number_of_pages[0] == ' ')
        return EMPTY_FIELD;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_number_of_pages[i]) == 0)
            return BAD_DIGIT;

    int digit = (int)strtol(buffer_number_of_pages, NULL, 10);
    if (digit <= 0 || digit > 99999 || errno == ERANGE)
        return BAD_CONVERSION_TO_DIGIT;

    tab->literatures_instances[index].number_of_pages = digit;
    tab->key_instances[index].key_value = digit;
    tab->key_instances[index].key_index = index;

    // заполнение поля типа литературы
    printf("\n    1. Техническая\n"
           "    2. Художественная\n"
           "    3. Детская\n\n");

    printf("    Выберите тип книги: ");

    char buffer_int_type[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_int_type[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_int_type[0] == '\n' || buffer_int_type[0] == '\0' || buffer_int_type[0] == ' ')
        return EMPTY_FIELD;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_int_type[i]) == 0)
            return BAD_DIGIT;

    digit = (int)strtol(buffer_int_type, NULL, 10);
    if (digit != 1 && digit != 2 && digit != 3)
        return BAD_CONVERSION_TO_DIGIT;

    tab->literatures_instances[index].int_type = digit;

    // техническая литература
    if (digit == 1)
    {
        // вид сферы
        printf("\n    Введите сферу книги: ");
        char buffer_sphere[BUFFER_LENGTH + 1] = { '\0' };
        count = 0;

        while ((ch = getchar()) != '\n')
        {
            if (count < BUFFER_LENGTH)
                buffer_sphere[count] = (char)ch;

            ++count;
        }

        if (count > BUFFER_LENGTH)
            return LONG_INPUT;

        if (buffer_sphere[0] == '\n' || buffer_sphere[0] == '\0' || buffer_sphere[0] == ' ')
            return EMPTY_FIELD;

        strncpy(tab->literatures_instances[index].type.technical_type.sphere, buffer_sphere, BUFFER_LENGTH + 1);

        // отечественная или переводная
        printf("\n    1. Отечественный\n"
               "    2. Переводной\n\n");

        printf("    Выберите перевод книги: ");

        char buffer_domestic_or_translated[BUFFER_LENGTH + 1] = { '\0' };
        count = 0;

        while ((ch = getchar()) != '\n')
        {
            if (count < BUFFER_LENGTH)
                buffer_domestic_or_translated[count] = (char)ch;

            ++count;
        }

        if (count > BUFFER_LENGTH)
            return LONG_INPUT;

        if (buffer_domestic_or_translated[0] == '\n' || buffer_domestic_or_translated[0] == '\0' || buffer_domestic_or_translated[0] == ' ')
            return EMPTY_FIELD;

        for (int i = 0; i < count; ++i)
            if (isdigit(buffer_domestic_or_translated[i]) == 0)
                return BAD_DIGIT;

        digit = (int)strtol(buffer_domestic_or_translated, NULL, 10);
        if (digit != 1 && digit != 2)
            return BAD_CONVERSION_TO_DIGIT;

        tab -> literatures_instances[index].type.technical_type.domestic_or_translated = digit;
        // год издания
        printf("\n    Укажите год издания книги: ");
        char buffer_year_of_publication[BUFFER_LENGTH + 1] = { '\0' };
        count = 0;

        while ((ch = getchar()) != '\n')
        {
            if (count < BUFFER_LENGTH)
                buffer_year_of_publication[count] = (char)ch;

            ++count;
        }

        if (buffer_year_of_publication[0] == '\n' || buffer_year_of_publication[0] == '\0' || buffer_year_of_publication[0] == ' ')
            return EMPTY_FIELD;

        if (count > BUFFER_LENGTH)
            return LONG_INPUT;

        for (int i = 0; i < count; ++i)
            if (isdigit(buffer_year_of_publication[i]) == 0)
                return BAD_DIGIT;

        digit = (int)strtol(buffer_year_of_publication, NULL, 10);
        if (digit > 2022 || digit <= 0 || errno == ERANGE)
            return BAD_CONVERSION_TO_DIGIT;

        tab -> literatures_instances[index].type.technical_type.year_of_publication = digit;
    }
    else if (digit == 2) // художественная литература
    {
        printf("\n    1. Роман\n"
               "    2. Пьеса\n"
               "    3. Стихи\n\n");

        printf("    Выберите тип художественной книги: ");

        char buffer_artistic[BUFFER_LENGTH + 1] = { '\0' };
        count = 0;

        while ((ch = getchar()) != '\n')
        {
            if (count < BUFFER_LENGTH)
                buffer_artistic[count] = (char)ch;

            ++count;
        }

        if (count > BUFFER_LENGTH)
            return LONG_INPUT;

        if (buffer_artistic[0] == '\n' || buffer_artistic[0] == '\0' || buffer_artistic[0] == ' ')
            return EMPTY_FIELD;

        for (int i = 0; i < count; ++i)
            if (isdigit(buffer_artistic[i]) == 0)
                return BAD_DIGIT;

        digit = (int)strtol(buffer_artistic, NULL, 10);
        if (digit != 1 && digit != 2 && digit != 3)
            return BAD_CONVERSION_TO_DIGIT;

        tab -> literatures_instances[index].type.artistic_type.artistic_type = digit;
    }
    else if (digit == 3) // детская литература
    {
        printf("\n    1. Сказки\n"
               "    2. Пьеса\n\n");

        printf("    Выберите тип детской книги: ");

        char buffer_children[BUFFER_LENGTH + 1] = { '\0' };
        count = 0;

        while ((ch = getchar()) != '\n')
        {
            if (count < BUFFER_LENGTH)
                buffer_children[count] = (char)ch;

            ++count;
        }

        if (count > BUFFER_LENGTH)
            return LONG_INPUT;

        if (buffer_children[0] == '\n' || buffer_children[0] == '\0' || buffer_children[0] == ' ')
            return EMPTY_FIELD;

        for (int i = 0; i < count; ++i)
            if (isdigit(buffer_children[i]) == 0)
                return BAD_DIGIT;

        digit = (int)strtol(buffer_children, NULL, 10);
        if (digit != 1 && digit != 2)
            return BAD_CONVERSION_TO_DIGIT;

        tab -> literatures_instances[index].type.children_type.children_type = digit;
    }

    tab -> fields_count += 1;
    return SUCCESS;
}

void print_table(table tab)
{
    printf("\n%30s", "Author surname");
    printf("%30s", "Book title");
    printf("%30s", "Publisher");
    printf("%30s", "Number of pages");
    printf("%30s", "Book type");
    printf("%50s\n\n", "Other");

    for (int i = 0; i < tab.fields_count; ++i)
    {
        printf("%30s", tab.literatures_instances[i].author_surname);
        printf("%30s", tab.literatures_instances[i].book_title);
        printf("%30s", tab.literatures_instances[i].publisher_name);
        printf("%30d", tab.literatures_instances[i].number_of_pages);
        if (tab.literatures_instances[i].int_type == 1)
        {
            printf("%30s", "technical");
            printf("%30s", tab.literatures_instances[i].type.technical_type.sphere);
            if (tab.literatures_instances[i].type.technical_type.domestic_or_translated == 1)
            {
                printf("%10s", "domestic");
            }
            else
            {
                printf("%10s", "import");
            }
            printf("%10d\n", tab.literatures_instances[i].type.technical_type.year_of_publication);
        }
        else if (tab.literatures_instances[i].int_type == 2)
        {
            printf("%30s", "artistic");

            if (tab.literatures_instances[i].type.artistic_type.artistic_type == 1)
            {
                printf("%50s\n", "romance");
            }
            else if (tab.literatures_instances[i].type.artistic_type.artistic_type == 2)
            {
                printf("%50s\n", "piece");
            }
            else
            {
                printf("%50s\n", "poem");
            }
        }
        else
        {
            printf("%30s", "children");

            if (tab.literatures_instances[i].type.children_type.children_type == 1)
            {
                printf("%50s\n", "fairy tail");
            }
            else
            {
                printf("%50s\n", "poem");
            }
        }
    }
}

int delete_record(table *tab)
{
    if (tab -> fields_count == 0)
    {
        printf("\n    В таблице нет записей\n");
        return EMPTY_TABLE;
    }

    printf("\n    Введите значение поля \"количество страниц\": ");
    char buffer_number_of_pages[BUFFER_LENGTH + 1] = { '\0' };
    int count = 0;
    int ch;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_number_of_pages[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_number_of_pages[0] == '\n' || buffer_number_of_pages[0] == '\0' || buffer_number_of_pages[0] == ' ')
        return EMPTY_FIELD;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_number_of_pages[i]) == 0)
            return BAD_DIGIT;

    int digit = (int)strtol(buffer_number_of_pages, NULL, 10);
    if (digit <= 0 || digit > 99999 || errno == ERANGE)
        return BAD_CONVERSION_TO_DIGIT;

    int temp_fields = tab -> fields_count;

    for (int i = 0; i < temp_fields; ++i)
    {
        if (tab -> literatures_instances[i].number_of_pages == digit)
        {
            for (int j = i; j < temp_fields - 1; ++j)
                tab -> literatures_instances[j] = tab -> literatures_instances[j + 1];

            temp_fields -= 1;

            --i;
        }
    }

    for (int i = 0; i < tab -> fields_count; ++i)
    {
        if (tab -> key_instances[i].key_value == digit)
        {
//            int index = tab -> key_instances[i].key_index;

            for (int j = i; j < tab -> fields_count - 1; ++j)
                tab->key_instances[j].key_value = tab->key_instances[j + 1].key_value;

//            for (int k = 0; k < tab -> fields_count; ++k)
//            {
//                if (tab -> key_instances[k].key_index > index)
//                    --tab -> key_instances[k].key_index;
//            }

            tab -> fields_count -= 1;

            --i;
        }
    }

    return SUCCESS;
}

int sort_key_table(table *tab)
{
    if (tab -> fields_count == 0)
        return EMPTY_TABLE;

    for (int i = 0; i < tab -> fields_count - 1; ++i)
    {
        for (int j = 0; j < tab -> fields_count - i - 1; ++j)
        {
            if (tab -> key_instances[j].key_value > tab -> key_instances[j + 1].key_value)
            {
                key_struct temp = tab -> key_instances[j + 1];
                tab -> key_instances[j + 1] = tab -> key_instances[j];
                tab -> key_instances[j] = temp;
            }
        }
    }

    return SUCCESS;
}

void print_key_table(table tab)
{
    printf("\n%30s", "Key index");
    printf("%30s\n\n", "Key value");

    for (int i = 0; i < tab.fields_count; ++i)
    {
        printf("%30d", tab.key_instances[i].key_index);
        printf("%30d\n", tab.key_instances[i].key_value);
    }
}

int sort_table(table *tab)
{
    if (tab -> fields_count == 0)
        return EMPTY_TABLE;

    for (int i = 0; i < tab -> fields_count - 1; ++i)
    {
        for (int j = 0; j < tab -> fields_count - i - 1; ++j)
        {
            if (tab -> literatures_instances[j].number_of_pages > tab -> literatures_instances[j + 1].number_of_pages)
            {
                literature_instance temp_1 = tab -> literatures_instances[j + 1];
                tab -> literatures_instances[j + 1] = tab -> literatures_instances[j];
                tab -> literatures_instances[j] = temp_1;
            }
        }
    }

    return SUCCESS;
}

void collect_new_key_table(table *tab)
{
    for (int i = 0; i < tab -> fields_count; ++i)
    {
        tab -> key_instances[i].key_index = i;
        tab -> key_instances[i].key_value = tab -> literatures_instances[i].number_of_pages;
    }
}

void print_sort_table_by_key(table tab)
{
    printf("\n%30s", "Author surname");
    printf("%30s", "Book title");
    printf("%30s", "Publisher");
    printf("%30s", "Number of pages");
    printf("%30s", "Book type");
    printf("%50s\n\n", "Other");

    for (int i = 0; i < tab.fields_count; ++i)
    {
        printf("%30s", tab.literatures_instances[tab.key_instances[i].key_index].author_surname);
        printf("%30s", tab.literatures_instances[tab.key_instances[i].key_index].book_title);
        printf("%30s", tab.literatures_instances[tab.key_instances[i].key_index].publisher_name);
        printf("%30d", tab.literatures_instances[tab.key_instances[i].key_index].number_of_pages);
        if (tab.literatures_instances[tab.key_instances[i].key_index].int_type == 1)
        {
            printf("%30s", "technical");
            printf("%30s", tab.literatures_instances[tab.key_instances[i].key_index].type.technical_type.sphere);
            if (tab.literatures_instances[tab.key_instances[i].key_index].type.technical_type.domestic_or_translated == 1)
            {
                printf("%10s", "domestic");
            }
            else
            {
                printf("%10s", "import");
            }
            printf("%10d\n", tab.literatures_instances[tab.key_instances[i].key_index].type.technical_type.year_of_publication);
        }
        else if (tab.literatures_instances[tab.key_instances[i].key_index].int_type == 2)
        {
            printf("%30s", "artistic");

            if (tab.literatures_instances[tab.key_instances[i].key_index].type.artistic_type.artistic_type == 1)
            {
                printf("%50s\n", "romance");
            }
            else if (tab.literatures_instances[tab.key_instances[i].key_index].type.artistic_type.artistic_type == 2)
            {
                printf("%50s\n", "piece");
            }
            else
            {
                printf("%50s\n", "poem");
            }
        }
        else
        {
            printf("%30s", "children");

            if (tab.literatures_instances[tab.key_instances[i].key_index].type.children_type.children_type == 1)
            {
                printf("%50s\n", "fairy tail");
            }
            else
            {
                printf("%50s\n", "poem");
            }
        }
    }
}

int table_comparator(const void *first, const void *second)
{
    return ((literature_instance *)(first)) -> number_of_pages - ((literature_instance *)(second)) -> number_of_pages;
}

int key_table_comparator(const void *first, const void *second)
{
    return ((key_struct *)(first)) -> key_value - ((key_struct *)(second)) -> key_value;
}

int qsort_table(table *tab)
{
    if (tab -> fields_count == 0)
        return EMPTY_TABLE;

    qsort(&tab -> literatures_instances[0], tab -> fields_count, sizeof(tab -> literatures_instances[0]), table_comparator);

    return SUCCESS;
}

int qsort_key_table(table *tab)
{
    if (tab -> fields_count == 0)
        return EMPTY_TABLE;

    qsort(&tab -> key_instances[0], tab -> fields_count, sizeof(tab -> key_instances[0]), key_table_comparator);

    return SUCCESS;
}

void analysis(table *tab)
{
    clock_t sum_skt = 0;
    for (int i = 0; i < 1000; ++i)
    {
        load_table(tab);
        clock_t start_sort_key_table = clock();
        sort_key_table(tab);
        clock_t end_sort_key_table = clock();
        sum_skt += end_sort_key_table - start_sort_key_table;
    }
    sum_skt = sum_skt / 1000;

    clock_t sum_qkt = 0;
    for (int i = 0; i < 1000; ++i)
    {
        load_table(tab);
        clock_t start_qsort_key_table = clock();
        qsort_key_table(tab);
        clock_t end_qsort_key_table = clock();
        sum_qkt += end_qsort_key_table - start_qsort_key_table;
    }
    sum_qkt = sum_qkt / 1000;

    clock_t sum_st = 0;
    for (int i = 0; i < 1000; ++i)
    {
        load_table(tab);
        clock_t start_sort_table = clock();
        sort_table(tab);
        clock_t end_sort_table = clock();
        sum_st += end_sort_table - start_sort_table;
    }
    sum_st = sum_st / 1000;

    clock_t sum_qt = 0;
    for (int i = 0; i < 1000; ++i)
    {
        load_table(tab);
        clock_t start_qsort_table = clock();
        qsort_table(tab);
        clock_t end_qsort_table = clock();
        sum_qt += end_qsort_table - start_qsort_table;
    }
    sum_qt  = sum_qt / 1000;

    printf("\n%30s", "Memory in bytes key table");
    printf("%30s", "Time key table (mc_s)");
    printf("%30s", "Memory in bytes table");
    printf("%30s\n\n", "Time table (mc_s)");

    printf("    Bubble%20ld%30ld%30ld%30ld\n", sizeof(tab -> key_instances[0]) * tab -> fields_count, sum_skt,
            sizeof(tab -> literatures_instances[0]) * tab -> fields_count, sum_st);

    printf("    Quick%21ld%30ld%30ld%30ld\n", sizeof(tab -> key_instances[0]) * tab -> fields_count,
            sum_qkt, sizeof(tab -> literatures_instances[0]) * tab -> fields_count,
            sum_qt);

    load_table(tab);
}

int search_domestic(table tab)
{
    if (tab.fields_count == 0)
        return EMPTY_TABLE;

    // вид сферы
    printf("\n    Введите сферу книги: ");
    char buffer_sphere[BUFFER_LENGTH + 1] = { '\0' };
    int count = 0;
    int ch;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_sphere[count] = (char)ch;

        ++count;
    }

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    if (buffer_sphere[0] == '\n' || buffer_sphere[0] == '\0' || buffer_sphere[0] == ' ')
        return EMPTY_FIELD;

    // год издания
    printf("\n    Укажите год издания книги: ");
    char buffer_year_of_publication[BUFFER_LENGTH + 1] = { '\0' };
    count = 0;

    while ((ch = getchar()) != '\n')
    {
        if (count < BUFFER_LENGTH)
            buffer_year_of_publication[count] = (char)ch;

        ++count;
    }

    if (buffer_year_of_publication[0] == '\n' || buffer_year_of_publication[0] == '\0' || buffer_year_of_publication[0] == ' ')
        return EMPTY_FIELD;

    if (count > BUFFER_LENGTH)
        return LONG_INPUT;

    for (int i = 0; i < count; ++i)
        if (isdigit(buffer_year_of_publication[i]) == 0)
            return BAD_DIGIT;

    int digit = (int)strtol(buffer_year_of_publication, NULL, 10);
    if (digit > 2022 || digit <= 0 || errno == ERANGE)
        return BAD_CONVERSION_TO_DIGIT;

    // Поиск
    size_t flag = 0;
    for (int i = 0; i < tab.fields_count; ++i)
    {
        if (tab.literatures_instances[i].int_type == 1 && strncmp(tab.literatures_instances[i].type.technical_type.sphere, buffer_sphere, BUFFER_LENGTH + 1) == 0
        && tab.literatures_instances[i].type.technical_type.domestic_or_translated == 1 && tab.literatures_instances[i].type.technical_type.year_of_publication == digit)
        {
            flag = 1;

            printf("\n%30s", tab.literatures_instances[i].author_surname);
            printf("%30s", tab.literatures_instances[i].book_title);
            printf("%30s", tab.literatures_instances[i].publisher_name);
            printf("%30d", tab.literatures_instances[i].number_of_pages);
            printf("%30s", "technical");
            printf("%30s", tab.literatures_instances[i].type.technical_type.sphere);
            printf("%30s", "domestic");
            printf("%30d\n", tab.literatures_instances[i].type.technical_type.year_of_publication);
        }
    }

    if (flag == 0)
        printf("\n    Нет таких записей (Сфера, Отечественная, год издания)\n");

    return SUCCESS;
}