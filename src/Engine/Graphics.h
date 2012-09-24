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

    void (*drawTexture)(
        const char* group, const char* name,
        float x, float y, float width, float height,
        bool alphaBlend = true,
        float angle = 0.0f, float rotX = 0.5f, float rotY = 0.5f,
        float scaleFactor = 1.0f, float scaleX = 0.5f, float scaleY = 0.5f
    );

    void (*setClip)(float x, float y, float width, float height);
    void (*resetClip)();

    float (*getWidth)();
    float (*getHeight)();
};

typedef Singleton<Graphics_Class> Graphics;
