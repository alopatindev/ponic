#pragma once

#include "misc/Singleton"
#include "GraphicsDevice.h"
#include "Texture.h" ???

class GraphicsClass
{
    GraphicsDevice* device;

public:
    void init();

    void prepareFrame() const;
    void endFrame() const;
    void forceRedraw() const;

    void drawTexture(const Texture* texture,
                     float x, float y, float width, float height) const;
    void drawTexture(const Texture* texture,
                     float x, float y, float width, float height,
                     float angle,
                     float centerOffsetX, float centerOffsetY) const;

    void drawTexture(const char* textureGroup,
                     const char* textureName,
                     float x, float y, float width, float height) const;
    void drawTexture(const char* textureGroup,
                     const char* textureName,
                     float x, float y, float width, float height,
                     float angle,
                     float centerOffsetX, float centerOffsetY) const;

    void setClip(float x, float y, float width, float height) const;
    void resetClip() const;

    float getWidth() const;
    float getHeight() const;
};

typedef Singleton<GraphicsClass> Graphics;
