#pragma once

#include "misc/Singleton.h"
#include "Graphics.h"
#include <glm/glm.hpp>
#include <game/Player.h>

class Camera_Class
{
    glm::vec3 m_pos;
    glm::vec3 m_newPos;
    bool m_lookAtPlayer;

public:
    Camera_Class();
    virtual ~Camera_Class();

    float getX() const;
    float getY() const;
    const glm::vec3& getPosition() const;
    float getZoom() const;

    void lookAt(float x, float y);
    void smoothLookAt(float x, float y);

    void setLookAtPlayer(bool lookAtPlayer);

    void zoom(float zoom = 0.0f);
    void smoothZoom(float zoom = 0.0f);

    void update(int dt);
    //bool isVisible(float x, float y, float width, float height)
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::get())
