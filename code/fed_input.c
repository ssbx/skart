#include "fed_input.h"
#include "sndo.h"
#include <cglm.h>
#include <math.h>

double INPUT_lastTime;
double INPUT_currentTime;
float INPUT_mouseSpeed;
float INPUT_deltaTime;
float INPUT_horizontalAngle;
float INPUT_verticalAngle;
float INPUT_initialFoV;
CGLMvec3 INPUT_position;

void fedInputInit(float mouseSpeed)
{
    
    INPUT_lastTime = glfwGetTime();
    INPUT_mouseSpeed = 0.002;
    INPUT_horizontalAngle = 3.14;
    INPUT_verticalAngle = 0.0;
    INPUT_initialFoV = 45.0;
    INPUT_position = (CGLMvec3) {4,4,3};
    

}

void fedKeyCallback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
}

void fedCursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos)
{
    
    INPUT_currentTime = glfwGetTime();
    INPUT_deltaTime   = INPUT_currentTime - INPUT_lastTime;
    
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    INPUT_horizontalAngle += INPUT_mouseSpeed * (float) (1024.0/2.0 - xpos) ;
    INPUT_verticalAngle   += INPUT_mouseSpeed * (float) (768.0/2.0 - ypos);
    
    CGLMvec3 direction = {
        cos(INPUT_verticalAngle) * sin(INPUT_horizontalAngle), 
        sin(INPUT_verticalAngle),
        cos(INPUT_verticalAngle) * cos(INPUT_horizontalAngle)
    };
    
    CGLMvec3 right = {
        sin(INPUT_horizontalAngle - 3.14f/2.0f),
        0,
        cos(INPUT_horizontalAngle - 3.14f/2.0f)
    };
    
    CGLMvec3 up = cglmCross(right, direction);
    
    float fov = INPUT_initialFoV;
    FED_ProjectionMatrix = cglmPerspective(fov, (float) 4/3, 0.1, 100.0);
    FED_ViewMatrix = cglmLookAt(
        INPUT_position,
        cglmAddVec3(INPUT_position, direction),
        up
    );
    
    INPUT_lastTime = INPUT_currentTime;
}


void fedMouseButtonCallback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods)
{
    if (action == GLFW_PRESS) 
    {
        switch(button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                sndoPlay(SND_GunShot);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                sndoPlay(SND_GunShot);
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                sndoPlay(SND_GunShot);
                break;
        }
    }
}
