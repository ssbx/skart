#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void fed_log_print(const char* head, const char* body, FILE *out);


void fed_log_errorCallback(int error, const char* message)
{
    fed_log_print("ERROR_CALLBACK: ", message, stderr);
}


void fed_log_printError(const char* message)
{
    fed_log_print("ERROR: ", message, stderr);
}


void fed_log_printWarning(const char* message)
{
    fed_log_print("WARNING: ", message, stderr);
}


void fed_log_printInfo(const char* message)
{
    fed_log_print("INFO: ", message, stdout);
}

void fed_log_printDebug(const char* message)
{
#ifdef DEBUG
    fed_log_print("DEBUG: ", message, stdout);
#endif
}

static void fed_log_print(const char* head, const char* body, FILE* out)
{

    char formated[sizeof(head) + sizeof(body)];

    strcpy(formated, head);
    strcat(formated, body);
    strcat(formated, "\n");

    fputs(formated, out);

}
