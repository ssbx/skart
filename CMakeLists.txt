#
# CMakeList for project SKART
#
cmake_minimum_required (VERSION 2.8)
project (SKART)


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
  deps/soil/code/
  deps/objloader/)


#
# "skart" executable
#
add_executable (skart
  code/skart.c
  code/screen.h
  code/shaders.h
  code/inputs.h
  code/sounds.h)

add_executable (viewer
    deps/objloader/examples/viewer/trackball.c
    deps/objloader/examples/viewer/trackball.h
    deps/objloader/examples/viewer/viewer.c
    deps/objloader/objloader.h)

add_dependencies (skart glfw glew shake soil)
add_dependencies (viewer glfw glew shake soil)
target_link_libraries (skart
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw glew shake soil)

target_link_libraries (viewer
  ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} glfw glew shake soil)

#
# "skart" executable simple test
#
enable_testing()
set (CTEST_OUTPUT_ON_FAILURE ON)
add_test (
    NAME MemCheck
    COMMAND valgrind --error-exitcode=1 --tool=memcheck
                     --leak-check=full --track-origins=yes -v ./skart)


#
# "make run" custom target
#
add_custom_target (run
  COMMAND skart
  DEPENDS skart
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  COMMENT "Execute the target...")

