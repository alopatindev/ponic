#include "Drawable3D.h"
#include "Graphics.h"
#include <glm/glm.hpp>

Drawable3D::Drawable3D()
    : m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_size(glm::vec2(0.0f, 0.0f))
    , m_angle(0.0f)
    , m_center(glm::vec2(0.0f, 0.0f))
    , m_scaleFactor(1.0f)
    , m_opacity(1.0f)
{
}

Drawable3D::~Drawable3D()
{
}

void Drawable3D::render() const
{
    GRAPHICS.drawImage3D(
        m_group,
        m_name,
        m_pos.x, m_pos.y, m_pos.z,
        m_size.x, m_size.y,
        m_angle,
        m_center.x, m_center.y,
        m_scaleFactor,
        m_opacity
    );
}

void Drawable3D::setImage(const std::string& group, const std::string& name)
{
    m_group = group;
    m_name = name;
}

void Drawable3D::setPosition(const glm::vec3& pos)
{
    m_pos = pos;
}

void Drawable3D::setPosition(float x, float y, float z)
{
    m_pos.x = x;
    m_pos.y = y;
    m_pos.z = z;
}

void Drawable3D::setSize(const glm::vec2& size)
{
    m_size = size;
}

void Drawable3D::setSize(float width, float height)
{
    m_size.x = width;
    m_size.y = height;
}

void Drawable3D::setAngle(float angle)
{
    m_angle = angle;
}

void Drawable3D::setCenter(const glm::vec2& center)
{
    m_center = center;
}

void Drawable3D::setCenter(float centerX, float centerY)
{
    m_center.x = centerX;
    m_center.y = centerY;
}

void Drawable3D::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}

void Drawable3D::setOpacity(float opacity)
{
    m_opacity = opacity;
}
