#ifndef FEDERATION_H
#define FEDERATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>


GLFWwindow *FED_Window; //< Federation main window

int FED_SOUND_Intro;
int FED_SOUND_GunShot;

CGLMmat4 FED_MATRIX_Projection;
CGLMmat4 FED_MATRIX_View;

double   INPUT_lastTime;
double   INPUT_currentTime;
float    INPUT_mouseSpeed;
float    INPUT_deltaTime;
float    INPUT_horizontalAngle;
float    INPUT_verticalAngle;
float    INPUT_fieldOfView;
CGLMvec3 INPUT_position;

float SCREEN_HEIGHT;
float SCREEN_WIDTH;
float SCREEN_RATIO;

#endif // FEDERATION_H
