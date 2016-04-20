#ifndef FINPUT_H
#define FINPUT_H

#include "f_common.h"

#include <shake.h>
#include <cglm.h>
#include <clog.h>

#include <stdio.h>

static double cursorLastXPos;
static double cursorLastYPos;
static float mouseSpeed;
static float horizontalAngle;
static float verticalAngle;
static float fieldOfView;
static float fieldOfView;
static double mouseLastMove;
static double keyLastMove;
CGLMvec3 position;
CGLMvec3 direction;
CGLMmat4 proj;
CGLMmat4 view;
CGLMmat4 model;
CGLMvec3 up;


void FInput_Init(
    float mouseSpeed_v,
    float horizontalAngle_v,
    float verticalAngle_v,
    float fieldOfView_v,
    CGLMvec3 position_v,
    CGLMvec3 direction_v)
{

    mouseSpeed      = mouseSpeed_v;
    horizontalAngle = horizontalAngle_v;
    verticalAngle   = verticalAngle_v;
    fieldOfView     = fieldOfView_v;
    position        = position_v;
    direction       = direction_v;
    mouseLastMove  = keyLastMove = glfwGetTime();
    glfwGetCursorPos(FED_Window, &cursorLastXPos, &cursorLastYPos);
   
    model = (CGLMmat4) cglmMat4(1);
    up = (CGLMvec3) {0,1,0};
    
    proj  = cglmPerspective(fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
    view  = cglmLookAt(position, direction, up);
    
    FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
   
}

void FInput_GetImmediateKeyInputs()
{

    if (glfwGetKey(FED_Window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position.z -= 1;
        view    = cglmLookAt(position, direction, up);
        FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
        return;
    }
    
    if (glfwGetKey(FED_Window, GLFW_KEY_S) == GLFW_PRESS) {
        position.z += 1;
        view    = cglmLookAt(position, direction, up);
        FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
        return;
    }
}


void FInput_KeyCallback(
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
    
    /*
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glfwIconifyWindow(FED_Window);
    }
    */
    

    
}

void FInput_ScrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset)
{
}

void FInput_CursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos)
{
    
    double now       = glfwGetTime();
    double deltaTime = now - mouseLastMove;
    clogInfo("Delta %f\n", deltaTime);
    
    clogInfo("pos %f %f \n", cursorLastXPos, cursorLastYPos);
    horizontalAngle += mouseSpeed * (cursorLastXPos - xpos);
    verticalAngle   += mouseSpeed * (cursorLastYPos - ypos);
    
    direction = (CGLMvec3) {
        cos(verticalAngle) * sin(horizontalAngle), 
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    };
    
    CGLMvec3 right = {
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    };
    
    up = cglmCross(right, direction);
    
    
    proj = cglmPerspective(fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
    view = cglmLookAt(
        position,
        cglmAddVec3(position, direction),
        up
    );
    
    mouseLastMove  = now;
    cursorLastXPos = xpos;
    cursorLastYPos = ypos;
    
    FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
    
}


void FInput_MouseButtonCallback(
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
                if (fieldOfView == 45.0) {
                    fieldOfView = 360.0;
                    proj = cglmPerspective(fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
                    FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
                } else {
                    fieldOfView = 45.0;
                    proj = cglmPerspective(fieldOfView, FED_SCREEN_RATIO, 0.1, 100.0);
                    FED_MVP = cglmMultMat4(cglmMultMat4(proj, view), model);
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                shakePlay(FED_SOUND_GunShot);
                break;
        }
    }
}

#endif
