#ifndef FEDCOMMON_H
#define FEDCOMMON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>


GLFWwindow *FED_Window; //< Federation main window

int FED_SOUND_Intro;
int FED_SOUND_GunShot;

CGLMmat4 FED_MATRIX_Projection;
CGLMmat4 FED_MATRIX_View;

double   FED_INPUT_cursorLastXPos;
double   FED_INPUT_cursorLastYPos;
double   FED_INPUT_lastTime;
double   FED_INPUT_currentTime;
float    FED_INPUT_mouseSpeed;
float    FED_INPUT_deltaTime;
float    FED_INPUT_horizontalAngle;
float    FED_INPUT_verticalAngle;
float    FED_INPUT_fieldOfView;
CGLMvec3 FED_INPUT_position;

float FED_SCREEN_HEIGHT;
float FED_SCREEN_WIDTH;
float FED_SCREEN_RATIO;

#endif // FEDCOMMON_H
