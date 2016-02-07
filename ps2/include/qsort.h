#pragma once
#include "stddef.h"
#include "stdbool.h"


void my_qsort (void* base, int num, int size, int (*compar)(const void*,const void*));
void partition(void* base, int num, int size, void* pivot, int* swappable, int (*compar)(const void*, const void*));