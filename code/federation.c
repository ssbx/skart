
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

// define init version: FGl_init0 [ FGl_init
#define FGL_INIT   FGlInit

// define example: exN_*
#define EX_INIT    ex1_init
#define EX_UPDATE  ex1_update
#define EX_CLEANUP ex1_cleanup

/**
 * @fn int main(int argc, char* argv)
 * @brief Federation main loop.
 *
 * @return 0
 */
int main(
    int   argc,
    char* argv)
{

    glfwSetErrorCallback(FErrorCallback);

    FGL_INIT();

    EX_INIT();

    glfwSetKeyCallback(fed_window, FKeyCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        EX_UPDATE();
    }

    EX_CLEANUP();
    FGlCleanup();

    return 0;

}
