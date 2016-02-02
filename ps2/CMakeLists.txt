cmake_minimum_required(VERSION 2.8)
project(cs6230_omp)

set(SOURCE "src")
set(INC "include")
set(BIN "bin")
set(TEST "test")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${BIN})

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
  message("OPENMP FOUND")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -O4")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -fopenmp -O4")

# add all files ...
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${INC})
add_library(qsort ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}/qsort.c)
add_library(util ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE}/util.c)
add_executable(test_qsort ${CMAKE_CURRENT_SOURCE_DIR}/${TEST}/qsort_test.c)
target_link_libraries(test_qsort qsort util)
