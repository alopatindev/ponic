#pragma once

#include "misc/Singleton.h"

class Camera_Class
{
    float x;
    float y;
    float z;

public:
    Camera_Class()
        : x(0.0f),
          y(0.0f),
          z(-1.0f)
    {
    }

    virtual ~Camera_Class()
    {
    }

    float getX()
    {
        return x;
    }

    float getY()
    {
        return y;
    }

    float getZoom()
    {
        return z;
    }

    void lookAt(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void setZoom(float zoom = -1.0f)
    {
        z = zoom;
    }

    bool isVisible(float x, float y, float width, float height)
    {
    }
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::getInstance())
