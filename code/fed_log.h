#ifndef FED_LOG_H
#define FED_LOG_H

#include <stdio.h>


/**
 * @file fed_log.h
 * @brief Federation logging utilities.
 */


/**
 * @fn fedErrorCallback(int error, const char* description)
 * @brief Error callback used by GLFW. Print ERROR_CALLBACK message to STDERR.
 */
void fedErrorCallback(
    int         error,
    const char* description);

/**
 * @fn fedErrorMsg(const char* message)
 * @brief Print ERROR message to STDERR.
 */
void fedErrorMsg(const char* message);

/**
 * @fn fedWarningMsg(const char* message)
 * @brief Print WARNING message to STDOUT.
 */
void fedWarningMsg(const char* message);

/**
 * @fn fedInfoMsg(const char* message)
 * @brief Print INFO message to STDOUT.
 */
void fedInfoMsg(const char* message);

/**
 * @fn fedDebugMsg(const char* message)
 * @brief Print DEBUG message to STDOUT.
 */
void fedDebugMsg(const char* message);


#endif
