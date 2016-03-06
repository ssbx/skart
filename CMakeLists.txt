# -----------------------------------------------------------------------------
# CMakeList for project FEDERATION
# -----------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8)
project (FEDERATION)


if (CMAKE_SOURCE_DIR MATCHES " ")
  message (FATAL_ERROR "Your Source Directory contains spaces.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
  message (FATAL_ERROR "Your Build Directory contains spaces.")
endif()



# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

# Preprocessor definitions
add_definitions(
  -D_CRT_SECURE_NO_WARNINGS
  -DCLOG_DEBUG)

# GLAD
add_subdirectory (deps/glad)

# GLFW
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "No examples")
set (GLFW_BUILD_TESTS    OFF CACHE BOOL "No tests")
add_subdirectory (deps/glfw)

# # CGLM
add_subdirectory(deps/cglm)

# CLOG
add_subdirectory(deps/clog)

include_directories (
  deps/glad/include/
  deps/glfw/include/
  deps/clog/
  deps/cglm/
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

add_dependencies (federation glad glfw clog cglm)
target_link_libraries (federation
  glad
  glfw
  ${GLFW_LIBRARIES}
  clog
  cglm)


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

  add_custom_target (federation_doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM)

endif (DOXYGEN_FOUND)

