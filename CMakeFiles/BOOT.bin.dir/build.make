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

# Utility rule file for BOOT.bin.

# Include the progress variables for this target.
include CMakeFiles/BOOT.bin.dir/progress.make

BOOT.bin: CMakeFiles/BOOT.bin.dir/build.make
	echo '\033[0;31mYou cannot create an SD card boot file. cmake was not run with -DSDCARD=1\033[0m';exit 1;
.PHONY : BOOT.bin

# Rule to build all files generated by this target.
CMakeFiles/BOOT.bin.dir/build: BOOT.bin

.PHONY : CMakeFiles/BOOT.bin.dir/build

CMakeFiles/BOOT.bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BOOT.bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BOOT.bin.dir/clean

CMakeFiles/BOOT.bin.dir/depend:
	cd /fsd/leicr/ecen330/build_emu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fsd/leicr/ecen330 /fsd/leicr/ecen330 /fsd/leicr/ecen330/build_emu /fsd/leicr/ecen330/build_emu /fsd/leicr/ecen330/build_emu/CMakeFiles/BOOT.bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BOOT.bin.dir/depend

