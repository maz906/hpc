#pragma once

#include "point.h"
#include "stddef.h"

void qsort_test(int size);
//void scale_qsort_test(int procs, int size);
void rigor_qsort_test(int size);
void basic_qsort_test(int size, int increment);
void test_qsort_array(void* arri_1, size_t num, size_t size, int(*compar) (const void*, const void*));
