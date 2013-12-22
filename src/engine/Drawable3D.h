#pragma once

#include <glm/glm.hpp>
#include <string>

class Drawable3D
{
    std::string m_group;
    std::string m_name;
    glm::vec3 m_pos;
    glm::vec2 m_size;
    float m_angle;
    glm::vec2 m_center;
    float m_scaleFactor;
    float m_opacity;

public:
    Drawable3D();
    virtual ~Drawable3D();

    virtual void render() const;
    virtual void update() = 0;

    void setImage(const std::string& group, const std::string& name);
    void setPosition(const glm::vec3& pos);
    void setPosition(float x, float y, float z);
    void setSize(const glm::vec2& size);
    void setSize(float width, float height);
    void setAngle(float angle);
    void setCenter(const glm::vec2& center);
    void setCenter(float centerX, float centerY);
    void setScaleFactor(float scaleFactor);
    void setOpacity(float opacity);
};