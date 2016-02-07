#pragma once
#include "point.h"
#include "util.h"

Point run(void* arri1, void* arri2, size_t num, size_t size, int (*compar) (const void*, const void*));
Point test_Point_array(size_t num, size_t size);
Point test_int_array(size_t num, size_t size);
Point test_double_array(size_t num, size_t size);
Point test_float_array(size_t num, size_t size);
Point test_long_array(size_t num, size_t size);
