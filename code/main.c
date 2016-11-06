#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "screen.h"
#include "inputs.h"
#include "sounds.h"

#include <clog.h>
#include <cargo.h>

#include <stdio.h>
#include <string.h>

void
glfwErrors(
        int         error,
        const char* description)
{
    clogError("GLFW error n %d: %s", error, description);
}

int
main(int argc, char* argv[])
{
    // maybe start windowed
    char* windowed = cargoFlag("windowed", "FALSE", argc, argv);

    int startWindowed;
    if (strcmp(windowed, "TRUE") == 0)
        startWindowed = 1;
    else
        startWindowed = 0;

    // configure glfw errors
    glfwSetErrorCallback(glfwErrors);

    // init glfw/glew/opengl
    GLFWwindow* win = init_screen(startWindowed);

    // init sounds
    init_sounds();

    // configure inputs
    init_inputs(
        0.0015,         // mouseSpeed
        180.0,          // horizontalAngle
        0.0,            // verticalAngle
        45.0,           // fieldOfView
        (CGLMvec3) {3,0,10},    // position
        (CGLMvec3) {0,0,0}      // direction
    );

    glfwSetInputMode          (win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback        (win, handle_keyboard_inputs_callback);
    glfwSetMouseButtonCallback(win, handle_mouse_button_inputs_callback);
    glfwSetCursorPosCallback  (win, handle_cursor_position_callback);
    glfwSetScrollCallback     (win, handle_scroll_inputs_callback);

    // begin to loop
    while (!glfwWindowShouldClose(win))
    {
        handle_real_time_key_inputs();
        update_screen();
    }

    // cleanup
    cleanup_screen();
    shakeTerminate();

    return 0;
}
