#include "fed_shader.h"

#include <clog.h>
#include <stdio.h>
#include <stdlib.h>

GLuint fedLoadShaders(
    const char * vertex_file_path,
    const char * fragment_file_path)
{

    clogDebugMsg("FShader_load");

    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


    // read vertex file
    char* vertex_code = fedDumpFile(vertex_file_path);
    if (!vertex_code)
        return -1;


    // read fragment file
    char* fragment_code = fedDumpFile(fragment_file_path);
    if (!fragment_code)
        return -1;


    clogDebugMsg(vertex_code);
    clogDebugMsg(fragment_code);

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
        clogErrorMsg("Error compiling vertex code");
    else
        clogDebugMsg("Compiling vertex success");

    if (info_log_length > 0) {
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetShaderInfoLog(VertexShaderID, info_log_length, NULL, info_log);
        clogInfoMsg((char*) info_log);
        free(info_log);
    }




    // Compiling fragment shader
    const GLchar* fragment_code_ptr = fragment_code;
    glShaderSource(FragmentShaderID, 1, &fragment_code_ptr, NULL);
    glCompileShader(FragmentShaderID);

    // verify
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &info_log_length);

    if (result == GL_FALSE)
        clogErrorMsg("Error compiling fragment code");
    else
        clogDebugMsg("Compiling fragment success");

    if (info_log_length > 0) {
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetShaderInfoLog(FragmentShaderID, info_log_length, NULL, info_log);
        clogInfoMsg((char*) info_log);
        free(info_log);
    }



    // linking program
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, VertexShaderID);
    glAttachShader(program_id, FragmentShaderID);
    glLinkProgram(program_id);

    // verify
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (result == GL_FALSE)
        clogErrorMsg("Error linking program");
    else
        clogDebugMsg("Linking program success");

    if (info_log_length > 0) {
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetProgramInfoLog(program_id, info_log_length, NULL, info_log);
        clogInfoMsg(info_log);
        free(info_log);
    }

    glDetachShader(program_id, VertexShaderID);
    glDetachShader(program_id, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    free(vertex_code);
    free(fragment_code);

    return program_id;
}

char* fedDumpFile(const char* file_path)
{
    char* file_content;
    FILE* file_ptr = NULL;
    long int file_size;

    file_ptr = fopen(file_path, "rb");

    if (!file_ptr) {
        clogErrorMsg("File not found!");
        return NULL;
    }

    fseek(file_ptr, 0, SEEK_END);
    file_size = ftell(file_ptr);
    rewind(file_ptr);

    file_content = malloc((file_size + 1) * (sizeof(char)));

    fread(file_content, sizeof(char), file_size, file_ptr);
    file_content[file_size] = '\0';

    fclose(file_ptr);

    return file_content;
}
