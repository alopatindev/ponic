#include "Camera.h"

Camera_Class::Camera_Class()
    : m_pos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_newPos(glm::vec3(0.0f, 0.0f, 0.0f))
    , m_lookAtPlayer(false)
    , m_playerSpeed(0.0f)
{
    zoom(CAMERA_DEFAULT_ZOOM);
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

void Camera_Class::setPlayerSpeed(float playerSpeed)
{
    m_playerSpeed = playerSpeed;
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
        glm::vec3 dpos = PLAYER.getPosition() - m_pos;
        glm::vec2 dPlayerPos = glm::vec2(dpos.x, dpos.y);
        glm::vec2 playerOffset = PLAYER.getSize();
        dPlayerPos += playerOffset;

        // smooth update
        static const float smooth = 0.01f;
        float camSpeed = smooth * dt;
        dPlayerPos *= camSpeed;
        //lookAt(m_pos.x + dPlayerPos.x, m_pos.y + dPlayerPos.y);
        m_pos.x += dPlayerPos.x;
        m_pos.y += dPlayerPos.y;

        // smooth zoom update
        if (m_playerSpeed < 0.002f)
        {
            static const float smooth = 0.00005f;
            camSpeed = smooth * dt;
            if (m_pos.z < CAMERA_DEFAULT_ZOOM)
                m_pos.z += camSpeed;
            else
                m_pos.z = CAMERA_DEFAULT_ZOOM;
        }
        else
        {
            static const float eps = 0.01f;
            if (m_playerSpeed > eps && m_pos.z > CAMERA_MIN_ZOOM)
            {
                camSpeed = smooth * dt;
                m_pos.z -= m_playerSpeed * camSpeed;
            }
        }
        return;
    }

    if (m_pos != m_newPos)
    {
        static const float eps = 0.001f;
        static const float smooth = 0.01f;
        float distance = glm::abs(glm::distance(m_pos, m_newPos));
        float camSpeed = distance * dt * smooth;
        if (distance > eps)
            m_pos += m_newPos * camSpeed;
        else
            m_pos = m_newPos;
    }
}

bool Camera_Class::isVisible(float x, float y, float width, float height) const
{
    float wfar = GRAPHICS.getWfar();
    float hfar = GRAPHICS.getHfar();
    float dx = m_pos.x + x;
    float dy = m_pos.y + y;

    if ((dx + width) >= -wfar && (dx - width) <= wfar &&
        (dy + height) >= -hfar && (dy - height) <= hfar)
        return true;

    return false;
}

bool Camera_Class::isVisible(const glm::vec3& pos, const glm::vec2& size) const
{
    return isVisible(pos.x, pos.y, size.x, size.y);
}
