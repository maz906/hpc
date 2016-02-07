#pragma once
#include "stddef.h"
void slowScan(void* base, int num, int size, void* (*oper)(void *x1, void *x2));
void genericScan(void *X, int num, int size, void* (*oper)(void *x1, void *x2));
