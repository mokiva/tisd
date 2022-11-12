#ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

// описание экземпляра технической литературы
struct technical_literature_instance
{
    char sphere[SPHERE_NAME + 1];
    int domestic_or_translated;
    int year_of_publication;
};

// описание типа художественной литературы
struct artistic_literature
{
    int artistic_type;
};

// описание типа детской литературы
struct children_literature
{
    int children_type;
};

typedef struct technical_literature_instance technical_literature_instance;
typedef struct artistic_literature artistic_literature;
typedef struct children_literature children_literature;

// описание вида литературы
union literature_type
{
    technical_literature_instance technical_type;
    artistic_literature artistic_type;
    children_literature children_type;
};

typedef union literature_type literature_type;

// описание экземпляра литературы (элемент таблицы)
struct literature_instance
{
    char author_surname[AUTHOR_SURNAME + 1];
    char book_title[BOOK_TITLE + 1];
    char publisher_name[PUBLISHER_NAME + 1];
    int number_of_pages;
    literature_type type;
};

typedef struct literature_instance literature_instance;

// описание типа ключа (значение - индекс)
struct key_struct
{
    int key_value;
    int key_index;
};

typedef struct key_struct key_struct;

// описание целой таблицы
struct table
{
    literature_instance literatures_instances[MAX_FIELDS];
    key_struct key_instances[MAX_FIELDS];
    int fields_count;
};

typedef struct table table;

#endif