#ifndef FEDINPUT_H
#define FEDINPUT_H

#include <fedCommon.h>

void fedInput_KeyCallback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods);


void fedInput_CursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos);

void fedInput_MouseButtonCallback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods);

void fedInput_ScrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset);


#endif
