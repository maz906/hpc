#!/bin/bash

mpicc ring.c -o ring
mpirun -np 10 ./ring -n 1
