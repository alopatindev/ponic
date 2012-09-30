#pragma once

#include "misc/Singleton.h"

class Graphics_Class
{
public:
    Graphics_Class();
    virtual ~Graphics_Class();

    void init();

    void prepareFrame();
    void endFrame();
    void forceRedraw();

    void setClip(float x, float y, float width, float height);
    void resetClip();

    float getWidth();
    float getHeight();

    void lookAt(float x, float y);
    float getCameraX();
    float getCameraY();
    float setZoom(float zoom = 1.0f);

    // TODO: where and how should we load the font? ResourceManager?
    // how and where should we select font size for different display sizes?
    void drawText(float x, float y, const char* text,
                  int size, const char* font);

    // the next functions are considering camera's coordinates and zoom
    void drawImage(
        const char* group, const char* name,
        float x, float y, float width, float height,
        float angle = 0.0f, float rCenterX = 0.5f, float rCenterY = 0.5f,
        float scaleFactor = 1.0f, float sCenterX = 0.5f, float sCenterY = 0.5f
    );

    bool isObjectInCamera(float x, float y, float width, float height);
};

typedef Singleton<Graphics_Class> Graphics;

#define GRAPHICS (Graphics::getInstance())
