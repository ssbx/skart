/**
 * @file federation.c
 * @brief Federation FPS
 * @version 0.1
 *
 * Simple FPS game created for learning various C/C++ tools and real time
 * rendering.
 *
 */
#include "federation.h"
#include "fed_gl.h"
#include "fed_input.h"
#include <clog.h>

/**
 * @fn int main(int argc, char* argv[])
 * @brief Federation main loop.
 *
 * @return 0
 */
int main(
    int   argc,
    char* argv[])
{

    glfwSetErrorCallback(clogErrorCallback);

    fedGlInit();
    glfwSetKeyCallback(fed_window, fedKeyCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        fedGlUpdate();
    }

    fedGlCleanup();

    return 0;

}
