# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/karthik/dev/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/karthik/dev/Server/build

# Include any dependencies generated for this target.
include CMakeFiles/ServerTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ServerTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ServerTest.dir/flags.make

CMakeFiles/ServerTest.dir/test/serverTest.cpp.o: CMakeFiles/ServerTest.dir/flags.make
CMakeFiles/ServerTest.dir/test/serverTest.cpp.o: ../test/serverTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/karthik/dev/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ServerTest.dir/test/serverTest.cpp.o"
	/usr/bin/g++-5   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ServerTest.dir/test/serverTest.cpp.o -c /home/karthik/dev/Server/test/serverTest.cpp

CMakeFiles/ServerTest.dir/test/serverTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ServerTest.dir/test/serverTest.cpp.i"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/karthik/dev/Server/test/serverTest.cpp > CMakeFiles/ServerTest.dir/test/serverTest.cpp.i

CMakeFiles/ServerTest.dir/test/serverTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ServerTest.dir/test/serverTest.cpp.s"
	/usr/bin/g++-5  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/karthik/dev/Server/test/serverTest.cpp -o CMakeFiles/ServerTest.dir/test/serverTest.cpp.s

CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.requires:

.PHONY : CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.requires

CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.provides: CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/ServerTest.dir/build.make CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.provides.build
.PHONY : CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.provides

CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.provides.build: CMakeFiles/ServerTest.dir/test/serverTest.cpp.o


# Object files for target ServerTest
ServerTest_OBJECTS = \
"CMakeFiles/ServerTest.dir/test/serverTest.cpp.o"

# External object files for target ServerTest
ServerTest_EXTERNAL_OBJECTS =

../bin/ServerTest: CMakeFiles/ServerTest.dir/test/serverTest.cpp.o
../bin/ServerTest: CMakeFiles/ServerTest.dir/build.make
../bin/ServerTest: ../lib/libPathPlanner.so
../bin/ServerTest: /home/karthik/Downloads/boost_1_73_0/stage/lib/libboost_serialization.so
../bin/ServerTest: CMakeFiles/ServerTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/karthik/dev/Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/ServerTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ServerTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ServerTest.dir/build: ../bin/ServerTest

.PHONY : CMakeFiles/ServerTest.dir/build

CMakeFiles/ServerTest.dir/requires: CMakeFiles/ServerTest.dir/test/serverTest.cpp.o.requires

.PHONY : CMakeFiles/ServerTest.dir/requires

CMakeFiles/ServerTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ServerTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ServerTest.dir/clean

CMakeFiles/ServerTest.dir/depend:
	cd /home/karthik/dev/Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/karthik/dev/Server /home/karthik/dev/Server /home/karthik/dev/Server/build /home/karthik/dev/Server/build /home/karthik/dev/Server/build/CMakeFiles/ServerTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ServerTest.dir/depend

