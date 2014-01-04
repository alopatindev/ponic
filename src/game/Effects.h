#pragma once

#include <misc/Singleton.h>

class Effects_Class
{
    int m_fadeSign;
    int m_fadeTime;
    int m_fadeTimer;
    float m_fadeColor;

public:
    Effects_Class();
    virtual ~Effects_Class();

    void startFadeIn(int time = 3000);
    void startFadeOut(int time = 3000);

    void update(int dt);
    void render() const;
};

typedef Singleton<Effects_Class> Effects;

#define EFFECTS (Effects::get())
