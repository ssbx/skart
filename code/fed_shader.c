#include "fed_shader.h"
#include "fed_utils.h"
#include "fed_log.h"

#include <stdio.h>
#include <stdlib.h>

GLuint FShader_load(
    const char * vertex_file_path,
    const char * fragment_file_path)
{

    FLog_debugMsg("FShader_load");

    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    char* vertex_code = FUtils_dumpFile(vertex_file_path);
    if (!vertex_code)
        return -1;

    char* fragment_code = FUtils_dumpFile(fragment_file_path);
    if (!fragment_code)
        return -1;

    FLog_debugMsg(vertex_code);
    FLog_debugMsg(fragment_code);

    GLint result = GL_FALSE;
    int   info_log_length;


    // Compiling vertex shader
    const GLchar* vertex_code_ptr = vertex_code;
    glShaderSource(VertexShaderID, 1, &vertex_code_ptr, NULL);
    glCompileShader(VertexShaderID);

    // verify
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &info_log_length);

    if (result == GL_FALSE)
        FLog_errorMsg("Error compiling vertex code");
    else
        FLog_debugMsg("Compiling vertex success");

    if (info_log_length > 0) {
        GLchar info_log[info_log_length + 1];
        glGetShaderInfoLog(VertexShaderID, info_log_length, NULL, info_log);
        FLog_infoMsg((char*) info_log);
    }

    free(vertex_code);



    // Compiling fragment shader
    const GLchar* fragment_code_ptr = fragment_code;
    glShaderSource(FragmentShaderID, 1, &fragment_code_ptr, NULL);
    glCompileShader(FragmentShaderID);

    // verify
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &info_log_length);

    if (result == GL_FALSE)
        FLog_errorMsg("Error compiling fragment code");
    else
        FLog_debugMsg("Compiling fragment success");

    if (info_log_length > 0) {
        GLchar info_log[info_log_length + 1];
        glGetShaderInfoLog(FragmentShaderID, info_log_length, NULL, info_log);
        FLog_infoMsg((char*) info_log);
    }

    free(fragment_code);


    // linking program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, VertexShaderID);
    glAttachShader(program_id, FragmentShaderID);
    glLinkProgram(program_id);

    // verify
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (result == GL_FALSE)
        FLog_errorMsg("Error linking program");
    else
        FLog_debugMsg("Linking program success");

    if (info_log_length > 0) {
        char info_log[info_log_length + 1];
        glGetProgramInfoLog(program_id, info_log_length, NULL, info_log);
        FLog_infoMsg(info_log);
    }

    glDetachShader(program_id, VertexShaderID);
    glDetachShader(program_id, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return program_id;
}
