#
# CMakeList for project FEDERATION
#
cmake_minimum_required (VERSION 2.8)
project (FEDERATION)


#
# external dependencies install
#
set (FEDERATION_DEPS_INSTALL ${CMAKE_BINARY_DIR}/install)
add_subdirectory (deps)

include_directories (${FEDERATION_DEPS_INSTALL}/include/)
set (GLFW_LIBRARY glfw ${FEDERATION_DEPS_INSTALL}/lib/libglfw3.a)

#
# shared dependencies
#
find_package(OpenGL REQUIRED)
MESSAGE (${OPENGL_LIBRARY})

#
# "federation" executable
#
add_executable (federation
  code/main.c
  code/federation.h
  code/fed_screen.c)

add_dependencies (federation OpenGL)
add_dependencies (federation GLFW)

target_link_libraries (federation ${OPENGL_LIBRARY})


#
# "make run" custom target
#
add_custom_target(run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

