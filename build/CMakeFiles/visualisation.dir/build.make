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
CMAKE_SOURCE_DIR = "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build"

# Include any dependencies generated for this target.
include CMakeFiles/visualisation.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/visualisation.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/visualisation.dir/flags.make

CMakeFiles/visualisation.dir/src/visualisation.cpp.o: CMakeFiles/visualisation.dir/flags.make
CMakeFiles/visualisation.dir/src/visualisation.cpp.o: ../src/visualisation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/visualisation.dir/src/visualisation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/visualisation.dir/src/visualisation.cpp.o -c "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/src/visualisation.cpp"

CMakeFiles/visualisation.dir/src/visualisation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualisation.dir/src/visualisation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/src/visualisation.cpp" > CMakeFiles/visualisation.dir/src/visualisation.cpp.i

CMakeFiles/visualisation.dir/src/visualisation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualisation.dir/src/visualisation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/src/visualisation.cpp" -o CMakeFiles/visualisation.dir/src/visualisation.cpp.s

CMakeFiles/visualisation.dir/src/visualisation.cpp.o.requires:

.PHONY : CMakeFiles/visualisation.dir/src/visualisation.cpp.o.requires

CMakeFiles/visualisation.dir/src/visualisation.cpp.o.provides: CMakeFiles/visualisation.dir/src/visualisation.cpp.o.requires
	$(MAKE) -f CMakeFiles/visualisation.dir/build.make CMakeFiles/visualisation.dir/src/visualisation.cpp.o.provides.build
.PHONY : CMakeFiles/visualisation.dir/src/visualisation.cpp.o.provides

CMakeFiles/visualisation.dir/src/visualisation.cpp.o.provides.build: CMakeFiles/visualisation.dir/src/visualisation.cpp.o


# Object files for target visualisation
visualisation_OBJECTS = \
"CMakeFiles/visualisation.dir/src/visualisation.cpp.o"

# External object files for target visualisation
visualisation_EXTERNAL_OBJECTS =

libvisualisation.a: CMakeFiles/visualisation.dir/src/visualisation.cpp.o
libvisualisation.a: CMakeFiles/visualisation.dir/build.make
libvisualisation.a: CMakeFiles/visualisation.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libvisualisation.a"
	$(CMAKE_COMMAND) -P CMakeFiles/visualisation.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/visualisation.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/visualisation.dir/build: libvisualisation.a

.PHONY : CMakeFiles/visualisation.dir/build

CMakeFiles/visualisation.dir/requires: CMakeFiles/visualisation.dir/src/visualisation.cpp.o.requires

.PHONY : CMakeFiles/visualisation.dir/requires

CMakeFiles/visualisation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/visualisation.dir/cmake_clean.cmake
.PHONY : CMakeFiles/visualisation.dir/clean

CMakeFiles/visualisation.dir/depend:
	cd "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar" "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar" "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build" "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build" "/home/lakshmi/Documents/summer projects/Max/MultiResolutionAstar/build/CMakeFiles/visualisation.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/visualisation.dir/depend
