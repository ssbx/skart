#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <clog.h>

typedef struct FileDump {
    int   size;
    char* dump;
} FileDump;

char* dump_shader_file(const char* file_path)
{
    char* file_content;
    FILE* file_ptr = NULL;
    long int file_size;

    file_ptr = fopen(file_path, "rb");

    if (!file_ptr) {
        clogError("File not found!", NULL);
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


/**
 * @brief Load shader
 */
GLuint load_shader(
    const char * vertex_file_path,
    const char * fragment_file_path)
{


    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


    // read vertex file
    char* vertex_code = dump_shader_file(vertex_file_path);
    if (!vertex_code)
        return -1;


    // read fragment file
    char* fragment_code = dump_shader_file(fragment_file_path);
    if (!fragment_code)
        return -1;



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
        clogError("Error compiling vertex code", NULL);

    if (info_log_length > 1) { // one char is the \0
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetShaderInfoLog(VertexShaderID, info_log_length, NULL, info_log);
        clogInfo(info_log, NULL);
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
        clogError("Error compiling fragment code", NULL);

    if (info_log_length > 1) {
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetShaderInfoLog(FragmentShaderID, info_log_length, NULL, info_log);
        clogWarning(info_log, NULL);
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
        clogError("Error linking program", NULL);

    if (info_log_length > 1) {
        GLchar* info_log = malloc((info_log_length + 1) * sizeof(GLchar));
        glGetProgramInfoLog(program_id, info_log_length, NULL, info_log);
        clogWarning(info_log, NULL);
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

#endif // SHADERS_H