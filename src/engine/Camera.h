#pragma once

#include "misc/Singleton.h"
#include "Graphics.h"
#include <glm/glm.hpp>

class Camera_Class
{
    glm::vec3 m_pos;
    glm::vec3 m_newPos;

public:
    Camera_Class()
        : m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
        , m_newPos(glm::vec3(0.0f, 0.0f, 0.0f))
    {
    }

    virtual ~Camera_Class()
    {
    }

    float getX()
    {
        return m_pos.x;
    }

    float getY()
    {
        return m_pos.y;
    }

    float getZoom()
    {
        return m_pos.z;
    }

    void lookAt(float x, float y)
    {
        m_newPos.x = x;
        m_newPos.y = y;
    }

    void setZoom(float zoom = 0.0f)
    {
        m_newPos.z = zoom;
    }

    void update(int dt)
    {
        if (m_pos != m_newPos)
        {
            static float eps = 0.001f;
            float distance = glm::abs(glm::distance(m_pos, m_newPos));
            float speed = distance * dt * 0.01f;
            if (distance > eps)
                m_pos += m_newPos * speed;
            else
                m_pos = m_newPos;
        }
    }

    /*bool isVisible(float x, float y, float width, float height)
    {
        float wfar = GRAPHICS.getWfar();
        float hfar = GRAPHICS.getHfar();
        float dx = m_pos.x + x;
        float dy = m_pos.y + y;

        if ((dx + width) >= -wfar && (dx - width) <= wfar &&
            (dy + height) >= -hfar && (dy - height) <= hfar)
            return true;

        return false;
    }*/
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::get())
