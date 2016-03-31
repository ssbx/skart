#include <fedInput.h>

#include <shake.h>
#include <cglm.h>
#include <math.h>

void fedInput_KeyCallback(
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

void fedInput_ScrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset)
{
}

void fedInput_CursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos)
{
    
    FED_INPUT_currentTime = glfwGetTime();
    FED_INPUT_deltaTime   = FED_INPUT_currentTime - FED_INPUT_lastTime;
    
    FED_INPUT_horizontalAngle += FED_INPUT_mouseSpeed * (FED_INPUT_cursorLastXPos - xpos);
    FED_INPUT_verticalAngle   += FED_INPUT_mouseSpeed * (FED_INPUT_cursorLastYPos - ypos);
    
    CGLMvec3 direction = {
        cos(FED_INPUT_verticalAngle) * sin(FED_INPUT_horizontalAngle), 
        sin(FED_INPUT_verticalAngle),
        cos(FED_INPUT_verticalAngle) * cos(FED_INPUT_horizontalAngle)
    };
    
    CGLMvec3 right = {
        sin(FED_INPUT_horizontalAngle - 3.14f/2.0f),
        0,
        cos(FED_INPUT_horizontalAngle - 3.14f/2.0f)
    };
    
    CGLMvec3 up = cglmCross(right, direction);
    
    float fov = FED_INPUT_fieldOfView;
    FED_MATRIX_Projection = cglmPerspective(fov, FED_SCREEN_RATIO, 0.1, 100.0);
    FED_MATRIX_View = cglmLookAt(
        FED_INPUT_position,
        cglmAddVec3(FED_INPUT_position, direction),
        up
    );
    
    FED_INPUT_lastTime = FED_INPUT_currentTime;
    FED_INPUT_cursorLastXPos = xpos;
    FED_INPUT_cursorLastYPos = ypos;
}


void fedInput_MouseButtonCallback(
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
                if (FED_INPUT_fieldOfView == 45.0) {
                    FED_INPUT_fieldOfView = 360.0;
                    FED_MATRIX_Projection = cglmPerspective(
                                    FED_INPUT_fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
                } else {
                    FED_INPUT_fieldOfView = 45.0;
                    FED_MATRIX_Projection = cglmPerspective(
                                    FED_INPUT_fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                shakePlay(FED_SOUND_GunShot);
                break;
        }
    }
}
