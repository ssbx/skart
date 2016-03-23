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



    if (argc > 1) {
        if (strcmp(argv[1], "basic_test") == 0) {
            clogInfoMsg("Start in test mode\n");
            fedGlInit();
            fedGlUpdate();
            fedGlCleanup();
            return 0;
        }
    }

    fedInputInit(0.01f);
    sndoInit(0.05);
    SND_Intro = sndoLoad("../tes.wav");
    SND_GunShot = sndoLoad("data/sounds/shot.wav");
    sndoPlay(SND_Intro);
    
    glfwSetErrorCallback(clogGLFWErrorCallback);

    fedGlInit();
    
    glfwSetKeyCallback(fed_window, fedKeyCallback);
    glfwSetMouseButtonCallback(fed_window, fedMouseButtonCallback);
    glfwSetCursorPosCallback(fed_window, fedCursorPosCallback);
    glfwSetScrollCallback(fed_window, fedScrollCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        fedGlUpdate();
    }

    fedGlCleanup();
    sndoTerminate();

    return 0;

}
