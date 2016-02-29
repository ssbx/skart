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
  -D_CRT_SECURE_NO_WARNINGS
  -DGLEW_STATIC
  -DFEDERATION_DEBUG)


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
  deps/glew/include/
  deps/cglm/include/
  code/)


#
# "federation" executable
#
add_executable (federation
  code/federation.c
  code/federation.h
  code/ex0.c
  code/ex0.h
  code/ex1.c
  code/ex1.h
  code/fed_gl.c
  code/fed_gl.h
  code/fed_log.c
  code/fed_log.h
  code/fed_input.c
  code/fed_input.h
  code/fed_shader.c
  code/fed_shader.h)

add_dependencies (federation glfw)
add_dependencies (federation GLEW_1130)

target_link_libraries (federation
  ${OPENGL_LIBRARY}
  ${GLFW_LIBRARIES}
  cglm
  glfw
  GLEW_1130)


#
# copy data to build dir target
#
add_custom_target (create_data_dirs)
add_custom_target (update_data)

add_custom_command (TARGET create_data_dirs POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_CURRENT_BINARY_DIR}/data/shaders)

file (GLOB shaders ${CMAKE_SOURCE_DIR}/data/shaders/*)
foreach(shader ${shaders})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${shader}
        ${CMAKE_CURRENT_BINARY_DIR}/data/shaders
  )
endforeach()

add_dependencies(federation update_data)
add_dependencies(update_data create_data_dirs)


#
# "make run" custom target
#
add_custom_target (run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


#
# "make doc" custom target
#
find_package (Doxygen)

if (DOXYGEN_FOUND)

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

  add_custom_target (doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)

endif (DOXYGEN_FOUND)
