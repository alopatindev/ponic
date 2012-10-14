#pragma once

#include "Log.h"

#ifdef _DEBUG
    #define ASSERT(expr, comment, ...) \
        { \
            if (!(expr)) \
            { \
                size_t offset = std::string(__FILE__).find("ponic/src"); \
                if (offset == std::string::npos) \
                    offset = 0; \
                LOGE("\n%s:%d\nASSERT: %s \"" comment "\"\n", \
                    __FILE__ + offset, \
                    __LINE__, \
                    __STRING(expr), \
                    ##__VA_ARGS__ \
                ); \
                Log::getInstance().printStack(); \
                exit(1);\
            } \
        }
#else
    #define ASSERT(expr) {}
#endif
