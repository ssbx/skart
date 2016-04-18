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
  code/client/
  code/server/
  deps/glfw/include/
  deps/glew/include/
  deps/cglm/
  deps/clog/
  deps/libshake/
  deps/cargo/
  deps/libobj/
  deps/soil/code/)


#
# "federation" executable
#
add_executable (federation
  code/client/main.c
  code/client/f_common.h
  code/client/f_gl.h
  code/client/f_input.h
  code/client/f_shader.h)


add_dependencies (federation glfw glew shake obj soil)
target_link_libraries (federation
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw glew shake obj soil)


#
# "federation" executable simple test
#
enable_testing()
add_test (NAME federation_init_cleanup COMMAND federation --testing)


#
# "fsrv" executable
#
add_executable (fsrv code/server/fsrv.c)


#
# copy data to build dir target
#
add_custom_target (update_data)

file (GLOB shaders ${CMAKE_SOURCE_DIR}/material/shaders/*.glsl)
foreach(shader ${shaders})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${shader}
        ${CMAKE_CURRENT_BINARY_DIR}
  )
endforeach()

file (GLOB sounds ${CMAKE_SOURCE_DIR}/material/sounds/*.wav)
foreach(sound ${sounds})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${sound}
        ${CMAKE_CURRENT_BINARY_DIR}
  )
endforeach()

file (GLOB textures ${CMAKE_SOURCE_DIR}/material/textures/*.tga)
foreach(texture ${textures})
  add_custom_command(TARGET update_data PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${texture}
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

