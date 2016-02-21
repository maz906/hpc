#pragma once
#include "stddef.h"
#include "stdbool.h"


void my_qsort (void* base, int num, int size, int (*compar)(const void*,const void*));
void partition(void* base, int num, int size, void* pivot, int* swappable, int (*compar)(const void*, const void*));
void partition_inplace(void* base, size_t num, size_t size, void* pivot, int* swappable, int(*compar)(const void*, const void*));
void partition_seq(void* base, int num, int size, void* pivot, int* swappable, int(*compar)(const void*, const void*));
void partition_inplace2(void* base, size_t num, size_t size, void* pivot, int* swappable, int(*compar)(const void*, const void*));
