#pragma once

void* bsearch(const void* key, const void* base, size_t num, size_t size, int (*compar)(const void*, const void*));
