#ifndef FEDSHADER_H
#define FEDSHADER_H

#include <fedCommon.h>

GLuint fedShader_Load(
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
char* fedShader_DumpFile(const char* file_path);

#endif
