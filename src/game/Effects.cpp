#include "Effects.h"
#include "Graphics.h"
#include <Log.h>

Effects_Class::Effects_Class()
{
    m_fadeSign = 0;
    m_fadeFreq = 30;
    m_fadeTimer = 0;
}

Effects_Class::~Effects_Class()
{
}

void Effects_Class::startFadeIn(int freq)
{
    if (m_fadeSign != 0)
        return;
    m_fadeFreq = freq;
    m_fadeSign = 1;
    m_fadeTimer = 0;
    GRAPHICS.setColor(0.0f);
}

void Effects_Class::startFadeOut(int freq)
{
    if (m_fadeSign != 0)
        return;
    m_fadeFreq = freq;
    m_fadeSign = -1;
    m_fadeTimer = 0;
    GRAPHICS.setColor(1.0f);
}

void Effects_Class::update(int dt)
{
    // fade in / out
    if (m_fadeSign != 0)
    {
        m_fadeTimer += dt;
        if (m_fadeTimer >= m_fadeFreq)
        {
            GRAPHICS.setColor(GRAPHICS.getColor() + 0.1 * m_fadeSign);
            if (m_fadeSign != 0)
            {
                float c = GRAPHICS.getColor();
                if (c >= 1.0f || c <= 0.0f)
                    m_fadeSign = 0;
            }
        }
    }
}
