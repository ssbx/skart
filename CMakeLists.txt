#
# CMakeList for project MARSWAR
# 
cmake_minimum_required (VERSION 2.6)
project (FEDERATION)

# shared dependencies
find_package(OpenGL REQUIRED)

# dependencies
add_subdirectory (deps)

# marswars executable
add_executable (federation
  code/federation.c
  code/federation.h
  code/fed_screen.c)

