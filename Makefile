# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/igor/Downloads/VNS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/igor/Downloads/VNS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/igor/Downloads/VNS/CMakeFiles /home/igor/Downloads/VNS/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/igor/Downloads/VNS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pcentri_vns

# Build rule for target.
pcentri_vns: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pcentri_vns
.PHONY : pcentri_vns

# fast build rule for target.
pcentri_vns/fast:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/build
.PHONY : pcentri_vns/fast

algorithm.o: algorithm.cpp.o

.PHONY : algorithm.o

# target to build an object file
algorithm.cpp.o:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/algorithm.cpp.o
.PHONY : algorithm.cpp.o

algorithm.i: algorithm.cpp.i

.PHONY : algorithm.i

# target to preprocess a source file
algorithm.cpp.i:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/algorithm.cpp.i
.PHONY : algorithm.cpp.i

algorithm.s: algorithm.cpp.s

.PHONY : algorithm.s

# target to generate assembly for a file
algorithm.cpp.s:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/algorithm.cpp.s
.PHONY : algorithm.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/main.cpp.s
.PHONY : main.cpp.s

structures.o: structures.cpp.o

.PHONY : structures.o

# target to build an object file
structures.cpp.o:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/structures.cpp.o
.PHONY : structures.cpp.o

structures.i: structures.cpp.i

.PHONY : structures.i

# target to preprocess a source file
structures.cpp.i:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/structures.cpp.i
.PHONY : structures.cpp.i

structures.s: structures.cpp.s

.PHONY : structures.s

# target to generate assembly for a file
structures.cpp.s:
	$(MAKE) -f CMakeFiles/pcentri_vns.dir/build.make CMakeFiles/pcentri_vns.dir/structures.cpp.s
.PHONY : structures.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... pcentri_vns"
	@echo "... algorithm.o"
	@echo "... algorithm.i"
	@echo "... algorithm.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... structures.o"
	@echo "... structures.i"
	@echo "... structures.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
