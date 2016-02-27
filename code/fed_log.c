#include "fed_log.h"
#include <stdlib.h>
#include <string.h>


static void FLog_print(
    const char* head,
    const char* body,
    FILE*       out)
{

    char formated[strlen(head) + strlen(body) + 2];

    strcpy(formated, head);
    strcat(formated, body);
    strcat(formated, "\n");

    fputs(formated, out);

}


void FLog_errorCallback(
    int         error,
    const char* message)
{
    FLog_print("ERROR_CALLBACK: ", message, stderr);
}


void FLog_errorMsg(const char* message)
{
    FLog_print("ERROR: ", message, stderr);
}


void FLog_warningMsg(const char* message)
{
    FLog_print("WARNING: ", message, stdout);
}


void FLog_infoMsg(const char* message)
{
    FLog_print("INFO: ", message, stdout);
}

void FLog_debugMsg(const char* message)
{
#ifdef FEDERATION_DEBUG
    FLog_print("DEBUG: ", message, stdout);
#endif
}

