#pragma once

#include "misc/Singleton.h"
#include "Log.h"

class Graphics_Class
{
    float m_aspect;
    float m_color;

public:
    Graphics_Class();
    virtual ~Graphics_Class();

    void init();

    void startFrame();
    void endFrame();

    void forceRedraw();

    void setColor(float color)
    {
        if (color <= 0.0f)
            color = 0.0f;
        else if (color >= 1.0f)
            color = 1.0f;
        //LOGI("setColor(%3.3f)", color);
        m_color = color;
    }

    float getColor()
    {
        return m_color;
    }

    void setClip(float x, float y, float width, float height);
    void resetClip();

    void onReshape(int width, int height);

    float getWidth();
    float getHeight();

    // TODO: where and how should we load the font? ResourceManager?
    // how and where should we select font size for different display sizes?
    void drawText2D(const char* fontName, int size,
                    const char* text,
                    float x, float y,
                    float r, float g, float b,
                    bool outline = false);

    void drawImage2D(
        const char* group, const char* name,
        float x, float y, float width, float height,
        float angle = 0.0f, float centerX = 0.5f, float centerY = 0.5f,
        float scaleFactor = 1.0f
    );

    // the next functions are considering camera's coordinates and zoom
    void drawImage3D(
        const char* group, const char* name,
        float x, float y, float z,
        float width, float height,
        float angle = 0.0f, float centerX = 0.5f, float centerY = 0.5f,
        float scaleFactor = 1.0f
    );
};

typedef Singleton<Graphics_Class> Graphics;

#define GRAPHICS (Graphics::getInstance())
