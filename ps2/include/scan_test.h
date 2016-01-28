#pragma once
#include "stddef.h"

void scan_test(int size);
void basic_scan_test(int size);

void* slowScan(void *X, size_t n, size_t l, void* (*oper)(void *x1, void *x2));