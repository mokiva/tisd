#ifndef STRUCTS_H
#define STRUCTS_H

#include "defines.h"

struct technical_literature_instance
{
    char sphere[SPHERE_NAME + 1];
    int domestic_or_translated;
    int year_of_publication;
};

struct artistic_literature
{
    int artistic_type;
};

struct children_literature
{
    int children_type;
};

typedef struct technical_literature_instance technical_literature_instance;
typedef struct artistic_literature artistic_literature;
typedef struct children_literature children_literature;

union literature_type
{
    technical_literature_instance technical_type;
    artistic_literature artistic_type;
    children_literature children_type;
};

typedef union literature_type literature_type;

struct literature_instance
{
    char author_surname[AUTHOR_SURNAME + 1];
    char book_title[BOOK_TITLE + 1];
    char publisher_name[PUBLISHER_NAME + 1];
    int number_of_pages;
    literature_type type;
};

typedef struct literature_instance literature_instance;

struct key_struct
{
    int key_value;
    int key_index;
};

typedef struct key_struct key_struct;

struct table
{
    literature_instance literatures_instances[MAX_FIELDS];
    key_struct key_instances[MAX_FIELDS];
    int fields_count;
};

typedef struct table table;

#endif