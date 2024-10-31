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
CMAKE_SOURCE_DIR = /home/kyanh/Desktop/packet_sniffing_project/packet_learning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build

# Include any dependencies generated for this target.
include src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/flags.make

src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o: src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/flags.make
src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o: ../src/network/packet/get_packet/get_packet.cpp
src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o: src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o"
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o -MF CMakeFiles/get_packet_lib.dir/get_packet.cpp.o.d -o CMakeFiles/get_packet_lib.dir/get_packet.cpp.o -c /home/kyanh/Desktop/packet_sniffing_project/packet_learning/src/network/packet/get_packet/get_packet.cpp

src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/get_packet_lib.dir/get_packet.cpp.i"
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kyanh/Desktop/packet_sniffing_project/packet_learning/src/network/packet/get_packet/get_packet.cpp > CMakeFiles/get_packet_lib.dir/get_packet.cpp.i

src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/get_packet_lib.dir/get_packet.cpp.s"
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kyanh/Desktop/packet_sniffing_project/packet_learning/src/network/packet/get_packet/get_packet.cpp -o CMakeFiles/get_packet_lib.dir/get_packet.cpp.s

# Object files for target get_packet_lib
get_packet_lib_OBJECTS = \
"CMakeFiles/get_packet_lib.dir/get_packet.cpp.o"

# External object files for target get_packet_lib
get_packet_lib_EXTERNAL_OBJECTS =

src/network/packet/get_packet/libget_packet_lib.a: src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/get_packet.cpp.o
src/network/packet/get_packet/libget_packet_lib.a: src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/build.make
src/network/packet/get_packet/libget_packet_lib.a: src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libget_packet_lib.a"
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && $(CMAKE_COMMAND) -P CMakeFiles/get_packet_lib.dir/cmake_clean_target.cmake
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/get_packet_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/build: src/network/packet/get_packet/libget_packet_lib.a
.PHONY : src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/build

src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/clean:
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet && $(CMAKE_COMMAND) -P CMakeFiles/get_packet_lib.dir/cmake_clean.cmake
.PHONY : src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/clean

src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/depend:
	cd /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kyanh/Desktop/packet_sniffing_project/packet_learning /home/kyanh/Desktop/packet_sniffing_project/packet_learning/src/network/packet/get_packet /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet /home/kyanh/Desktop/packet_sniffing_project/packet_learning/build/src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/network/packet/get_packet/CMakeFiles/get_packet_lib.dir/depend

