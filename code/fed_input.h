#ifndef FED_INPUT_H
#define FED_INPUT_H

#include "federation.h"

void fedKeyCallback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods);


void fedCursorPosCallback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos);

void fedMouseButtonCallback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods);

void fedScrollCallback(
    GLFWwindow* window,
    double xoffset,
    double yoffset);


#endif
