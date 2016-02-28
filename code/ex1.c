#include "federation.h"
#include "ex1.h"
#include "fed_shader.h"
#include "fed_math.h"
#include "fed_math2.h"

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
static Mat4 look;

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


    projection = fedPerspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    fedPrintMat(projection, "projection");

    Vector4 v1 = {{4,3,3,1}};
    Vector4 v2 = {{0,0,0,0}};
    view = fedLookAt(v1,v2);
    fedPrintMat(view, "view");

    model = IDENTITY_MATRIX;
    fedPrintMat(model, "model");

    Matrix compresult = fedMultiplymat4(&projection, &model);
    fedPrintMat(compresult, "intermediary");
    MVP = fedMultiplymat4(&compresult, &model);
    fedPrintMat(MVP, "MVP");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    Mat4 mattest2 = mat4(1);
    printMat4(mattest2, "hello");
    Mat4 mattest = multiplyMat4(mattest2, mat4(1));
    printMat4(mattest, "hello");

    Vec3 t1 = {4.0f, 3.0f, 3.0f};
    Vec3 t2 = {0.0f, 0.0f, 0.0f};
    Vec3 t3 = {0.0f, 1.0f, 0.0f};

    look = lookAt(t1,t2,t3);

    fedPrintMat(view, "view");
    printMat4(look, "view");

    Mat4 proj = perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
    fedPrintMat(projection, "projection");
    printMat4(proj, "projection");
    //Mat4 mattest = fedMultiplymat4(mattest2);
    Mat4 d = multiplyMat4(look, look);
    printMat4(d, "mult");
    //fedPrintMat4(mattest);

    return;
}

void ex1_update()
{

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );

    // Use our shader
    glUseProgram(program_id);

    glUniformMatrix4fv(IN_modelViewProjection, 1, GL_FALSE, &(look.a0));
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
