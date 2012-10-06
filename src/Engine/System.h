#pragma once

#include "misc/Singleton.h"

class System_Class
{
    int m_dt;

public:
    System_Class();
    virtual ~System_Class();

    int getDt();
    void setDt(int dt);
};

typedef Singleton<System_Class> System;

#define SYSTEM (System::getInstance())
