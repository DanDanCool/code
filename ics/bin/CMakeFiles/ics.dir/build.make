# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dandancool/dev/code/ics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dandancool/dev/code/ics/bin

# Include any dependencies generated for this target.
include CMakeFiles/ics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ics.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ics.dir/flags.make

CMakeFiles/ics.dir/src/main.cpp.o: CMakeFiles/ics.dir/flags.make
CMakeFiles/ics.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/ics.dir/src/main.cpp.o: CMakeFiles/ics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dandancool/dev/code/ics/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ics.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ics.dir/src/main.cpp.o -MF CMakeFiles/ics.dir/src/main.cpp.o.d -o CMakeFiles/ics.dir/src/main.cpp.o -c /home/dandancool/dev/code/ics/src/main.cpp

CMakeFiles/ics.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ics.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dandancool/dev/code/ics/src/main.cpp > CMakeFiles/ics.dir/src/main.cpp.i

CMakeFiles/ics.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ics.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dandancool/dev/code/ics/src/main.cpp -o CMakeFiles/ics.dir/src/main.cpp.s

CMakeFiles/ics.dir/src/memarena.cpp.o: CMakeFiles/ics.dir/flags.make
CMakeFiles/ics.dir/src/memarena.cpp.o: ../src/memarena.cpp
CMakeFiles/ics.dir/src/memarena.cpp.o: CMakeFiles/ics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dandancool/dev/code/ics/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ics.dir/src/memarena.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ics.dir/src/memarena.cpp.o -MF CMakeFiles/ics.dir/src/memarena.cpp.o.d -o CMakeFiles/ics.dir/src/memarena.cpp.o -c /home/dandancool/dev/code/ics/src/memarena.cpp

CMakeFiles/ics.dir/src/memarena.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ics.dir/src/memarena.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dandancool/dev/code/ics/src/memarena.cpp > CMakeFiles/ics.dir/src/memarena.cpp.i

CMakeFiles/ics.dir/src/memarena.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ics.dir/src/memarena.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dandancool/dev/code/ics/src/memarena.cpp -o CMakeFiles/ics.dir/src/memarena.cpp.s

# Object files for target ics
ics_OBJECTS = \
"CMakeFiles/ics.dir/src/main.cpp.o" \
"CMakeFiles/ics.dir/src/memarena.cpp.o"

# External object files for target ics
ics_EXTERNAL_OBJECTS =

ics: CMakeFiles/ics.dir/src/main.cpp.o
ics: CMakeFiles/ics.dir/src/memarena.cpp.o
ics: CMakeFiles/ics.dir/build.make
ics: CMakeFiles/ics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dandancool/dev/code/ics/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ics"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ics.dir/build: ics
.PHONY : CMakeFiles/ics.dir/build

CMakeFiles/ics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ics.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ics.dir/clean

CMakeFiles/ics.dir/depend:
	cd /home/dandancool/dev/code/ics/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dandancool/dev/code/ics /home/dandancool/dev/code/ics /home/dandancool/dev/code/ics/bin /home/dandancool/dev/code/ics/bin /home/dandancool/dev/code/ics/bin/CMakeFiles/ics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ics.dir/depend

