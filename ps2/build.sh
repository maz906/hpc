#!/bin/bash

export OMP_NUM_THREADS=24
cd cmake
cmake ..
make all
cd ..
