#include "federation.h"
#include "ex1.h"
#include "fed_shader.h"
#include "fed_math.h"

static GLuint program_id;
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
static const GLushort g_element_buffer_data[] = { 0, 1, 2 };
static GLuint vertexbuffer;
static GLuint IN_modelVertex;
static GLuint IN_modelViewProjection;
static Mat4 projection;
static Mat4 view;
static Mat4 model;
static Mat4 MVP;

void ex1_init()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    program_id = fedLoadShaders(
        "data/shaders/SimpleTransform.vertexshader",
        "data/shaders/SingleColor.fragmentshader"
    );

    IN_modelViewProjection =
        glGetUniformLocation(program_id, "modelViewProjection");

    IN_modelVertex =
        glGetAttribLocation(program_id, "modelVertex");


    projection = perspective(45, (GLfloat) 4/3, 0.1, 100);

    Vec3 eye    = {4,3,3};
    Vec3 center = {0,0,0};
    Vec3 up     = {0,1,0};
    view = lookAt(eye, center, up);
    model = mat4(1);
    MVP = mplMat4(mplMat4(projection, view), model);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);
}

void ex1_update()
{

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // Use our shader
    glUseProgram(program_id);

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

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(IN_modelVertex);

    // Swap buffers
    glfwSwapBuffers(fed_window);
    glfwPollEvents();

}

void ex1_cleanup()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(program_id);
    return;
}
