#pragma once

#include "misc/Singleton.h"
#include "Log.h"
#include <map>
#include <queue>
#include <string>

class Graphics_Class
{
    float m_width;
    float m_height;

    static const float ZNEAR = 0.1f;
    static const float ZFAR = 10.0f;

    float m_perspMatrix[16];
    float m_hfar;
    float m_wfar;

    struct Command
    {
        enum {Rectangle2D, Image2D, Image3D} type;
        std::string group;
        std::string name;
        float x;
        float y;
        float z;
        float width;
        float height;
        float angle;
        float centerX;
        float centerY;
        float scaleFactor;
        float color[3];
        float opacity;
        bool depth;
    };

    typedef std::map< float, std::queue<Command*> > BufferType;
    BufferType m_imagesBuffer;
    BufferType m_imagesBufferTransparent;

public:
    Graphics_Class();
    virtual ~Graphics_Class();

    void init();

    void startFrame();
    void endFrame();

    void forceRedraw();

    void setClip(float x, float y, float width, float height);
    void resetClip();

    void onReshape(int width, int height);

    float getWidth();
    float getHeight();

    float getHfar() { return m_hfar; }
    float getWfar() { return m_wfar; }

    // TODO: where and how should we load the font? ResourceManager?
    // how and where should we select font size for different display sizes?
    void drawText2D(const char* fontName, int size,
                    const char* text,
                    float x, float y,
                    float r, float g, float b,
                    bool outline = false);

    void drawRectangle2D(float x, float y, float width, float height,
                         float r, float g, float b, float opacity,
                         bool onTop = false);

    void drawImage2D(
        const char* group, const char* name,
        float x, float y, float width, float height,
        float angle = 0.0f, float centerX = 0.5f, float centerY = 0.5f,
        float scaleFactor = 1.0f,
        float opacity = 1.0f,
        bool onTop = false
    );

    // the next functions are considering camera's coordinates and zoom
    void drawImage3D(
        const char* group, const char* name,
        float x, float y, float z,
        float width, float height,
        float angle = 0.0f, float centerX = 0.5f, float centerY = 0.5f,
        float scaleFactor = 1.0f,
        float opacity = 1.0f
    );

private:
    void flushRectangle2D(const Command* command);
    void flushImage2D(const Command* command);
    void flushImage3D(const Command* command);
    void flushGeomerty(BufferType & buffer);
    void buildPerspProjMat(float *m, float fov,
                           float aspect, float znear, float zfar);
};

typedef Singleton<Graphics_Class> Graphics;

#define GRAPHICS (Graphics::getInstance())
