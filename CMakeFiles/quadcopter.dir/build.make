# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/fred/dev/quadcopter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fred/dev/quadcopter

# Include any dependencies generated for this target.
include CMakeFiles/quadcopter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/quadcopter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/quadcopter.dir/flags.make

CMakeFiles/quadcopter.dir/src/OLED.cpp.o: CMakeFiles/quadcopter.dir/flags.make
CMakeFiles/quadcopter.dir/src/OLED.cpp.o: src/OLED.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fred/dev/quadcopter/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/quadcopter.dir/src/OLED.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/quadcopter.dir/src/OLED.cpp.o -c /home/fred/dev/quadcopter/src/OLED.cpp

CMakeFiles/quadcopter.dir/src/OLED.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quadcopter.dir/src/OLED.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fred/dev/quadcopter/src/OLED.cpp > CMakeFiles/quadcopter.dir/src/OLED.cpp.i

CMakeFiles/quadcopter.dir/src/OLED.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quadcopter.dir/src/OLED.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fred/dev/quadcopter/src/OLED.cpp -o CMakeFiles/quadcopter.dir/src/OLED.cpp.s

CMakeFiles/quadcopter.dir/src/OLED.cpp.o.requires:
.PHONY : CMakeFiles/quadcopter.dir/src/OLED.cpp.o.requires

CMakeFiles/quadcopter.dir/src/OLED.cpp.o.provides: CMakeFiles/quadcopter.dir/src/OLED.cpp.o.requires
	$(MAKE) -f CMakeFiles/quadcopter.dir/build.make CMakeFiles/quadcopter.dir/src/OLED.cpp.o.provides.build
.PHONY : CMakeFiles/quadcopter.dir/src/OLED.cpp.o.provides

CMakeFiles/quadcopter.dir/src/OLED.cpp.o.provides.build: CMakeFiles/quadcopter.dir/src/OLED.cpp.o

CMakeFiles/quadcopter.dir/src/Log.cpp.o: CMakeFiles/quadcopter.dir/flags.make
CMakeFiles/quadcopter.dir/src/Log.cpp.o: src/Log.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fred/dev/quadcopter/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/quadcopter.dir/src/Log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/quadcopter.dir/src/Log.cpp.o -c /home/fred/dev/quadcopter/src/Log.cpp

CMakeFiles/quadcopter.dir/src/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quadcopter.dir/src/Log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fred/dev/quadcopter/src/Log.cpp > CMakeFiles/quadcopter.dir/src/Log.cpp.i

CMakeFiles/quadcopter.dir/src/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quadcopter.dir/src/Log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fred/dev/quadcopter/src/Log.cpp -o CMakeFiles/quadcopter.dir/src/Log.cpp.s

CMakeFiles/quadcopter.dir/src/Log.cpp.o.requires:
.PHONY : CMakeFiles/quadcopter.dir/src/Log.cpp.o.requires

CMakeFiles/quadcopter.dir/src/Log.cpp.o.provides: CMakeFiles/quadcopter.dir/src/Log.cpp.o.requires
	$(MAKE) -f CMakeFiles/quadcopter.dir/build.make CMakeFiles/quadcopter.dir/src/Log.cpp.o.provides.build
.PHONY : CMakeFiles/quadcopter.dir/src/Log.cpp.o.provides

CMakeFiles/quadcopter.dir/src/Log.cpp.o.provides.build: CMakeFiles/quadcopter.dir/src/Log.cpp.o

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o: CMakeFiles/quadcopter.dir/flags.make
CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o: src/Quadcopter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fred/dev/quadcopter/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o -c /home/fred/dev/quadcopter/src/Quadcopter.cpp

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fred/dev/quadcopter/src/Quadcopter.cpp > CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.i

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fred/dev/quadcopter/src/Quadcopter.cpp -o CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.s

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.requires:
.PHONY : CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.requires

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.provides: CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.requires
	$(MAKE) -f CMakeFiles/quadcopter.dir/build.make CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.provides.build
.PHONY : CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.provides

CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.provides.build: CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o

CMakeFiles/quadcopter.dir/src/Controller.cpp.o: CMakeFiles/quadcopter.dir/flags.make
CMakeFiles/quadcopter.dir/src/Controller.cpp.o: src/Controller.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/fred/dev/quadcopter/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/quadcopter.dir/src/Controller.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/quadcopter.dir/src/Controller.cpp.o -c /home/fred/dev/quadcopter/src/Controller.cpp

CMakeFiles/quadcopter.dir/src/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/quadcopter.dir/src/Controller.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/fred/dev/quadcopter/src/Controller.cpp > CMakeFiles/quadcopter.dir/src/Controller.cpp.i

CMakeFiles/quadcopter.dir/src/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/quadcopter.dir/src/Controller.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/fred/dev/quadcopter/src/Controller.cpp -o CMakeFiles/quadcopter.dir/src/Controller.cpp.s

CMakeFiles/quadcopter.dir/src/Controller.cpp.o.requires:
.PHONY : CMakeFiles/quadcopter.dir/src/Controller.cpp.o.requires

CMakeFiles/quadcopter.dir/src/Controller.cpp.o.provides: CMakeFiles/quadcopter.dir/src/Controller.cpp.o.requires
	$(MAKE) -f CMakeFiles/quadcopter.dir/build.make CMakeFiles/quadcopter.dir/src/Controller.cpp.o.provides.build
.PHONY : CMakeFiles/quadcopter.dir/src/Controller.cpp.o.provides

CMakeFiles/quadcopter.dir/src/Controller.cpp.o.provides.build: CMakeFiles/quadcopter.dir/src/Controller.cpp.o

# Object files for target quadcopter
quadcopter_OBJECTS = \
"CMakeFiles/quadcopter.dir/src/OLED.cpp.o" \
"CMakeFiles/quadcopter.dir/src/Log.cpp.o" \
"CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o" \
"CMakeFiles/quadcopter.dir/src/Controller.cpp.o"

# External object files for target quadcopter
quadcopter_EXTERNAL_OBJECTS =

quadcopter: CMakeFiles/quadcopter.dir/src/OLED.cpp.o
quadcopter: CMakeFiles/quadcopter.dir/src/Log.cpp.o
quadcopter: CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o
quadcopter: CMakeFiles/quadcopter.dir/src/Controller.cpp.o
quadcopter: CMakeFiles/quadcopter.dir/build.make
quadcopter: src/c_drivers/libc_drivers.so
quadcopter: CMakeFiles/quadcopter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable quadcopter"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quadcopter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/quadcopter.dir/build: quadcopter
.PHONY : CMakeFiles/quadcopter.dir/build

CMakeFiles/quadcopter.dir/requires: CMakeFiles/quadcopter.dir/src/OLED.cpp.o.requires
CMakeFiles/quadcopter.dir/requires: CMakeFiles/quadcopter.dir/src/Log.cpp.o.requires
CMakeFiles/quadcopter.dir/requires: CMakeFiles/quadcopter.dir/src/Quadcopter.cpp.o.requires
CMakeFiles/quadcopter.dir/requires: CMakeFiles/quadcopter.dir/src/Controller.cpp.o.requires
.PHONY : CMakeFiles/quadcopter.dir/requires

CMakeFiles/quadcopter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/quadcopter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/quadcopter.dir/clean

CMakeFiles/quadcopter.dir/depend:
	cd /home/fred/dev/quadcopter && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fred/dev/quadcopter /home/fred/dev/quadcopter /home/fred/dev/quadcopter /home/fred/dev/quadcopter /home/fred/dev/quadcopter/CMakeFiles/quadcopter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/quadcopter.dir/depend

