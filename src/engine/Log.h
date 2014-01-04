#pragma once

#include "misc/Singleton.h"
#include "Assert.h"
#include <cstdlib>

class Log_Class
{
public:
    void info(const char* format, ...);
    void warn(const char* format, ...);
    void err(const char* format, ...);
    void printStack(size_t skip = 1, size_t depth = 40);
};

typedef Singleton<Log_Class> Log;

#ifdef _DEBUG
    #define LOGI(...) Log::get().info(__VA_ARGS__)
    #define LOGW(...) Log::get().warn(__VA_ARGS__)
    #define LOGE(...) Log::get().err(__VA_ARGS__)
#else
    #define LOGI(...) {}
    #define LOGW(...) {}
    #define LOGE(...) {}
#endif
