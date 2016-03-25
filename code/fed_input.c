#include "fed_input.h"
#include "shake.h"
#include <cglm.h>
#include <math.h>

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
    } else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glfwIconifyWindow(FED_Window);
        return;
    }
}

void fedScrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset)
{
}

void fedCursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos)
{
    
    INPUT_currentTime = glfwGetTime();
    INPUT_deltaTime   = INPUT_currentTime - INPUT_lastTime;
    
    INPUT_horizontalAngle += INPUT_mouseSpeed * (INPUT_cursorLastXPos - xpos);
    INPUT_verticalAngle   += INPUT_mouseSpeed * (INPUT_cursorLastYPos - ypos);
    
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
    
    float fov = INPUT_fieldOfView;
    FED_MATRIX_Projection = cglmPerspective(fov, SCREEN_RATIO, 0.1, 100.0);
    FED_MATRIX_View = cglmLookAt(
        INPUT_position,
        cglmAddVec3(INPUT_position, direction),
        up
    );
    
    INPUT_lastTime = INPUT_currentTime;
    INPUT_cursorLastXPos = xpos;
    INPUT_cursorLastYPos = ypos;
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
                shakePlay(FED_SOUND_GunShot);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                shakePlay(FED_SOUND_GunShot);
                if (INPUT_fieldOfView == 45.0) {
                    INPUT_fieldOfView = 360.0;
                    FED_MATRIX_Projection = cglmPerspective(
                                    INPUT_fieldOfView, SCREEN_RATIO, 0.1, 100.0);
                } else {
                    INPUT_fieldOfView = 45.0;
                    FED_MATRIX_Projection = cglmPerspective(
                                    INPUT_fieldOfView, SCREEN_RATIO, 0.1, 100.0);
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                shakePlay(FED_SOUND_GunShot);
                break;
        }
    }
}
