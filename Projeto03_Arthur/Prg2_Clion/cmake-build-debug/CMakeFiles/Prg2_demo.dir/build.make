# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/Akray/Tools/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/Akray/Tools/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Prg2_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Prg2_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Prg2_demo.dir/flags.make

CMakeFiles/Prg2_demo.dir/main.cpp.o: CMakeFiles/Prg2_demo.dir/flags.make
CMakeFiles/Prg2_demo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Prg2_demo.dir/main.cpp.o"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Prg2_demo.dir/main.cpp.o -c "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/main.cpp"

CMakeFiles/Prg2_demo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Prg2_demo.dir/main.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/main.cpp" > CMakeFiles/Prg2_demo.dir/main.cpp.i

CMakeFiles/Prg2_demo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Prg2_demo.dir/main.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/main.cpp" -o CMakeFiles/Prg2_demo.dir/main.cpp.s

CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o: CMakeFiles/Prg2_demo.dir/flags.make
CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o: ../Projeto03.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o"
	/usr/lib64/ccache/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o -c "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/Projeto03.cpp"

CMakeFiles/Prg2_demo.dir/Projeto03.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Prg2_demo.dir/Projeto03.cpp.i"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/Projeto03.cpp" > CMakeFiles/Prg2_demo.dir/Projeto03.cpp.i

CMakeFiles/Prg2_demo.dir/Projeto03.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Prg2_demo.dir/Projeto03.cpp.s"
	/usr/lib64/ccache/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/Projeto03.cpp" -o CMakeFiles/Prg2_demo.dir/Projeto03.cpp.s

# Object files for target Prg2_demo
Prg2_demo_OBJECTS = \
"CMakeFiles/Prg2_demo.dir/main.cpp.o" \
"CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o"

# External object files for target Prg2_demo
Prg2_demo_EXTERNAL_OBJECTS =

Prg2_demo: CMakeFiles/Prg2_demo.dir/main.cpp.o
Prg2_demo: CMakeFiles/Prg2_demo.dir/Projeto03.cpp.o
Prg2_demo: CMakeFiles/Prg2_demo.dir/build.make
Prg2_demo: CMakeFiles/Prg2_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Prg2_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Prg2_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Prg2_demo.dir/build: Prg2_demo

.PHONY : CMakeFiles/Prg2_demo.dir/build

CMakeFiles/Prg2_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Prg2_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Prg2_demo.dir/clean

CMakeFiles/Prg2_demo.dir/depend:
	cd "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion" "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion" "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug" "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug" "/home/Akray/CLionProjects/Projeto 03/Prg2_Clion.tar (1)/Prg2_Clion/cmake-build-debug/CMakeFiles/Prg2_demo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Prg2_demo.dir/depend
