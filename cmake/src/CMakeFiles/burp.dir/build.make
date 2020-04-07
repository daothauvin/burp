# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/dao/git/burp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dao/git/burp/cmake

# Include any dependencies generated for this target.
include src/CMakeFiles/burp.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/burp.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/burp.dir/flags.make

src/CMakeFiles/burp.dir/main.c.o: src/CMakeFiles/burp.dir/flags.make
src/CMakeFiles/burp.dir/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dao/git/burp/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/burp.dir/main.c.o"
	cd /home/dao/git/burp/cmake/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/burp.dir/main.c.o   -c /home/dao/git/burp/src/main.c

src/CMakeFiles/burp.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/burp.dir/main.c.i"
	cd /home/dao/git/burp/cmake/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dao/git/burp/src/main.c > CMakeFiles/burp.dir/main.c.i

src/CMakeFiles/burp.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/burp.dir/main.c.s"
	cd /home/dao/git/burp/cmake/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dao/git/burp/src/main.c -o CMakeFiles/burp.dir/main.c.s

src/CMakeFiles/burp.dir/main.c.o.requires:

.PHONY : src/CMakeFiles/burp.dir/main.c.o.requires

src/CMakeFiles/burp.dir/main.c.o.provides: src/CMakeFiles/burp.dir/main.c.o.requires
	$(MAKE) -f src/CMakeFiles/burp.dir/build.make src/CMakeFiles/burp.dir/main.c.o.provides.build
.PHONY : src/CMakeFiles/burp.dir/main.c.o.provides

src/CMakeFiles/burp.dir/main.c.o.provides.build: src/CMakeFiles/burp.dir/main.c.o


# Object files for target burp
burp_OBJECTS = \
"CMakeFiles/burp.dir/main.c.o"

# External object files for target burp
burp_EXTERNAL_OBJECTS =

src/burp: src/CMakeFiles/burp.dir/main.c.o
src/burp: src/CMakeFiles/burp.dir/build.make
src/burp: src/model/libmodel.a
src/burp: src/view/libview.a
src/burp: src/model/file_reader/libfile_reader.a
src/burp: src/model/game/libgame.a
src/burp: /usr/lib/x86_64-linux-gnu/libcurses.so
src/burp: /usr/lib/x86_64-linux-gnu/libform.so
src/burp: src/CMakeFiles/burp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dao/git/burp/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable burp"
	cd /home/dao/git/burp/cmake/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/burp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/burp.dir/build: src/burp

.PHONY : src/CMakeFiles/burp.dir/build

src/CMakeFiles/burp.dir/requires: src/CMakeFiles/burp.dir/main.c.o.requires

.PHONY : src/CMakeFiles/burp.dir/requires

src/CMakeFiles/burp.dir/clean:
	cd /home/dao/git/burp/cmake/src && $(CMAKE_COMMAND) -P CMakeFiles/burp.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/burp.dir/clean

src/CMakeFiles/burp.dir/depend:
	cd /home/dao/git/burp/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dao/git/burp /home/dao/git/burp/src /home/dao/git/burp/cmake /home/dao/git/burp/cmake/src /home/dao/git/burp/cmake/src/CMakeFiles/burp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/burp.dir/depend

