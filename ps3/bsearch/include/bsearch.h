#pragma once

#include <stddef.h>

#include <mpi.h>

void* bsearch(const void* key, const void* base, size_t num, size_t size, int (*compar)(const void*, const void*)
								MPI_COMM_WORLD comm, size_t nkey, size_t nthreads);

void* seq_bsearch(const void* key, const void* base, size_t num, size_t size, int (*compar)(const void*, const void*);
