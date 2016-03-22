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

#include <sndo.h>

#include <string.h>

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


    sndoInit();
    GUN_SHOT = sndoLoad("data/sounds/shot.wav");

    if (argc > 1) {
        if (strcmp(argv[1], "basic_test") == 0) {
            clogInfoMsg("Start in test mode\n");
            fedGlInit();
            fedGlUpdate();
            fedGlCleanup();
            return 0;
        }
    }

    glfwSetErrorCallback(clogGLFWErrorCallback);

    fedGlInit();
    glfwSetKeyCallback(fed_window, fedKeyCallback);
    glfwSetMouseButtonCallback(fed_window, fedMouseButtonCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        fedGlUpdate();
    }

    fedGlCleanup();
    sndoTerminate();

    return 0;

}
