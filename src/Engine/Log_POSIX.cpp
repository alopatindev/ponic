#include "Log.h"
#include <cstdio>
#include <cstdarg>

#ifdef __linux__
extern "C"
{
    #include <execinfo.h>
}
#endif

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
    std::fflush(stdout);
    va_end(args);
}

void Log_Class::warn(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    printf("\033[01;33m%s\033[00m\n", buffer);  // yellow
    std::fflush(stdout);
    va_end(args);
}

void Log_Class::err(const char* format, ...)
{
    char buffer[BUFFER_SIZE];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, BUFFER_SIZE, format, args);
    printf("\033[01;31m%s\n", buffer);  // red
    std::fflush(stdout);
    va_end(args);

    printStack(2);
}

void Log_Class::printStack(size_t skip, size_t depth)
{
#ifdef __linux__
    // NOTE: you need to add "-rdynamic" to your CXXFLAGS to see backtraces
    void* bbuffer[depth];
    size_t bsize = backtrace(bbuffer, depth);
    char** btext = backtrace_symbols(bbuffer, bsize);
    for (size_t i = skip; i < bsize; ++i)
    {
        printf("\033[01;31m%s\n", btext[i]);
        std::fflush(stdout);
    }
    printf("\033[00m\n\n");
    std::fflush(stdout);
    std::free(btext);
#endif
}

#undef BUFFER_SIZE
