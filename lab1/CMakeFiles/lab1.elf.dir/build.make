# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/lib/python3.6/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python3.6/dist-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /fsd/leicr/ecen330

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /fsd/leicr/ecen330/build_emu

# Include any dependencies generated for this target.
include lab1/CMakeFiles/lab1.elf.dir/depend.make

# Include the progress variables for this target.
include lab1/CMakeFiles/lab1.elf.dir/progress.make

# Include the compile flags for this target's objects.
include lab1/CMakeFiles/lab1.elf.dir/flags.make

lab1/CMakeFiles/lab1.elf.dir/main.c.o: lab1/CMakeFiles/lab1.elf.dir/flags.make
lab1/CMakeFiles/lab1.elf.dir/main.c.o: ../lab1/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/fsd/leicr/ecen330/build_emu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lab1/CMakeFiles/lab1.elf.dir/main.c.o"
	cd /fsd/leicr/ecen330/build_emu/lab1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab1.elf.dir/main.c.o -c /fsd/leicr/ecen330/lab1/main.c

lab1/CMakeFiles/lab1.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab1.elf.dir/main.c.i"
	cd /fsd/leicr/ecen330/build_emu/lab1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /fsd/leicr/ecen330/lab1/main.c > CMakeFiles/lab1.elf.dir/main.c.i

lab1/CMakeFiles/lab1.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab1.elf.dir/main.c.s"
	cd /fsd/leicr/ecen330/build_emu/lab1 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /fsd/leicr/ecen330/lab1/main.c -o CMakeFiles/lab1.elf.dir/main.c.s

# Object files for target lab1.elf
lab1_elf_OBJECTS = \
"CMakeFiles/lab1.elf.dir/main.c.o"

# External object files for target lab1.elf
lab1_elf_EXTERNAL_OBJECTS =

lab1/lab1.elf: lab1/CMakeFiles/lab1.elf.dir/main.c.o
lab1/lab1.elf: lab1/CMakeFiles/lab1.elf.dir/build.make
lab1/lab1.elf: lab1/CMakeFiles/lab1.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/fsd/leicr/ecen330/build_emu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab1.elf"
	cd /fsd/leicr/ecen330/build_emu/lab1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab1.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lab1/CMakeFiles/lab1.elf.dir/build: lab1/lab1.elf

.PHONY : lab1/CMakeFiles/lab1.elf.dir/build

lab1/CMakeFiles/lab1.elf.dir/clean:
	cd /fsd/leicr/ecen330/build_emu/lab1 && $(CMAKE_COMMAND) -P CMakeFiles/lab1.elf.dir/cmake_clean.cmake
.PHONY : lab1/CMakeFiles/lab1.elf.dir/clean

lab1/CMakeFiles/lab1.elf.dir/depend:
	cd /fsd/leicr/ecen330/build_emu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fsd/leicr/ecen330 /fsd/leicr/ecen330/lab1 /fsd/leicr/ecen330/build_emu /fsd/leicr/ecen330/build_emu/lab1 /fsd/leicr/ecen330/build_emu/lab1/CMakeFiles/lab1.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lab1/CMakeFiles/lab1.elf.dir/depend
