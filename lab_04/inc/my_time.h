#ifndef __MY_TIME_H__
#define __MY_TIME_H__

#include <stdint.h>

void print_time(int64_t start1, int64_t end1, int64_t start2, int64_t end2);

void create_rand_nums(int *arr, int count);

void time_add(int count);

void time_del(int count);

void time_process(int count);

void time_counting(void);

uint64_t tick(void);

#endif