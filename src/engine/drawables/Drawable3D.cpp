#include "Drawable3D.h"
#include <glm/glm.hpp>

Drawable3D::Drawable3D()
    : m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_size(glm::vec2(1.0f, 1.0f))
    , m_angle(0.0f)
    , m_center(glm::vec2(0.0f, 0.0f))
    , m_scaleFactor(1.0f)
    , m_opacity(1.0f)
{
}

Drawable3D::~Drawable3D()
{
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

const glm::vec3& Drawable3D::getPosition()
{
    return m_pos;
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
