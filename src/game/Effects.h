#pragma once

#include <misc/Singleton.h>

class Effects_Class
{
    int m_fadeSign;
    int m_fadeFreq;
    int m_fadeTimer;

public:
    Effects_Class();
    virtual ~Effects_Class();

    void startFadeIn(int freq = 500);
    void startFadeOut(int freq = 500);

    void update(int dt);
};

typedef Singleton<Effects_Class> Effects;

#define EFFECTS (Effects::getInstance())
