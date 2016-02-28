#include "fed_log.h"
#include <stdlib.h>
#include <string.h>


static void FLog(
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


void FErrorCallback(
    int         error,
    const char* message)
{
    FLog("ERROR_CALLBACK: ", message, stderr);
}


void FErrorMsg(const char* message)
{
    FLog("ERROR: ", message, stderr);
}


void FWarningMsg(const char* message)
{
    FLog("WARNING: ", message, stdout);
}


void FInfoMsg(const char* message)
{
    FLog("INFO: ", message, stdout);
}

void FDebugMsg(const char* message)
{
#ifdef FEDERATION_DEBUG
    FLog("DEBUG: ", message, stdout);
#endif
}

