/**
 * @file federation.c
 * @brief Federation FPS
 * @version 0.1
 *
 * Simple FPS game created for learning various C/C++ tools and real time
 * rendering.
 *
 */

#include "f_common.h"
#include "f_gl.h"
#include "f_input.h"

#include <clog.h>
#include <shake.h>
#include <cargo.h>

#include <stdio.h>
#include <string.h>


void glfwErrors(int error, const char* description)
{
    
    clogError("GLFW error n %d: %s", error, description);
    
}

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
        
        FGl_InitScreen(startWindowed);
        FGl_UpdateScreen();
        FGl_CleanupScreen();
        return 0;
        
    }
    

    // init sounds
    shakeInit(0.05);
    FED_SOUND_GunShot = shakeLoad("shot.wav");
        
    glfwSetErrorCallback(glfwErrors);
    FGl_InitScreen(startWindowed);

    FInput_Init(
        0.0015,         // mouseSpeed
        180.0,          // horizontalAngle
        0.0,            // verticalAngle
        45.0,           // fieldOfView
        (CGLMvec3) {3,0,10},    // position
        (CGLMvec3) {0,0,0}      // direction
    );
    
    glfwSetInputMode(FED_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(FED_Window, FInput_KeyCallback);
    glfwSetMouseButtonCallback(FED_Window, FInput_MouseButtonCallback);
    glfwSetCursorPosCallback(FED_Window, FInput_CursorPosCallback);
    glfwSetScrollCallback(FED_Window, FInput_ScrollCallback);

    while (!glfwWindowShouldClose(FED_Window))
    {
        FInput_GetUserInputs();
        FGl_UpdateScreen();
    }
    
    FGl_CleanupScreen();
    shakeTerminate();

    return 0;

}
