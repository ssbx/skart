#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "fGl.h"
#include "fInput.h"
#include "fSounds.h"

#include <clog.h>
#include <cargo.h>

#include <stdio.h>
#include <string.h>

void glfwErrors(int error, const char* description)
{
    clogError("GLFW error n %d: %s", error, description);
}



int main(int argc, char* argv[])
{
 
    // maybe start windowed
    char* windowed = cargoFlag("windowed", "FALSE", argc, argv);

    int startWindowed;
    if (strcmp(windowed, "TRUE") == 0)
        startWindowed = 1;
    else
        startWindowed = 0;
    

    // configure glfw errors
    glfwSetErrorCallback(glfwErrors);


    // init glfw/glew/opengl
    GLFWwindow* win = FGl_InitScreen(startWindowed);

    // init sounds
    FSounds_Init();

    // configure inputs
    FInput_Init(
        0.0015,         // mouseSpeed
        180.0,          // horizontalAngle
        0.0,            // verticalAngle
        45.0,           // fieldOfView
        (CGLMvec3) {3,0,10},    // position
        (CGLMvec3) {0,0,0}      // direction
    );
    
    glfwSetInputMode          (win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback        (win, FInput_KeyCallback);
    glfwSetMouseButtonCallback(win, FInput_MouseButtonCallback);
    glfwSetCursorPosCallback  (win, FInput_CursorPosCallback);
    glfwSetScrollCallback     (win, FInput_ScrollCallback);


    // begin to loop
    while (!glfwWindowShouldClose(win))
    {
        FInput_GetImmediateKeyInputs();
        FGl_UpdateScreen();
    }
    

    // cleanup
    FGl_CleanupScreen();
    shakeTerminate();


    return 0;

}
