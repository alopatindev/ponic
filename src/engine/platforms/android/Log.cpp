#include "Log.h"
#include <cstdio>
#include <cstdarg>

extern "C"
{
    #include <android/log.h>
}

// TODO: print to graphic screen if ready
// TODO: write to log file

#define BUFFER_SIZE 256
#define LOG_TAG "Ponic"

void Log_Class::info(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, buffer);
    va_end(args);
}

void Log_Class::warn(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    __android_log_print(ANDROID_LOG_WARN, LOG_TAG, buffer);
    va_end(args);
}

void Log_Class::err(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, buffer);
    va_end(args);
}

void Log_Class::printStack(size_t skip, size_t depth)
{
}

#undef BUFFER_SIZE
#undef LOG_TAG
