#ifndef FEDERATION_H
#define FEDERATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>


GLFWwindow *fed_window; //< Federation main window

int SND_Intro;
int SND_GunShot;

CGLMmat4 FED_ProjectionMatrix;
CGLMmat4 FED_ViewMatrix;

#endif // FEDERATION_H
