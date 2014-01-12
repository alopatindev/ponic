#include "Camera.h"

Camera_Class::Camera_Class()
    : m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_newPos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_lookAtPlayer(false)
{
}

Camera_Class::~Camera_Class()
{
}

float Camera_Class::getX() const
{
    return m_pos.x;
}

float Camera_Class::getY() const
{
    return m_pos.y;
}

const glm::vec3& Camera_Class::getPosition() const
{
    return m_pos;
}

float Camera_Class::getZoom() const
{
    return m_pos.z;
}

void Camera_Class::lookAt(float x, float y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void Camera_Class::smoothLookAt(float x, float y)
{
    m_newPos.x = x;
    m_newPos.y = y;
}

void Camera_Class::setLookAtPlayer(bool lookAtPlayer)
{
    m_lookAtPlayer = lookAtPlayer;
}

void Camera_Class::zoom(float zoom)
{
    m_pos.z = zoom;
}

void Camera_Class::smoothZoom(float zoom)
{
    m_newPos.z = zoom;
}

void Camera_Class::update(int dt)
{
    if (m_lookAtPlayer)
    {
        glm::vec3 dpos = Player::get().getPosition() - m_pos;
        glm::vec2 dPlayerPos = glm::vec2(dpos.x, dpos.y);
        glm::vec2 playerOffset = Player::get().getSize();
        dPlayerPos += playerOffset;

        // smooth update
        float speed = 0.01f * dt;
        dPlayerPos *= speed;
        //lookAt(m_pos.x + dPlayerPos.x, m_pos.y + dPlayerPos.y);
        m_pos.x += dPlayerPos.x;
        m_pos.y += dPlayerPos.y;
        return;
    }

    if (m_pos != m_newPos)
    {
        static const float eps = 0.001f;
        float distance = glm::abs(glm::distance(m_pos, m_newPos));
        float speed = distance * dt * 0.01f;
        if (distance > eps)
            m_pos += m_newPos * speed;
        else
            m_pos = m_newPos;
    }
}

/*bool Camera_Class::isVisible(float x, float y, float width, float height) const
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
