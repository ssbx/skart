# GLFW
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "No examples")
set (GLFW_BUILD_TESTS    OFF CACHE BOOL "No tests")
add_subdirectory (glfw)
include_directories (
  glfw/include/
  glew/include/)

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

endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")


# GLEW
add_library(glew STATIC glew/src/glew.c)
target_link_libraries(glew ${OPENGL_LIBRARY})


# CGLM
add_subdirectory(cglm)


# CLOG
add_subdirectory(clog)


# shake
add_subdirectory(libshake)
