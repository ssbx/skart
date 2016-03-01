#include "federation.h"
#include "ex3.h"
#include "fed_shader.h"
#include "cglm.h"
#include "stdio.h"
#include "math.h"

static GLuint program_id;
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


#define COL1 1.0f, 0.0f, 0.0f,
#define COL2 1.0f, 0.2f, 0.0f,
#define COL3 1.0f, 0.4f, 0.0f,
#define COLEND 1.0f, 0.2f, 0.0f

static const GLfloat g_color_buffer_data[] = {
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COL3
    COL1
    COL2
    COLEND
};

static GLuint vertexbuffer;
static GLuint colorbuffer;
static GLuint IN_modelVertex;
static GLuint IN_colorVertex;
static GLuint IN_modelViewProjection;
static GLuint IN_sinVar;

static Mat4 projection;
static Mat4 view;
static Mat4 model;
static Mat4 MVP;

void ex3_init()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    program_id = fedLoadShaders(
        "data/shaders/fedVertexShader.glsm",
        "data/shaders/fedFragmentShader.glsm"
    );

    IN_modelViewProjection =
        glGetUniformLocation(program_id, "modelViewProjection");

    IN_sinVar =
        glGetUniformLocation(program_id, "sinVar");

    IN_modelVertex =
        glGetAttribLocation(program_id, "modelVertex");

    IN_colorVertex =
        glGetAttribLocation(program_id, "vertexColor");


    projection = perspective(45, (GLfloat) 4/3, 0.1, 100.0);

    Vec3 eye    = {4,3,3};
    Vec3 center = {0,0,0};
    Vec3 up     = {0,1,0};
    view = lookAt(eye, center, up);
    model = mat4(1);
    MVP = multMat4(multMat4(projection, view), model);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
                 g_color_buffer_data, GL_STATIC_DRAW);


}

void ex3_update()
{

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(program_id);

    float tsin = (float) sin(glfwGetTime());
    if (tsin < 0) {
        tsin = -tsin;
    }
    glUniform1f(IN_sinVar, tsin);
    glUniformMatrix4fv(IN_modelViewProjection, 1, GL_FALSE, &(MVP.a0));

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(IN_modelVertex);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        IN_modelVertex,     // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(IN_colorVertex);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        IN_colorVertex,               // The attribute we want to configure
        3,                           // size
        GL_FLOAT,                    // type
        GL_FALSE,                    // normalized?
        0,                           // stride
        (void*)0                     // array buffer offset
    );



    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 12*3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(IN_modelVertex);
    glDisableVertexAttribArray(IN_colorVertex);

    // Swap buffers
    glfwSwapBuffers(fed_window);
    glfwPollEvents();

}

void ex3_cleanup()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(program_id);
    return;
}
