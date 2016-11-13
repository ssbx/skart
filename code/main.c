#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "screen.h"
#include "sounds.h"
#include "inputs.h"

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
        0.0005f,                        // mouse_speed
        0.001f,                         // move_speed
        180.0f,                         // horizontal_angle
        0.0f,                           // vertical_angle
        45.0f,                          // field_of_view
        (CGLMvec3) {3.0f,0.0f,10.0f},   // position
        (CGLMvec3) {0.0f,0.0f,0.0f}     // direction
    );

    glfwSetInputMode          (win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback        (win, handle_keyboard_inputs_callback);
    glfwSetMouseButtonCallback(win, handle_mouse_button_inputs_callback);
    glfwSetCursorPosCallback  (win, handle_cursor_position_callback);
    glfwSetScrollCallback     (win, handle_scroll_inputs_callback);

    // begin to loop
    while (!glfwWindowShouldClose(win))
    {
        update_screen();
    }

    // cleanup
    cleanup_screen();
    shakeTerminate();

    return 0;
}
