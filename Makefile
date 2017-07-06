# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/edoardo/Progetti/vanin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/edoardo/Progetti/vanin

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/usr/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test

.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/edoardo/Progetti/vanin/CMakeFiles /home/edoardo/Progetti/vanin/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/edoardo/Progetti/vanin/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named channel_lib

# Build rule for target.
channel_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 channel_lib
.PHONY : channel_lib

# fast build rule for target.
channel_lib/fast:
	$(MAKE) -f src/CMakeFiles/channel_lib.dir/build.make src/CMakeFiles/channel_lib.dir/build
.PHONY : channel_lib/fast

#=============================================================================
# Target rules for targets named user_lib

# Build rule for target.
user_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 user_lib
.PHONY : user_lib

# fast build rule for target.
user_lib/fast:
	$(MAKE) -f src/CMakeFiles/user_lib.dir/build.make src/CMakeFiles/user_lib.dir/build
.PHONY : user_lib/fast

#=============================================================================
# Target rules for targets named utils_lib

# Build rule for target.
utils_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 utils_lib
.PHONY : utils_lib

# fast build rule for target.
utils_lib/fast:
	$(MAKE) -f src/CMakeFiles/utils_lib.dir/build.make src/CMakeFiles/utils_lib.dir/build
.PHONY : utils_lib/fast

#=============================================================================
# Target rules for targets named user_thread_lib

# Build rule for target.
user_thread_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 user_thread_lib
.PHONY : user_thread_lib

# fast build rule for target.
user_thread_lib/fast:
	$(MAKE) -f src/CMakeFiles/user_thread_lib.dir/build.make src/CMakeFiles/user_thread_lib.dir/build
.PHONY : user_thread_lib/fast

#=============================================================================
# Target rules for targets named irc_server

# Build rule for target.
irc_server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 irc_server
.PHONY : irc_server

# fast build rule for target.
irc_server/fast:
	$(MAKE) -f src/CMakeFiles/irc_server.dir/build.make src/CMakeFiles/irc_server.dir/build
.PHONY : irc_server/fast

#=============================================================================
# Target rules for targets named check_user

# Build rule for target.
check_user: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 check_user
.PHONY : check_user

# fast build rule for target.
check_user/fast:
	$(MAKE) -f tests/CMakeFiles/check_user.dir/build.make tests/CMakeFiles/check_user.dir/build
.PHONY : check_user/fast

#=============================================================================
# Target rules for targets named check_channel

# Build rule for target.
check_channel: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 check_channel
.PHONY : check_channel

# fast build rule for target.
check_channel/fast:
	$(MAKE) -f tests/CMakeFiles/check_channel.dir/build.make tests/CMakeFiles/check_channel.dir/build
.PHONY : check_channel/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... edit_cache"
	@echo "... channel_lib"
	@echo "... user_lib"
	@echo "... utils_lib"
	@echo "... user_thread_lib"
	@echo "... irc_server"
	@echo "... check_user"
	@echo "... check_channel"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
