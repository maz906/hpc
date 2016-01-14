#include "stddef.h"
typedef struct _Point {
	double x;
	double y;
} Point;

void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));

