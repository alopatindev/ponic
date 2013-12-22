#pragma once

#include "misc/IVisible.h"
#include <glm/glm.hpp>

class Drawable3D : virtual public IVisible
{
public:
    Drawable3D();
    virtual ~Drawable3D();

    virtual void render() const = 0;
    virtual void update() = 0;

    void setPosition(const glm::vec3& pos);
    void setPosition(float x, float y, float z);
    void setSize(const glm::vec2& size);
    void setSize(float width, float height);
    void setAngle(float angle);
    void setCenter(const glm::vec2& center);
    void setCenter(float centerX, float centerY);
    void setScaleFactor(float scaleFactor);
    void setOpacity(float opacity);

protected:
    glm::vec3 m_pos;
    glm::vec2 m_size;
    float m_angle;
    glm::vec2 m_center;
    float m_scaleFactor;
    float m_opacity;
};
