# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nazenji/Git/hpc/ps2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nazenji/Git/hpc/ps2/cmake

# Include any dependencies generated for this target.
include CMakeFiles/test_qsort.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_qsort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_qsort.dir/flags.make

CMakeFiles/test_qsort.dir/test/qsort_test.c.o: CMakeFiles/test_qsort.dir/flags.make
CMakeFiles/test_qsort.dir/test/qsort_test.c.o: ../test/qsort_test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nazenji/Git/hpc/ps2/cmake/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/test_qsort.dir/test/qsort_test.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/test_qsort.dir/test/qsort_test.c.o   -c /home/nazenji/Git/hpc/ps2/test/qsort_test.c

CMakeFiles/test_qsort.dir/test/qsort_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_qsort.dir/test/qsort_test.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/nazenji/Git/hpc/ps2/test/qsort_test.c > CMakeFiles/test_qsort.dir/test/qsort_test.c.i

CMakeFiles/test_qsort.dir/test/qsort_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_qsort.dir/test/qsort_test.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/nazenji/Git/hpc/ps2/test/qsort_test.c -o CMakeFiles/test_qsort.dir/test/qsort_test.c.s

CMakeFiles/test_qsort.dir/test/qsort_test.c.o.requires:
.PHONY : CMakeFiles/test_qsort.dir/test/qsort_test.c.o.requires

CMakeFiles/test_qsort.dir/test/qsort_test.c.o.provides: CMakeFiles/test_qsort.dir/test/qsort_test.c.o.requires
	$(MAKE) -f CMakeFiles/test_qsort.dir/build.make CMakeFiles/test_qsort.dir/test/qsort_test.c.o.provides.build
.PHONY : CMakeFiles/test_qsort.dir/test/qsort_test.c.o.provides

CMakeFiles/test_qsort.dir/test/qsort_test.c.o.provides.build: CMakeFiles/test_qsort.dir/test/qsort_test.c.o

# Object files for target test_qsort
test_qsort_OBJECTS = \
"CMakeFiles/test_qsort.dir/test/qsort_test.c.o"

# External object files for target test_qsort
test_qsort_EXTERNAL_OBJECTS =

../bin/test_qsort: CMakeFiles/test_qsort.dir/test/qsort_test.c.o
../bin/test_qsort: CMakeFiles/test_qsort.dir/build.make
../bin/test_qsort: ../bin/libqsort.a
../bin/test_qsort: CMakeFiles/test_qsort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../bin/test_qsort"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_qsort.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_qsort.dir/build: ../bin/test_qsort
.PHONY : CMakeFiles/test_qsort.dir/build

CMakeFiles/test_qsort.dir/requires: CMakeFiles/test_qsort.dir/test/qsort_test.c.o.requires
.PHONY : CMakeFiles/test_qsort.dir/requires

CMakeFiles/test_qsort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_qsort.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_qsort.dir/clean

CMakeFiles/test_qsort.dir/depend:
	cd /home/nazenji/Git/hpc/ps2/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nazenji/Git/hpc/ps2 /home/nazenji/Git/hpc/ps2 /home/nazenji/Git/hpc/ps2/cmake /home/nazenji/Git/hpc/ps2/cmake /home/nazenji/Git/hpc/ps2/cmake/CMakeFiles/test_qsort.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_qsort.dir/depend
