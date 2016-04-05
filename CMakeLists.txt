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
  deps/libshake/
  deps/cargo/
  deps/libobj/
  .)


#
# "federation" executable
#
add_executable (federation
  main.c
  fedCommon.h
  fedGl.c
  fedGl.h
  fedInput.c
  fedInput.h
  fedShader.c
  fedShader.h)

add_dependencies (federation glfw glew clog cglm shake cargo obj)
target_link_libraries (federation
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} clog cglm glfw glew shake cargo obj)


#
# "federation" executable simple test
#
enable_testing()
add_test (NAME federation_init_cleanup COMMAND federation --testing)


#
# copy data to build dir target
#
add_custom_target (update_data)

file (GLOB shaders ${CMAKE_SOURCE_DIR}/*.glsl)
foreach(shader ${shaders})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${shader}
        ${CMAKE_CURRENT_BINARY_DIR}
  )
endforeach()

file (GLOB sounds ${CMAKE_SOURCE_DIR}/*.wav)
foreach(sound ${sounds})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${sound}
        ${CMAKE_CURRENT_BINARY_DIR}
  )
endforeach()

add_dependencies(federation update_data)


#
# "make run" custom target
#
add_custom_target (run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

