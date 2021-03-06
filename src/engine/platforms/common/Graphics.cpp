#include "Graphics.h"
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

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
            case Command::CommandType::Rectangle2D:
                flushRectangle2D(c);
                break;
            case Command::CommandType::Image2D:
                flushImage2D(c);
                break;
            case Command::CommandType::Rectangle3D:
                flushRectangle3D(c);
                break;
            case Command::CommandType::Image3D:
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

float Graphics_Class::getAspect()
{
    return m_width / m_height;
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

    c->type = Command::CommandType::Rectangle2D;
    //c->group = "";
    //c->name = "";
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
    c->horizMirrored = false;
    c->ignoreCamera = false;
    c->depth = !onTop;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::drawImage2D(
    const std::string& group, const std::string& name,
    float x, float y, float width, float height,
    float angle,
    float centerX, float centerY,
    float scaleFactor,
    float opacity,
    bool onTop
)
{
    if (opacity == 0.0f)
        return;

    float z = 0.0f;
    Command* c = new Command;

    c->type = Command::CommandType::Image2D;
    c->group = group;
    c->name = name;
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
    c->horizMirrored = false;
    c->ignoreCamera = false;
    c->depth = !onTop;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::drawRectangle3D(
    float x, float y, float z,
    float width, float height,
    float r, float g, float b,
    float opacity)
{
    if (opacity == 0.0f)
        return;

    Command* c = new Command;

    c->type = Command::CommandType::Rectangle3D;
    //c->group = "";
    //c->name = "";
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
    c->horizMirrored = false;
    c->ignoreCamera = false;
    c->depth = true;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::drawImage3D(
    const std::string& group, const std::string& name,
    float x, float y, float z,
    float width, float height,
    float angle,
    float centerX, float centerY,
    float scaleFactor,
    float opacity,
    bool horizMirrored,
    bool ignoreCamera
)
{
    //if (!CAMERA.isVisible(x, y, width, height))
    //    return;

    if (opacity == 0.0f)
        return;

    ASSERT(!group.empty() && !name.empty(), "invalid group or name")

    Command* c = new Command;

    c->type = Command::CommandType::Image3D;
    c->group = group;
    c->name = name;
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
    c->horizMirrored = horizMirrored;
    c->ignoreCamera = ignoreCamera;
    c->depth = true;

    if (opacity != 1.0f)
        m_imagesBufferTransparent[z].push(c);
    else
        m_imagesBuffer[z].push(c);
}

void Graphics_Class::buildPerspProjMat(float *m, float fov,
                                       float aspect, float znear, float zfar)
{
    /*float fovRad = (fov * M_PI) / 180.0;
    float xymax = znear * glm::tan(fovRad);
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
    m[15] = 0;*/
    fov *= 2.0f; // FIXME: no idea why need to do that
    glm::mat4 persp = glm::perspective(fov, aspect, znear, zfar);
    const float* ptr = glm::value_ptr(persp);
    for (size_t i = 0; i < 16; ++i)
        m[i] = ptr[i];
}
