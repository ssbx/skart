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
#include <shake.h>
#include <cargo.h>

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

 
    char* windowed = cargoFlag("windowed", "FALSE", argc, argv);
    int startWindowed;
    if (strcmp(windowed, "TRUE") == 0) {
        startWindowed = 1;
    } else {
        startWindowed = 0;
    }    
    
    
    char* testing = cargoFlag("testing", "FALSE", argc, argv); 
    if (strcmp(testing, "TRUE") == 0) {
        
        clogInfoMsg("Start in test mode\n");
        fedGlInit(startWindowed);
        fedGlUpdate();
        fedGlCleanup();
        return 0;
        
    }
    
    // init sounds
    shakeInit(0.05);
    FED_SOUND_GunShot = shakeLoad("data/sounds/shot.wav");
        
    // initial input variables
    INPUT_lastTime        = glfwGetTime();
    INPUT_mouseSpeed      = 0.0015;
    INPUT_horizontalAngle = 3.14;
    INPUT_verticalAngle   = 0.0;
    INPUT_fieldOfView     = 45.0;
    INPUT_position = (CGLMvec3) {4,4,3};
    
    glfwSetErrorCallback(clogGLFWErrorCallback);
    
    fedGlInit(startWindowed);
    glfwSetInputMode(FED_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(FED_Window, &INPUT_cursorLastXPos, &INPUT_cursorLastYPos);
    glfwSetKeyCallback(FED_Window, fedKeyCallback);
    glfwSetMouseButtonCallback(FED_Window, fedMouseButtonCallback);
    glfwSetCursorPosCallback(FED_Window, fedCursorPosCallback);
    glfwSetScrollCallback(FED_Window, fedScrollCallback);

    while (!glfwWindowShouldClose(FED_Window))
    {
        fedGlUpdate();
    }

    fedGlCleanup();
    shakeTerminate();

    return 0;

}
