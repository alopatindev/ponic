#include "Graphics.h"
#include <cstring>
#include "Camera.h"
#include <glm/glm.hpp>

Graphics_Class::Graphics_Class()
    : m_width(0)
    , m_height(0)
    , m_hfar(0)
    , m_wfar(0)
{
    std::memset(m_perspMatrix, 0, sizeof(m_perspMatrix));
}

Graphics_Class::~Graphics_Class()
{
}

void Graphics_Class::flushGeomerty(BufferType & buffer)
{
    for (BufferType::iterator it = buffer.begin();
         it != buffer.end();
         ++it)
    {
        while (!it->second.empty())
        {
            Command* c = it->second.front();

            switch (c->type)
            {
            case Command::Rectangle2D:
                flushRectangle2D(c);
                break;
            case Command::Image2D:
                flushImage2D(c);
                break;
            case Command::Image3D:
                flushImage3D(c);
                break;
            default:
                break;
            }

            delete c;
            it->second.pop();
        }
    }
}

float Graphics_Class::getWidth()
{
    return m_width;
}

float Graphics_Class::getHeight()
{
    return m_height;
}

void Graphics_Class::drawRectangle2D(float x, float y,
                                     float width, float height,
                                     float r, float g, float b, float opacity,
                                     bool onTop)
{
    if (opacity == 0.0f)
        return;

    float z = 0.0f;
    Command* c = new Command;

    c->type = Command::Rectangle2D;
    c->group = "";
    c->name = "";
    c->x = x;
    c->y = y;
    c->z = z;
    c->width = width;
    c->height = height;
    c->angle = 0.0f;
    c->centerX = 0.5f;
    c->centerY = 0.5f;
    c->scaleFactor = 1.0f;
    c->color[0] = r;
    c->color[1] = g;
    c->color[2] = b;
    c->opacity = opacity;
    c->depth = !onTop;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::drawImage2D(
    const char* group, const char* name,
    float x, float y, float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor,
    float opacity,
    bool onTop
)
{
    if (opacity == 0.0f)
        return;

    float z = 0.0f;
    Command* c = new Command;

    c->type = Command::Image2D;
    c->group = std::string(group);
    c->name = std::string(name);
    c->x = x;
    c->y = y;
    c->z = z;
    c->width = width;
    c->height = height;
    c->angle = angle;
    c->centerX = centerX;
    c->centerY = centerY;
    c->scaleFactor = scaleFactor;
    c->color[0] = 0.0f;
    c->color[1] = 0.0f;
    c->color[2] = 0.0f;
    c->opacity = opacity;
    c->depth = !onTop;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::drawImage3D(
    const char* group, const char* name,
    float x, float y, float z,
    float width, float height,
    float angle, float centerX, float centerY,
    float scaleFactor,
    float opacity
)
{
    if (!CAMERA.isVisible(x, y, width, height))
        return;

    if (opacity == 0.0f)
        return;

    Command* c = new Command;

    c->type = Command::Image3D;
    c->group = std::string(group);
    c->name = std::string(name);
    c->x = x;
    c->y = y;
    c->z = z;
    c->width = width;
    c->height = height;
    c->angle = angle;
    c->centerX = centerX;
    c->centerY = centerY;
    c->scaleFactor = scaleFactor;
    c->color[0] = 0.0f;
    c->color[1] = 0.0f;
    c->color[2] = 0.0f;
    c->opacity = opacity;
    c->depth = true;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::buildPerspProjMat(float *m, float fov,
                                       float aspect, float znear, float zfar)
{
    float xymax = znear * glm::tan((fov * M_PI) / 180.0);
    float ymin = -xymax;
    float xmin = -xymax;

    float width = xymax - xmin;
    float height = xymax - ymin;

    float depth = zfar - znear;
    float q = -(zfar + znear) / depth;
    float qn = -2.0f * (zfar * znear) / depth;

    float w = 2.0f * znear / width;
    w = w / aspect;
    float h = 2.0f * znear / height;

    m[0] = w;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;

    m[4] = 0;
    m[5] = h;
    m[6] = 0;
    m[7] = 0;

    m[8] = 0;
    m[9] = 0;
    m[10] = q;
    m[11] = -1.0f;

    m[12] = 0;
    m[13] = 0;
    m[14] = qn;
    m[15] = 0;
}
