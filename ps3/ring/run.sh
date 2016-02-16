#!/bin/bash

mpicc ring.c -o ring
mpirun -np $1 ./ring -n $2 
