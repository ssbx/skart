#ifndef FED_SHADER_H
#define FED_SHADER_H

#include "GL/glew.h"

GLuint FLoadShader(
    const char * vertex_file_path,
    const char * fragment_file_path);

#endif
