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
static Matrix projection;
static Matrix view;
static Matrix model;
static Matrix MVP;

void ex1_init()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    program_id = FLoadShader(
        "data/shaders/SimpleTransform.vertexshader",
        "data/shaders/SingleColor.fragmentshader"
    );

    IN_modelViewProjection =
        glGetUniformLocation(program_id, "modelViewProjection");

    IN_modelVertex =
        glGetAttribLocation(program_id, "modelVertex");


    projection = FMath_perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    Vector4 v1 = {{0,0,0,0}};
    Vector4 v2 = {{0,0,0,0}};
    view = FMath_lookAt(v1,v2);

    model = IDENTITY_MATRIX;

    //Matrix compresult = FMath_multiplymat4(&projection, &view);
    //MVP = FMath_multiplymat4(&compresult, &model);
    MVP = FMath_multiplymat4(&projection, &view);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    return;
}

void ex1_update()
{

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // Use our shader
    glUseProgram(program_id);

    glUniformMatrix4fv(IN_modelViewProjection, 1, GL_FALSE, &(model.m[0]));
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
