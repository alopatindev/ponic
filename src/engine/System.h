#pragma once

#include "misc/Singleton.h"
#include <string>

class System_Class
{
    std::string m_resourcesPath;

public:
    System_Class();
    virtual ~System_Class();

    const std::string& getResourcesPath();
    void setResourcesPath(const std::string& resourcesPath);
};

typedef Singleton<System_Class> System;

#define SYSTEM (System::get())
