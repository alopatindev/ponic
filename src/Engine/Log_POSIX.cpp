#include "Log.h"
#include <cstdio>
#include <cstdarg>

#define BUFFER_SIZE 256

// TODO: Android: run it's ndk log function and
// print to graphic screen if ready

// TODO: write to log file

void Log_Class::info(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    printf("\033[01;37m%s\033[00m\n", buffer);  // white
    va_end(args);
}

void Log_Class::warn(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    printf("\033[01;33m%s\033[00m\n", buffer);  // yellow
    va_end(args);
}

void Log_Class::err(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    printf("\033[01;31m%s\033[00m\n", buffer);  // red
    va_end(args);

    // print backtrace(3) if possible
}

#undef BUFFER_SIZE
