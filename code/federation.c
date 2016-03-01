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
#include "fed_log.h"
#include "fed_input.h"

#include "ex0.h"
#include "ex1.h"
#include "ex2.h"

// define init version: FGl_init0 [ FGl_init
#define FGL_INIT   fedGlInit

// define example: exN_*
#define EX_INIT    ex2_init
#define EX_UPDATE  ex2_update
#define EX_CLEANUP ex2_cleanup

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

    glfwSetErrorCallback(fedErrorCallback);

    FGL_INIT();

    EX_INIT();

    glfwSetKeyCallback(fed_window, fedKeyCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        EX_UPDATE();
    }

    EX_CLEANUP();
    fedGlCleanup();

    return 0;

}
