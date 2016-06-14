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
  .
  deps/glfw/include/
  deps/glew/include/
  deps/cglm/
  deps/clog/
  deps/libshake/
  deps/cargo/
  deps/libobj/
  deps/soil/code/)

#
# "fsrv" executable
#
add_executable (fsrv code/fSrv.c)

#
# "federation" executable
#
add_executable (federation
  code/main.c
  code/fGl.h
  code/fInput.h
  code/fSounds.h)


add_dependencies (federation glfw glew shake soil)
target_link_libraries (federation
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw glew shake soil)


#
# "federation" executable simple test
#
enable_testing()
set (CTEST_OUTPUT_ON_FAILURE ON)
add_test (NAME MemCheck  COMMAND valgrind --error-exitcode=1 --tool=memcheck --leak-check=full --track-origins=yes -v ./federation)





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

