#ifndef FED_SHADER_H
#define FED_SHADER_H

#include "GL/glew.h"

GLuint fedLoadShaders(
    const char * vertex_file_path,
    const char * fragment_file_path);

/**
 * @struct FileDump
 * @brief File dump structure.
 * Contain the size of dump and the file dump.
 * t_FileDump.dump must be free().
 */
typedef struct FileDump {
    int   size;
    char* dump;
} FileDump;

/**
 * @fn fedDumpFile(const char* file_path)
 * @return char*
 */
char* fedDumpFile(const char* file_path);

#endif
