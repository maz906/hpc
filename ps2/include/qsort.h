#pragma once
#include "stddef.h"
#include "stdbool.h"


void my_qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
void* genericScan(void *X, size_t n, size_t l, void* (*oper)(void *x1, void *x2));
void select_lower(void* base, size_t num, size_t size, void* pivot, int* swappable, int (*compar)(const void*, const void*));

void* slowScan(void* base, int left, int right, size_t size, void* (*oper)(void *x1, void *x2));
