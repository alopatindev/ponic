#pragma once

#include "misc/Singleton.h"
#include "Graphics.h"
#include <glm/glm.hpp>
#include <game/Player.h>

static const float CAMERA_MIN_ZOOM = 0.4f;
static const float CAMERA_DEFAULT_ZOOM = 0.44f;

//static const float CAMERA_MIN_ZOOM = 0.01f;
//static const float CAMERA_DEFAULT_ZOOM = 0.f;

class Camera_Class
{
    glm::vec3 m_pos;
    glm::vec3 m_newPos;
    bool m_lookAtPlayer;
    float m_playerSpeed;

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
    void setPlayerSpeed(float playerSpeed);

    void zoom(float zoom = 0.0f);
    void smoothZoom(float zoom = 0.0f);

    void update(int dt);

    bool isVisible(float x, float y, float width, float height) const;
    bool isVisible(const glm::vec3& pos, const glm::vec2& size) const;
};

typedef Singleton<Camera_Class> Camera;

#define CAMERA (Camera::get())
