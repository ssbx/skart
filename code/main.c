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

void
countFPS(int* frame_count, double* last_time)
{
    double current_time;
    *frame_count += 1;
    current_time = glfwGetTime();
    if (current_time - *last_time >= 1.0f) {
        clogInfo("%i FPS", *frame_count);
        clogInfo("%f ms/frame \n", 1000.0f/ (double) *frame_count);
        *frame_count = 0;
        *last_time += 1.0f;
    }

}

int
main(int argc, char* argv[])
{
    char* windowed;
    int startWindowed, frame_count;
    double last_time, current_time;
    GLFWwindow* win;

    // maybe start windowed
    windowed = cargoFlag("windowed", "FALSE", argc, argv);
    startWindowed;
    if (strcmp(windowed, "TRUE") == 0)
        startWindowed = 1;
    else
        startWindowed = 0;

    // configure glfw errors
    glfwSetErrorCallback(glfwErrors);

    // init glfw/glew/opengl
    win = init_screen(startWindowed);

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

    frame_count = 0;
    last_time = glfwGetTime();

    // begin to loop
    while (!glfwWindowShouldClose(win))
    {
        update_screen();
        countFPS(&frame_count, &last_time);
    }

    // cleanup
    cleanup_screen();
    shakeTerminate();

    return 0;
}
