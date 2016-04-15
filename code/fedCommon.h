#ifndef FEDCOMMON_H
#define FEDCOMMON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>


GLFWwindow *FED_Window; //< Federation main window

int FED_SOUND_Intro;
int FED_SOUND_GunShot;

float FED_SCREEN_HEIGHT;
float FED_SCREEN_WIDTH;
float FED_SCREEN_RATIO;

CGLMmat4 FED_MVP;

#endif // FEDCOMMON_H
