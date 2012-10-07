#include "FontManager.h"
#include "Log.h"
#include <cstdarg>

FontManager_Class::FontManager_Class()
{
}

FontManager_Class::~FontManager_Class()
{
}

void FontManager_Class::loadFont(const char* filename, ...)
{
    va_list args;
    va_start(args, filename);

    for (int i = 0;;)
    {
        i = va_arg(args, int);
        if (i == 0)
            break;
        LOGI("loading font %s with size %d", filename, i);
    }

    va_end(args);
}

void FontManager_Class::bindFont(const char* name, int size)
{
}

void FontManager_Class::freeFont(const char* name)
{
}

void FontManager_Class::freeAllFonts()
{
}
