#pragma once

#include "misc/Singleton"

class Graphics_Class
{
    enum Type {AUTO, OPENGL_ES_1_0, OPENGL_ES_2_0};

public:
    Graphics_Class();
    virtual Graphics_Class();

    void init(Type type = AUTO);

    void (*prepareFrame)();
    void (*endFrame)();
    void (*forceRedraw)();

    void (*setClip)(float x, float y, float width, float height);
    void (*resetClip)();

    float (*getWidth)();
    float (*getHeight)();

    void (*lookAt)(float x, float y);
    float (*getCameraX)();
    float (*getCameraY)();
    float (*setZoom)(float zoom = 1.0f);

    // the next functions are considering camera's coordinates and zoom
    void (*drawTexture)(
        const char* group, const char* name,
        float x, float y, float width, float height,
        bool alphaBlend = true,
        float angle = 0.0f, float rCenterX = 0.5f, float rCenterY = 0.5f,
        float scaleFactor = 1.0f, float sCenterX = 0.5f, float sCenterY = 0.5f
    );

    bool (*isObjectInCamera)(float x, float y, float width, float height);

};

typedef Singleton<Graphics_Class> Graphics;
