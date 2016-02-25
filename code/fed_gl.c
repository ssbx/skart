#include "fed_gl.h"
#include "fed_log.h"


// GLFWwindow *fed_window
#include "federation.h"


// local
#include <stdlib.h>


void fed_gl_init()
{

    fed_log_printDebug("fed_gl_init");

    if (!glfwInit()) {
        exit(1);
    }

    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    fed_window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!fed_window)
    {
        fed_log_printError("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(fed_window);


    if (glewInit() != GLEW_OK)
    {
        fed_log_printError("fed_gl_init Failed to initialize GLEW\n");
        fed_gl_cleanup();
        exit(1);
    }

    glfwSwapInterval(1);

}


void fed_gl_cleanup()
{

    fed_log_printDebug("fed_gl_cleanup");
    glfwDestroyWindow(fed_window);
    glfwTerminate();

}
