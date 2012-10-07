#pragma once

#include "misc/Singleton.h"

class FontManager_Class
{
public:
    FontManager_Class();
    virtual ~FontManager_Class();

    void loadFont(const char* filename, ...);
    void bindFont(const char* name, int size);

    void freeFont(const char* name);
    void freeAllFonts();
};

typedef Singleton<FontManager_Class> FontManager;
