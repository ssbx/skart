#ifndef FED_LOG_H
#define FED_LOG_H

void fed_log_errorCallback(int error, const char* description);
void fed_log_printError(const char* message);
void fed_log_printWarning(const char* message);
void fed_log_printInfo(const char* message);
void fed_log_printDebug(const char* message);

#endif
