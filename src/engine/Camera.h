#pragma once

#include "misc/Singleton.h"
#include "Graphics.h"

class Camera_Class
{
    float m_x;
    float m_y;
    float m_z;

    float m_tx;
    float m_ty;
    float m_tz;

public:
    Camera_Class()
        : m_x(0.0f),
          m_y(0.0f),
          m_z(0.0f),
          m_tx(0.0f),
          m_ty(0.0f),
          m_tz(0.0f)
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
        m_tx = x;
        m_ty = y;
    }

    void setZoom(float zoom = 0.0f)
    {
        m_tz = zoom;
    }

    void update()
    {
        m_x = m_tx;
        m_y = m_ty;
        m_z = m_tz;
    }

    bool isVisible(float x, float y, float width, float height)
    {
        float wfar = GRAPHICS.getWfar();
        float hfar = GRAPHICS.getHfar();
        float xx = x + m_x;
        float yy = y + m_y;

        if ((xx + width) >= -wfar && (xx - width) <= wfar &&
            (yy + height) >= -hfar && (yy - height) <= hfar)
            return true;

        return false;
    }
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::getInstance())
