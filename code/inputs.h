#ifndef INPUTS_H
#define INPUTS_H

#include "sounds.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm.h>

#include <clog.h>

// view
static CGLMmat4 VIEW;
static CGLMvec3 VIEW_POSITION;
static CGLMvec3 VIEW_DIRECTION;
static CGLMmat4 VIEW_PROJECTION;
static CGLMmat4 VIEW_MODEL;
static CGLMvec3 VIEW_UP;

// for computing TIME_DELTA
static double TIME_LAST;
static double TIME_DELTA;

// mouse controls things
static double CURSOR_X;
static double CURSOR_Y;
static float  MOUSE_SPEED;
static float  ANGLE_HORIZONTAL;
static float  ANGLE_VERTICAL;
static float  FIELD_OF_VIEW;

// keyboard move speed
static double MOVE_SPEED;

// extern
extern float       FED_screenRatio;
extern GLFWwindow* MAIN_WINDOW;
extern CGLMmat4    FED_mvp;

/**
 * Called at startup
 */
void
init_inputs(
        float    mouse_speed,
        float    move_speed,
        float    angle_horizontal,
        float    angle_vertical,
        float    field_of_view,
        CGLMvec3 position,
        CGLMvec3 direction)
{
    ANGLE_HORIZONTAL = angle_horizontal;
    ANGLE_VERTICAL   = angle_vertical;
    FIELD_OF_VIEW    = field_of_view;
    VIEW_POSITION    = position;
    VIEW_DIRECTION   = direction;
    MOUSE_SPEED      = mouse_speed;
    MOVE_SPEED       = move_speed;
    TIME_LAST        = glfwGetTime();
    TIME_DELTA       = 0.0f;

    glfwGetCursorPos(MAIN_WINDOW, &CURSOR_X, &CURSOR_Y);

    VIEW_MODEL = cglmMat4(1);
    VIEW_UP    = (CGLMvec3) {0,1,0};

    VIEW_PROJECTION  = cglmPerspective(
            FIELD_OF_VIEW,
            FED_screenRatio,
            0.1,
            100.0);

    VIEW  = cglmLookAt(VIEW_POSITION, VIEW_DIRECTION, VIEW_UP);
}

/**
 * Handle real time key inputs because GLFW handle
 * simple key press/repeat/release
 */
void
handle_real_time_key_inputs()
{
    if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_W) == GLFW_PRESS) {
        VIEW_POSITION.z -= MOVE_SPEED * TIME_DELTA;
    } else if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_S) == GLFW_PRESS) {
        VIEW_POSITION.z += MOVE_SPEED * TIME_DELTA;
    } else if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_H) == GLFW_PRESS) {
        VIEW_POSITION.x -= MOVE_SPEED * TIME_DELTA;
    } else if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_L) == GLFW_PRESS) {
        VIEW_POSITION.x += MOVE_SPEED * TIME_DELTA;
    }
}

/**
 * GLFW callback used by glfwSetKeyCallback()
 */
void
handle_keyboard_inputs_callback(
        GLFWwindow* window,
        int         key,
        int         scancode,
        int         action,
        int         mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }

    /*
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glfwIconifyWindow(FED_window);
    }
    */
}

/**
 * GLFW callback used by glfwSetScrollCallback()
 */
void
handle_scroll_inputs_callback(
        GLFWwindow* window,
        double xoffset,
        double yoffset)
{
}

/**
 * GLFW callback used by glfwSetCursorPosCallback()
 */
void
handle_cursor_position_callback(
        GLFWwindow* window,
        double      xpos,
        double      ypos)
{
    ANGLE_HORIZONTAL += MOUSE_SPEED * (CURSOR_X - xpos);
    ANGLE_VERTICAL   += MOUSE_SPEED * (CURSOR_Y - ypos);

    VIEW_DIRECTION = (CGLMvec3) {
        cos(ANGLE_VERTICAL) * sin(ANGLE_HORIZONTAL),
        sin(ANGLE_VERTICAL),
        cos(ANGLE_VERTICAL) * cos(ANGLE_HORIZONTAL)
    };

    VIEW_PROJECTION = cglmPerspective(FIELD_OF_VIEW, FED_screenRatio, 0.1, 100.0);

    CURSOR_X = xpos;
    CURSOR_Y = ypos;

}

/**
 * GLFW callback used by glfwSetMouseButtonCallback()
 */
void
handle_mouse_button_inputs_callback(
        GLFWwindow* window,
        int         button,
        int         action,
        int         mods)
{
    if (action == GLFW_PRESS)
        switch(button) {
            case GLFW_MOUSE_BUTTON_LEFT:
                play_sound(FED_SOUND_GunShot);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                play_sound(FED_SOUND_GunShot);
                if (FIELD_OF_VIEW == 45.0) {
                    FIELD_OF_VIEW = 360.0;
                    VIEW_PROJECTION = cglmPerspective(
                                    FIELD_OF_VIEW, FED_screenRatio, 0.1, 100.0);
                } else {
                    FIELD_OF_VIEW = 45.0;
                    VIEW_PROJECTION = cglmPerspective(
                                    FIELD_OF_VIEW, FED_screenRatio, 0.1, 100.0);
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                play_sound(FED_SOUND_GunShot);
                break;
        }
}

/**
 * Used to process all user inputs. Used from screen.h after rendering.
 */
void
poll_events_input()
{
    double time_now;
    CGLMvec3 right;

    // Set TIME_DELTA value
    time_now = glfwGetTime();
    TIME_DELTA = (float) time_now - (float) TIME_LAST;
    TIME_LAST  = (float) time_now;

    // handle real_time_key user inputs
    handle_real_time_key_inputs();

    // Mouse position/buttons and normal key inputsare handled by glfw callbacks
    glfwPollEvents();

    // recalculate new MVP
    right = (CGLMvec3) {
        sin(ANGLE_HORIZONTAL - 3.14f/2.0f),
        0,
        cos(ANGLE_HORIZONTAL - 3.14f/2.0f)
    };

    VIEW_UP = cglmCross(right, VIEW_DIRECTION);
    VIEW    = cglmLookAt(
            VIEW_POSITION,
            cglmAddVec3(VIEW_DIRECTION, VIEW_POSITION),
            VIEW_UP);
    FED_mvp = cglmMultMat4(cglmMultMat4(VIEW_PROJECTION, VIEW), VIEW_MODEL);

    return;
}

#endif // INPUTS_H


