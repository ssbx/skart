#ifndef FGL_H
#define FGL_H


#include "f_input.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm.h>
#include <clog.h>
#include <soil.h>

#include <stdio.h>
#include <stdlib.h>

static GLuint programID;
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
     1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
     1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
     1.0f,-1.0f, 1.0f
};

static const GLfloat g_uv_buffer_data[] = { 
    0.000059f, 1.0f-0.000004f, 
    0.000103f, 1.0f-0.336048f, 
    0.335973f, 1.0f-0.335903f, 
    1.000023f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.336024f, 1.0f-0.671877f, 
    0.667969f, 1.0f-0.671889f, 
    1.000023f, 1.0f-0.000013f, 
    0.668104f, 1.0f-0.000013f, 
    0.667979f, 1.0f-0.335851f, 
    0.000059f, 1.0f-0.000004f, 
    0.335973f, 1.0f-0.335903f, 
    0.336098f, 1.0f-0.000071f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.336024f, 1.0f-0.671877f, 
    1.000004f, 1.0f-0.671847f, 
    0.999958f, 1.0f-0.336064f, 
    0.667979f, 1.0f-0.335851f, 
    0.668104f, 1.0f-0.000013f, 
    0.335973f, 1.0f-0.335903f, 
    0.667979f, 1.0f-0.335851f, 
    0.335973f, 1.0f-0.335903f, 
    0.668104f, 1.0f-0.000013f, 
    0.336098f, 1.0f-0.000071f, 
    0.000103f, 1.0f-0.336048f, 
    0.000004f, 1.0f-0.671870f, 
    0.336024f, 1.0f-0.671877f, 
    0.000103f, 1.0f-0.336048f, 
    0.336024f, 1.0f-0.671877f, 
    0.335973f, 1.0f-0.335903f, 
    0.667969f, 1.0f-0.671889f, 
    1.000004f, 1.0f-0.671847f, 
    0.667979f, 1.0f-0.335851f
};
static GLuint vertexbuffer;
static GLuint uvbuffer;

static GLuint VertexUVID;
static GLuint MatrixID;
static GLuint vertexPosition_modelspaceID;
static GLuint Texture;
static GLuint TextureID;

float FED_SCREEN_HEIGHT;
float FED_SCREEN_WIDTH;
float FED_SCREEN_RATIO;

GLFWwindow *FED_WINDOW; //< Federation main window

/*=============================================================================
 * SHADER UTILS
 *============================================================================*/
typedef struct FileDump {
    int   size;
    char* dump;
} FileDump;

char* FGl_DumpShaderFile(const char* file_path)
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
GLuint FGl_LoadShader(
    const char * vertex_file_path,
    const char * fragment_file_path)
{


    // Create the shaders
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


    // read vertex file
    char* vertex_code = FGl_DumpShaderFile(vertex_file_path);
    if (!vertex_code)
        return -1;


    // read fragment file
    char* fragment_code = FGl_DumpShaderFile(fragment_file_path);
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


/*=============================================================================
 * OPENGL
 *============================================================================*/
GLFWwindow* FGl_InitScreen(int startWindowed)
{
    
    
    if (!glfwInit()) {
        exit(1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    if (startWindowed == 1) {
                
        FED_SCREEN_WIDTH = 1024;
        FED_SCREEN_HEIGHT = 768;
        FED_SCREEN_RATIO = FED_SCREEN_WIDTH / FED_SCREEN_HEIGHT;
        
        FED_WINDOW = glfwCreateWindow(
            FED_SCREEN_WIDTH, FED_SCREEN_HEIGHT, "Federation", NULL, NULL);
        
    } else {
 
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        
        FED_SCREEN_WIDTH = mode->width;
        FED_SCREEN_HEIGHT = mode->height;
        FED_SCREEN_RATIO = FED_SCREEN_WIDTH / FED_SCREEN_HEIGHT;
        
        clogInfo("%f %f %f\n", FED_SCREEN_HEIGHT, FED_SCREEN_WIDTH, FED_SCREEN_RATIO);
        
        FED_WINDOW = glfwCreateWindow(
            FED_SCREEN_WIDTH, FED_SCREEN_HEIGHT, "Federation", monitor, NULL);
        
    }
    
    if (!FED_WINDOW)
    {
        clogError("fed_gl_init Failed to open GLFW window.", NULL);
        glfwTerminate();
        exit(0);
    }
   
    
    glfwMakeContextCurrent(FED_WINDOW);


    if (glewInit() != GLEW_OK)
    {
        clogError("fed_gl_init Failed to initialize GLEW.", NULL);
        glfwTerminate();
        exit(1);
    }
 
    glViewport(0, 0, FED_SCREEN_WIDTH, FED_SCREEN_HEIGHT);
    
    glfwSwapInterval(1);
    glfwSetInputMode(FED_WINDOW, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // configure begin
    programID = FGl_LoadShader(
        "TransformVertexShader.glsl",
        "TextureFragmentShader.glsl"
    );
    
    MatrixID = glGetUniformLocation(programID, "MVP");
    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    VertexUVID = glGetAttribLocation(programID, "vertexUV");

    Texture = SOIL_load_OGL_texture(
        "uvtemplate.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
          SOIL_FLAG_COMPRESS_TO_DXT
        | SOIL_FLAG_INVERT_Y
        | SOIL_FLAG_NTSC_SAFE_RGB
        | SOIL_FLAG_MIPMAPS
    );
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    /*
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    */
    
    if (Texture == 0)
    {
        clogError( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    
    TextureID = glGetUniformLocation(programID, "myTextureSampler");
    
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data),
                 g_uv_buffer_data, GL_STATIC_DRAW);


    return FED_WINDOW;
}

void FGl_UpdateScreen()
{
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(FED_MVP.a0));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glUniform1i(TextureID, 0);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        vertexPosition_modelspaceID,     // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : UVs
    glEnableVertexAttribArray(VertexUVID);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(
        VertexUVID,               // The attribute we want to configure
        2,                           // size
        GL_FLOAT,                    // type
        GL_FALSE,                    // normalized?
        0,                           // stride
        (void*)0                     // array buffer offset
    );



    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(vertexPosition_modelspaceID);
    glDisableVertexAttribArray(VertexUVID);

    // Swap buffers
    glfwSwapBuffers(FED_WINDOW);
    glfwPollEvents();
}

void FGl_CleanupScreen()
{

    glfwDestroyWindow(FED_WINDOW);
    glfwTerminate();

}

#endif // FGL_H