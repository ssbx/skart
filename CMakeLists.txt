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
include_directories(${OPENGL_INCLUDE_DIR})


#
# dependencies build
#
add_subdirectory (deps)
include_directories (
  code/
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
  code/main.c
  code/screen.h
  code/shaders.h
  code/inputs.h
  code/sounds.h)

add_dependencies (federation glfw glew shake soil)
target_link_libraries (federation
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw glew shake soil)


#
# "federation" executable simple test
#
enable_testing()
set (CTEST_OUTPUT_ON_FAILURE ON)
add_test (
    NAME MemCheck
    COMMAND valgrind --error-exitcode=1 --tool=memcheck
                     --leak-check=full --track-origins=yes -v ./federation)


#
# "make run" custom target
#
add_custom_target (run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Execute the target...")

