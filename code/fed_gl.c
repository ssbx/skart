#include "federation.h"

#include "fed_gl.h"
#include "fed_log.h"




// local
#include <stdlib.h>

void fedGlInit0()
{

    fedDebugMsg("fedGlInit0");

    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    fed_window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!fed_window)
    {
        fedErrorMsg("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(fed_window);


    if (glewInit() != GLEW_OK)
    {
        fedErrorMsg("fed_gl_init Failed to initialize GLEW\n");
        fedGlCleanup();
        exit(1);
    }

    glfwSwapInterval(1);

}

void fedGlInit()
{

    fedDebugMsg("fedGlIit");

    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    fed_window = glfwCreateWindow(1024, 768, "Simple example", NULL, NULL);
    if (!fed_window)
    {
        fedErrorMsg("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(fed_window);


    if (glewInit() != GLEW_OK)
    {
        fedErrorMsg("fed_gl_init Failed to initialize GLEW\n");
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(1);

}


void fedGlCleanup()
{

    fedDebugMsg("fedGlCleanup");
    glfwDestroyWindow(fed_window);
    glfwTerminate();

}
