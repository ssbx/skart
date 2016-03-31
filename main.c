/**
 * @file federation.c
 * @brief Federation FPS
 * @version 0.1
 *
 * Simple FPS game created for learning various C/C++ tools and real time
 * rendering.
 *
 */

#include <fedCommon.h>
#include <fedGl.h>
#include <fedInput.h>

#include <string.h>
#include <clog.h>
#include <shake.h>
#include <cargo.h>


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
        fedGl_Init(startWindowed);
        fedGl_Update();
        fedGl_Cleanup();
        return 0;
        
    }
    
    // init sounds
    shakeInit(0.05);
    FED_SOUND_GunShot = shakeLoad("shot.wav");
        
    // initial input variables
    FED_INPUT_lastTime        = glfwGetTime();
    FED_INPUT_mouseSpeed      = 0.0015;
    FED_INPUT_horizontalAngle = 3.14;
    FED_INPUT_verticalAngle   = 0.0;
    FED_INPUT_fieldOfView     = 45.0;
    FED_INPUT_position = (CGLMvec3) {4,4,3};
    
    glfwSetErrorCallback(clogGLFWErrorCallback);
    
    fedGl_Init(startWindowed);
    glfwSetInputMode(FED_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(FED_Window, &FED_INPUT_cursorLastXPos, &FED_INPUT_cursorLastYPos);
    glfwSetKeyCallback(FED_Window, fedInput_KeyCallback);
    glfwSetMouseButtonCallback(FED_Window, fedInput_MouseButtonCallback);
    glfwSetCursorPosCallback(FED_Window, fedInput_CursorPosCallback);
    glfwSetScrollCallback(FED_Window, fedInput_ScrollCallback);

    while (!glfwWindowShouldClose(FED_Window))
    {
        fedGl_Update();
    }

    fedGl_Cleanup();
    shakeTerminate();

    return 0;

}
