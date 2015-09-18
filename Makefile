# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /opt/cmake/3.3.0/bin/cmake

# The command to remove a file.
RM = /opt/cmake/3.3.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/userspace/ajs224/Dropbox/Code/pbIterativeSolver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/userspace/ajs224/Dropbox/Code/pbIterativeSolver

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/opt/cmake/3.3.0/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/cmake/3.3.0/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/cmake/3.3.0/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/userspace/ajs224/Dropbox/Code/pbIterativeSolver/CMakeFiles /home/userspace/ajs224/Dropbox/Code/pbIterativeSolver/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/userspace/ajs224/Dropbox/Code/pbIterativeSolver/CMakeFiles 0
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
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named pbIterativeSolver

# Build rule for target.
pbIterativeSolver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 pbIterativeSolver
.PHONY : pbIterativeSolver

# fast build rule for target.
pbIterativeSolver/fast:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/build
.PHONY : pbIterativeSolver/fast

source/Cell.o: source/Cell.c++.o

.PHONY : source/Cell.o

# target to build an object file
source/Cell.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Cell.c++.o
.PHONY : source/Cell.c++.o

source/Cell.i: source/Cell.c++.i

.PHONY : source/Cell.i

# target to preprocess a source file
source/Cell.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Cell.c++.i
.PHONY : source/Cell.c++.i

source/Cell.s: source/Cell.c++.s

.PHONY : source/Cell.s

# target to generate assembly for a file
source/Cell.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Cell.c++.s
.PHONY : source/Cell.c++.s

source/Particle.o: source/Particle.c++.o

.PHONY : source/Particle.o

# target to build an object file
source/Particle.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Particle.c++.o
.PHONY : source/Particle.c++.o

source/Particle.i: source/Particle.c++.i

.PHONY : source/Particle.i

# target to preprocess a source file
source/Particle.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Particle.c++.i
.PHONY : source/Particle.c++.i

source/Particle.s: source/Particle.c++.s

.PHONY : source/Particle.s

# target to generate assembly for a file
source/Particle.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Particle.c++.s
.PHONY : source/Particle.c++.s

source/Solver.o: source/Solver.c++.o

.PHONY : source/Solver.o

# target to build an object file
source/Solver.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Solver.c++.o
.PHONY : source/Solver.c++.o

source/Solver.i: source/Solver.c++.i

.PHONY : source/Solver.i

# target to preprocess a source file
source/Solver.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Solver.c++.i
.PHONY : source/Solver.c++.i

source/Solver.s: source/Solver.c++.s

.PHONY : source/Solver.s

# target to generate assembly for a file
source/Solver.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/Solver.c++.s
.PHONY : source/Solver.c++.s

source/blurb.o: source/blurb.c++.o

.PHONY : source/blurb.o

# target to build an object file
source/blurb.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/blurb.c++.o
.PHONY : source/blurb.c++.o

source/blurb.i: source/blurb.c++.i

.PHONY : source/blurb.i

# target to preprocess a source file
source/blurb.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/blurb.c++.i
.PHONY : source/blurb.c++.i

source/blurb.s: source/blurb.c++.s

.PHONY : source/blurb.s

# target to generate assembly for a file
source/blurb.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/blurb.c++.s
.PHONY : source/blurb.c++.s

source/mfa_params.o: source/mfa_params.c++.o

.PHONY : source/mfa_params.o

# target to build an object file
source/mfa_params.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/mfa_params.c++.o
.PHONY : source/mfa_params.c++.o

source/mfa_params.i: source/mfa_params.c++.i

.PHONY : source/mfa_params.i

# target to preprocess a source file
source/mfa_params.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/mfa_params.c++.i
.PHONY : source/mfa_params.c++.i

source/mfa_params.s: source/mfa_params.c++.s

.PHONY : source/mfa_params.s

# target to generate assembly for a file
source/mfa_params.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/mfa_params.c++.s
.PHONY : source/mfa_params.c++.s

source/moments.o: source/moments.c++.o

.PHONY : source/moments.o

# target to build an object file
source/moments.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/moments.c++.o
.PHONY : source/moments.c++.o

source/moments.i: source/moments.c++.i

.PHONY : source/moments.i

# target to preprocess a source file
source/moments.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/moments.c++.i
.PHONY : source/moments.c++.i

source/moments.s: source/moments.c++.s

.PHONY : source/moments.s

# target to generate assembly for a file
source/moments.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/moments.c++.s
.PHONY : source/moments.c++.s

source/n_in.o: source/n_in.c++.o

.PHONY : source/n_in.o

# target to build an object file
source/n_in.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/n_in.c++.o
.PHONY : source/n_in.c++.o

source/n_in.i: source/n_in.c++.i

.PHONY : source/n_in.i

# target to preprocess a source file
source/n_in.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/n_in.c++.i
.PHONY : source/n_in.c++.i

source/n_in.s: source/n_in.c++.s

.PHONY : source/n_in.s

# target to generate assembly for a file
source/n_in.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/n_in.c++.s
.PHONY : source/n_in.c++.s

source/pbIterativeSolver.o: source/pbIterativeSolver.c++.o

.PHONY : source/pbIterativeSolver.o

# target to build an object file
source/pbIterativeSolver.c++.o:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/pbIterativeSolver.c++.o
.PHONY : source/pbIterativeSolver.c++.o

source/pbIterativeSolver.i: source/pbIterativeSolver.c++.i

.PHONY : source/pbIterativeSolver.i

# target to preprocess a source file
source/pbIterativeSolver.c++.i:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/pbIterativeSolver.c++.i
.PHONY : source/pbIterativeSolver.c++.i

source/pbIterativeSolver.s: source/pbIterativeSolver.c++.s

.PHONY : source/pbIterativeSolver.s

# target to generate assembly for a file
source/pbIterativeSolver.c++.s:
	$(MAKE) -f CMakeFiles/pbIterativeSolver.dir/build.make CMakeFiles/pbIterativeSolver.dir/source/pbIterativeSolver.c++.s
.PHONY : source/pbIterativeSolver.c++.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... test"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... pbIterativeSolver"
	@echo "... source/Cell.o"
	@echo "... source/Cell.i"
	@echo "... source/Cell.s"
	@echo "... source/Particle.o"
	@echo "... source/Particle.i"
	@echo "... source/Particle.s"
	@echo "... source/Solver.o"
	@echo "... source/Solver.i"
	@echo "... source/Solver.s"
	@echo "... source/blurb.o"
	@echo "... source/blurb.i"
	@echo "... source/blurb.s"
	@echo "... source/mfa_params.o"
	@echo "... source/mfa_params.i"
	@echo "... source/mfa_params.s"
	@echo "... source/moments.o"
	@echo "... source/moments.i"
	@echo "... source/moments.s"
	@echo "... source/n_in.o"
	@echo "... source/n_in.i"
	@echo "... source/n_in.s"
	@echo "... source/pbIterativeSolver.o"
	@echo "... source/pbIterativeSolver.i"
	@echo "... source/pbIterativeSolver.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

