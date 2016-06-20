#ifndef FGL_H
#define FGL_H


#include "inputs.h"
#include "shaders.h"

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

float screenHeight;
float screenWidth;

float       FED_screenRatio;
GLFWwindow* MAIN_WINDOW; //< Federation main window
CGLMmat4    FED_mvp;



/*=============================================================================
 * OPENGL
 *============================================================================*/
GLFWwindow* init_screen(int startWindowed)
{
    
    
    if (!glfwInit()) {
        clogError("GLFW init failure\n", NULL);
        exit(1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    if (startWindowed == 1) {
                
        screenWidth = 1024;
        screenHeight = 768;
        FED_screenRatio = screenWidth / screenHeight;
        
        MAIN_WINDOW = glfwCreateWindow(
            screenWidth, screenHeight, "Federation", NULL, NULL);
        
    } else {
 
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        
        screenWidth = mode->width;
        screenHeight = mode->height;
        FED_screenRatio = screenWidth / screenHeight;
        
        clogInfo("%f %f %f\n", screenHeight, screenWidth, FED_screenRatio);
        
        MAIN_WINDOW = glfwCreateWindow(
            screenWidth, screenHeight, "Federation", monitor, NULL);
        
    }
    
    if (!MAIN_WINDOW)
    {
        clogError("fed_gl_init Failed to open GLFW window.", NULL);
        glfwTerminate();
        exit(0);
    }
   
    
    glfwMakeContextCurrent(MAIN_WINDOW);


    if (glewInit() != GLEW_OK)
    {
        clogError("fed_gl_init Failed to initialize GLEW.", NULL);
        glfwTerminate();
        exit(1);
    }
 
    glViewport(0, 0, screenWidth, screenHeight);
    
    glfwSwapInterval(1);
    glfwSetInputMode(MAIN_WINDOW, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // configure begin
    programID = load_shader(
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


    return MAIN_WINDOW;
}

void update_screen()
{
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(FED_mvp.a0));

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
    glfwSwapBuffers(MAIN_WINDOW);
    glfwPollEvents();
}

void cleanup_screen()
{

    glfwDestroyWindow(MAIN_WINDOW);
    glfwTerminate();

}

#endif // FGL_H
