#ifndef SCREEN_H
#define SCREEN_H


#include "inputs.h"
#include "shaders.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>

#include <clog.h>
#include <soil.h>
#include <obj.h>

#include <stdio.h>
#include <stdlib.h>

static OBJscene scene;

static GLuint programID;

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
GLFWwindow*
init_screen(int startWindowed)
{
    int objLoad_status;

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
        GLFWmonitor*       monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS,     mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS,   mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS,    mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        screenWidth  = mode->width;
        screenHeight = mode->height;
        FED_screenRatio = screenWidth / screenHeight;

        clogInfo("%f %f %f\n", screenHeight, screenWidth, FED_screenRatio);

        MAIN_WINDOW = glfwCreateWindow(
            screenWidth, screenHeight, "Federation", monitor, NULL);
    }

    if (!MAIN_WINDOW) {
        clogError("Failed to open GLFW window.", NULL);
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(MAIN_WINDOW);

    if (glewInit() != GLEW_OK) {
        clogError("Failed to initialize GLEW.", NULL);
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
        "scenes/cube/TransformVertexShader.glsl",
        "scenes/cube/TextureFragmentShader.glsl"
    );

    MatrixID = glGetUniformLocation(programID, "MVP");
    vertexPosition_modelspaceID = glGetAttribLocation(
                                        programID, "vertexPosition_modelspace");
    VertexUVID = glGetAttribLocation(programID, "vertexUV");

    Texture = SOIL_load_OGL_texture(
        "scenes/cube/uvtemplate.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
          SOIL_FLAG_COMPRESS_TO_DXT
        | SOIL_FLAG_INVERT_Y
        | SOIL_FLAG_NTSC_SAFE_RGB
        | SOIL_FLAG_MIPMAPS
    );

    if (Texture == 0) {
        clogError( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }

    TextureID = glGetUniformLocation(programID, "myTextureSampler");

    scene = objLoad("scenes/cube/cube.obj", &objLoad_status);
    if (objLoad_status == OBJ_FALSE) {
        clogError( "Obj load error\n", NULL);
        exit(1);
    } else {
        clogDebug( "Successfully loaded obj file\n", NULL);
    }

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(OBJvec3) * scene.vertices_count,
                                            &scene.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(OBJvec2) * scene.vertices_count,
                                                &scene.uvs[0], GL_STATIC_DRAW);

    return MAIN_WINDOW;
}

void
update_screen()
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
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangle

    glDisableVertexAttribArray(vertexPosition_modelspaceID);
    glDisableVertexAttribArray(VertexUVID);

    // Swap buffers
    glfwSwapBuffers(MAIN_WINDOW);
    poll_events_input();
}

void
cleanup_screen()
{
    objRelease(scene);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &TextureID);
    glfwDestroyWindow(MAIN_WINDOW);
    glfwTerminate();
}

#endif // SCREEN_H
