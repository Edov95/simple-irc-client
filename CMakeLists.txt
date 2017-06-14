cmake_minimum_required(VERSION 3.4)

project(irc_server_proj VERSION 1.0 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)

################################################################################
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

################################################################################
subdirectory(src)

################################################################################
