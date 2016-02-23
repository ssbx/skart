include (ExternalProject)

#
# GLFW external project
#
set (GLFW_CMAKE_CONF_ARGS 
  -DBUILD_SHARED_LIBS=OFF 
  -DGLFW_BUILD_EXAMPLES=OFF 
  -DGLFW_BUILD_TESTS=OFF 
  -DGLFW_BUILD_DOCS=OFF
  -DCMAKE_INSTALL_PREFIX=${FEDERATION_DEPS_INSTALL})

ExternalProject_Add (GLFW
  URL           "http://github.com/glfw/glfw/archive/3.1.2.tar.gz"
  URL_HASH      "MD5=ea3494930a90ccec00719c59ad458983"
  CMAKE_ARGS    ${GLFW_CMAKE_CONF_ARGS}
  INSTALL_DIR   ${FEDERATION_DEPS_INSTALL})

#ExternalProject_Add (glm)
#ExternalProject_Add (assimp)
#ExternalProject_Add (portaudio)

