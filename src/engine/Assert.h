#pragma once

#include "Log.h"

#ifdef _DEBUG
    #define ASSERT(expr, comment, ...) \
        { \
            if (!(expr)) \
            { \
                std::string filename(__FILE__); \
                size_t offset = filename.find("ponic/src"); \
                if (offset != std::string::npos) \
                    filename = filename.substr(offset); \
                LOGE("\n%s:%d\nASSERT: %s \"" comment "\"\n", \
                    filename.c_str(), \
                    __LINE__, \
                    __STRING(expr), \
                    ##__VA_ARGS__ \
                ); \
                Log::get().printStack(); \
                /*exit(1);*/\
            } \
        }
#else
    #define ASSERT(expr, comment, ...) {}
#endif
