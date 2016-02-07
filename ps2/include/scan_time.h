#pragma once
#include "point.h"

void scan_time(int size);
void scale_scan_time(int size, int procs);
void basic_scan_time(int size, int increment, int times);
Point time_scan_array(void* arri_1, size_t num, size_t size, void*(*oper) (const void*, const void*));
