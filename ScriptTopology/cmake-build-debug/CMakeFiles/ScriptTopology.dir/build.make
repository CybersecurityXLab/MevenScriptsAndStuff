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
CMAKE_COMMAND = /root/Documents/clion-2018.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /root/Documents/clion-2018.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ScriptTopology.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ScriptTopology.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ScriptTopology.dir/flags.make

CMakeFiles/ScriptTopology.dir/main.c.o: CMakeFiles/ScriptTopology.dir/flags.make
CMakeFiles/ScriptTopology.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ScriptTopology.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ScriptTopology.dir/main.c.o   -c /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/main.c

CMakeFiles/ScriptTopology.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ScriptTopology.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/main.c > CMakeFiles/ScriptTopology.dir/main.c.i

CMakeFiles/ScriptTopology.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ScriptTopology.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/main.c -o CMakeFiles/ScriptTopology.dir/main.c.s

CMakeFiles/ScriptTopology.dir/main.c.o.requires:

.PHONY : CMakeFiles/ScriptTopology.dir/main.c.o.requires

CMakeFiles/ScriptTopology.dir/main.c.o.provides: CMakeFiles/ScriptTopology.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/ScriptTopology.dir/build.make CMakeFiles/ScriptTopology.dir/main.c.o.provides.build
.PHONY : CMakeFiles/ScriptTopology.dir/main.c.o.provides

CMakeFiles/ScriptTopology.dir/main.c.o.provides.build: CMakeFiles/ScriptTopology.dir/main.c.o


# Object files for target ScriptTopology
ScriptTopology_OBJECTS = \
"CMakeFiles/ScriptTopology.dir/main.c.o"

# External object files for target ScriptTopology
ScriptTopology_EXTERNAL_OBJECTS =

ScriptTopology: CMakeFiles/ScriptTopology.dir/main.c.o
ScriptTopology: CMakeFiles/ScriptTopology.dir/build.make
ScriptTopology: CMakeFiles/ScriptTopology.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ScriptTopology"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ScriptTopology.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ScriptTopology.dir/build: ScriptTopology

.PHONY : CMakeFiles/ScriptTopology.dir/build

CMakeFiles/ScriptTopology.dir/requires: CMakeFiles/ScriptTopology.dir/main.c.o.requires

.PHONY : CMakeFiles/ScriptTopology.dir/requires

CMakeFiles/ScriptTopology.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ScriptTopology.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ScriptTopology.dir/clean

CMakeFiles/ScriptTopology.dir/depend:
	cd /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug /root/Documents/GitHub/MevenScriptsAndStuff/ScriptTopology/cmake-build-debug/CMakeFiles/ScriptTopology.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ScriptTopology.dir/depend

