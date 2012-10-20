#include "Effects.h"
#include "Graphics.h"
#include <Log.h>

Effects_Class::Effects_Class()
{
    m_fadeSign = 0;
    m_fadeTime = 0;
    m_fadeTimer = 0;
    m_fadeColor = 1.0f;
}

Effects_Class::~Effects_Class()
{
}

void Effects_Class::startFadeIn(int time)
{
    if (m_fadeSign != 0)
        return;
    m_fadeTime = time;
    m_fadeTimer = 0;
    m_fadeSign = 1;
    m_fadeColor = 0.0f;
}

void Effects_Class::startFadeOut(int time)
{
    if (m_fadeSign != 0)
        return;
    m_fadeTime = time;
    m_fadeTimer = 0;
    m_fadeSign = -1;
    m_fadeColor = 1.0f;
}

void Effects_Class::update(int dt)
{
    // fade in / out
    if (m_fadeSign != 0)
    {
        static const int freq = 60;
        m_fadeTimer += dt;
        int fadeStepTime = m_fadeTime / freq;
        if (m_fadeTimer >= freq)
        {
            //m_fadeTimer = 0;
            m_fadeTimer -= freq;
            float fadeSpeed = 1.0f / (float)fadeStepTime;
            m_fadeColor += fadeSpeed * m_fadeSign;
            if (m_fadeSign != 0)
            {
                if (m_fadeColor >= 1.0f || m_fadeColor <= 0.0f)
                    m_fadeSign = 0;
            }
        }
    }
}

void Effects_Class::render() const
{
    GRAPHICS.drawRectangle2D(-1.0f, -1.0f, 2.0f, 2.0f,
                             0.0f, 0.0f, 0.0f, 1.0f - m_fadeColor);
}
