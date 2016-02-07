#pragma once
#include "stddef.h"

#include "point.h"

void qsort_time(int size);
void basic_qsort_time(int size, int increment, int times);
void scale_qsort_time(int size, int procs);
Point time_qsort_array(void* arri_1, size_t num, size_t size, int(*compar) (const void*, const void*));
