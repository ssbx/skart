#
# CMakeList for project FEDERATION
#
cmake_minimum_required (VERSION 2.8)
project (FEDERATION)


if (CMAKE_SOURCE_DIR MATCHES " ")
  message (FATAL_ERROR "Your Source Directory contains spaces.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
  message (FATAL_ERROR "Your Build Directory contains spaces.")
endif()


#
# preprocessor definitions
#
add_definitions(
  -D_CRT_SECURE_NO_WARNINGS)


#
# shared dependencies
#
find_package(OpenGL REQUIRED)


#
# dependencies build
#
add_subdirectory (deps)
include_directories (
  deps/glfw/include/
  deps/glm/)


#
# "federation" executable
#
add_executable (federation
  code/main.c
  code/federation.h
  code/fed_screen.c)

add_dependencies (federation glfw)

target_link_libraries (federation ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw)


#
# "make run" custom target
#
add_custom_target(run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

