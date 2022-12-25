cmake_minimum_required(VERSION 3.18)
project(lab_04 C)

set(CMAKE_C_STANDARD 99)

include_directories(inc)

add_executable(lab_04
        inc/defs.h
        inc/text.h
        inc/adt.h
        inc/list.h
        inc/expr.h

        src/main.c
        src/text.c
        src/list.c
        src/expr.c)
