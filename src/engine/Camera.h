#pragma once

#include "misc/Singleton.h"

class Camera_Class
{
    float m_x;
    float m_y;
    float m_z;

public:
    Camera_Class()
        : m_x(0.0f),
          m_y(0.0f),
          m_z(-1.0f)
    {
    }

    virtual ~Camera_Class()
    {
    }

    float getX()
    {
        return m_x;
    }

    float getY()
    {
        return m_y;
    }

    float getZoom()
    {
        return m_z;
    }

    void lookAt(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    void setZoom(float zoom = -1.0f)
    {
        m_z = zoom;
    }

    bool isVisible(float x, float y, float width, float height)
    {
    }
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::getInstance())
