#pragma once
#include "stddef.h"
#include "stdbool.h"


void my_qsort (void* base, int num, int size, int (*compar)(const void*,const void*));
void* genericScan(void *X, int n, int l, void* (*oper)(void *x1, void *x2));
void partition(void* base, size_t num, size_t size, void* pivot, int* swappable, int (*compar)(const void*, const void*));

