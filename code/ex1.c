#include "federation.h"
#include "ex1.h"
#include "fed_shader.h"

static GLuint program_id;
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
static GLuint vertexbuffer;
static GLuint vertexPosition_modelspaceID;

void ex1_init()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    program_id = FShader_load(
        "data/shaders/SimpleVertexShader.vertexshader",
        "data/shaders/SimpleFragmentShader.fragmentshader"
    );

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

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(vertexPosition_modelspaceID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        vertexPosition_modelspaceID, // The attribute we want to configure
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

    glDisableVertexAttribArray(vertexPosition_modelspaceID);

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
