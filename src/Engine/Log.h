#pragma once

#include "misc/Singleton.h"

class Log_Class
{
public:
    void info(const char* format, ...);
    void warn(const char* format, ...);
    void err(const char* format, ...);
};

typedef Singleton<Log_Class> Log;

#ifdef _DEBUG
    #define LOGI(...) Log::getInstance().info(__VA_ARGS__);
    #define LOGW(...) Log::getInstance().warn(__VA_ARGS__);
    #define LOGE(...) Log::getInstance().err(__VA_ARGS__);
#else
    #define LOGI(...) if (false)
    #define LOGW(...) if (false)
    #define LOGE(...) if (false)
#endif
