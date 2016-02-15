#
# CMakeList for project FEDERATION
# 
cmake_minimum_required (VERSION 2.8)
project (FEDERATION)


#
# external dependencies
#
add_subdirectory (deps)


#
# shared dependencies
#
find_package(OpenGL REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set (OPENGL_LIBRARY
    ${OPENGL_LIBRARY}
    -lGL -lGLU -lXrandr -lXext -lX11 -lrt
    ${CMAKE_DL_LIBS}
    ${GLFW_LIBRARIES})

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set (OPENGL_LIBRARY
    ${OPENGL_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${GLFW_LIBRARIES})

endif()


#
# "federation" executable
#
add_executable (federation
  code/main.c
  code/federation.h
  code/fed_screen.c)

target_link_libraries (federation
  ${OPENGL_LIBRARY})


#
# "make run" custom target
#
add_custom_target(run
  COMMAND federation
  DEPENDS federation
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

