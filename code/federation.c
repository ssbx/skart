
/**
 * @file federation.c
 * @brief Federation FPS
 * @version 0.1
 *
 * Simple FPS game created for learning various C/C++ tools and real time
 * rendering.
 *
 */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "federation.h"
#include "fed_gl.h"
#include "fed_log.h"
#include "fed_input.h"

/**
 * @fn int main(int argc, char* argv)
 * @brief Federation main loop.
 *
 * @return 0
 */
int main(int argc, char* argv) {

    glfwSetErrorCallback(fed_log_errorCallback);
    fed_gl_init();
    glfwSetKeyCallback(fed_window, fed_input_keyCallback);

    while (!glfwWindowShouldClose(fed_window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(fed_window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(fed_window);
        glfwPollEvents();
    }

    fed_gl_cleanup();

    return 0;

}
