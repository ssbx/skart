#include <fedCommon.h>
#include <fedGl.h>
#include <fedShader.h>

#include <stdio.h>
#include <math.h>
#include <cglm.h>
#include <clog.h>

// local
#include <stdlib.h>

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

static CGLMmat4 model;
static CGLMmat4 MVP;

void fedGl_Init(int startWindowed)
{

    clogDebugMsg("fedGlIit");

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
        
        FED_Window = glfwCreateWindow(
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
        
        printf("hello %f %f %f\n", FED_SCREEN_HEIGHT, FED_SCREEN_WIDTH, FED_SCREEN_RATIO);
        
        FED_Window = glfwCreateWindow(
            FED_SCREEN_WIDTH, FED_SCREEN_HEIGHT, "Federation", monitor, NULL);
        
    }
    
    if (!FED_Window)
    {
        clogErrorMsg("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(0);
    }
   
    
    glfwMakeContextCurrent(FED_Window);


    if (glewInit() != GLEW_OK)
    {
        clogErrorMsg("fed_gl_init Failed to initialize GLEW\n");
        glfwTerminate();
        exit(1);
    }
 
    glViewport(0, 0, FED_SCREEN_WIDTH, FED_SCREEN_HEIGHT);
    
    glfwSwapInterval(1);
    glfwSetInputMode(FED_Window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // configure begin
    program_id = fedShader_Load(
        "shaderVertex.glsl",
        "shaderFragment.glsl"
    );

    IN_modelViewProjection =
        glGetUniformLocation(program_id, "modelViewProjection");

    IN_sinVar =
        glGetUniformLocation(program_id, "sinVar");

    IN_modelVertex =
        glGetAttribLocation(program_id, "modelVertex");

    IN_colorVertex =
        glGetAttribLocation(program_id, "vertexColor");


    FED_MATRIX_Projection = cglmPerspective(45, FED_SCREEN_RATIO, 0.1, 100.0);
    //FED_ProjectionMatrix = cglmOrtho(-10,10,-10,10,0,100);

    CGLMvec3 eye    = {4,3,3};
    CGLMvec3 center = {0,0,0};
    CGLMvec3 up     = {0,1,0};
    FED_MATRIX_View = cglmLookAt(eye, center, up);
    model = cglmMat4(1);
    MVP = cglmMultMat4(cglmMultMat4(FED_MATRIX_Projection, FED_MATRIX_View), model);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                 g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
                 g_color_buffer_data, GL_STATIC_DRAW);


}

void fedGl_Update()
{
    MVP = cglmMultMat4(cglmMultMat4(FED_MATRIX_Projection, FED_MATRIX_View), model);
    
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
    glfwSwapBuffers(FED_Window);
    glfwPollEvents();
}

void fedGl_Cleanup()
{

    clogDebugMsg("fedGlCleanup");
    glfwDestroyWindow(FED_Window);
    glfwTerminate();

}
