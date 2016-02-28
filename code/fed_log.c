#include "fed_log.h"
#include <stdlib.h>
#include <string.h>


static void fedLog(
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


void fedErrorCallback(
    int         error,
    const char* message)
{
    fedLog("ERROR_CALLBACK: ", message, stderr);
}


void fedErrorMsg(const char* message)
{
    fedLog("ERROR: ", message, stderr);
}


void fedWarningMsg(const char* message)
{
    fedLog("WARNING: ", message, stdout);
}


void fedInfoMsg(const char* message)
{
    fedLog("INFO: ", message, stdout);
}

void fedDebugMsg(const char* message)
{
#ifdef FEDERATION_DEBUG
    fedLog("DEBUG: ", message, stdout);
#endif
}

