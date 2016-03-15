#
# CMakeList for project FEDERATION
#
cmake_minimum_required (VERSION 2.8)
project (FEDERATION)


#
# preprocessor definitions
#
add_definitions(
  -D_CRT_SECURE_NO_WARNINGS
  -DGLEW_STATIC
  -DCLOG_DEBUG)


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
  deps/cglm/
  deps/clog/
  deps/sndo/
  code/)


#
# "federation" executable
#
add_executable (federation
  code/federation.c
  code/federation.h
  code/fed_gl.c
  code/fed_gl.h
  code/fed_input.c
  code/fed_input.h
  code/fed_shader.c
  code/fed_shader.h)

add_dependencies (federation glfw glew clog cglm sndo)
target_link_libraries (federation
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} clog cglm glfw glew sndo)


#
# "federation" executable simple test
#
enable_testing()
add_test (NAME federation_init_cleanup COMMAND federation basic_test)


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

