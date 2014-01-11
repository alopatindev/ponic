#include "Player.h"
#include <Camera.h>
#include <Graphics.h>

Player::Player()
    : m_grid(nullptr)
    , m_gridSize(glm::vec2(2.0f, 2.0f))
    , m_collision(Empty)
    , m_groundCollision(true)
    , m_gravityAcceleration(0.1f)
    , m_jumpAcceleration(0.0f)
{
    setImage("game_common", "horse_stands");
    setPosition(-0.5f, -0.5f, -0.6f);
    //setCenter(0.5f, 0.5f);
    //setOpacity(1.0f);
    m_grid = &Drawable3DGrid::get();
    setSize(m_grid->getTileSize() * m_gridSize);
}

Player::~Player()
{
}

void Player::update(int dt)
{
}

void Player::fixedUpdate(int dt)
{
    //LOGI("jump=%f gravity=%f m_pos=(%f %f)",
    //     m_jumpAcceleration, m_gravityAcceleration, m_pos.x, m_pos.y);
    float tileWidth = m_grid->getTileWidth();
    float tileHeight = m_grid->getTileHeight();
    m_collision = Empty;
    glm::vec3 cursor;
    cursor = m_pos;
    for (int x = 0;
         m_collision == Empty && x < int(m_gridSize.x) + 1;
         ++x, cursor.x += tileWidth)
    {
        cursor.y = m_pos.y;
        for (int y = 0;
             m_collision == Empty && y < int(m_gridSize.y);
             ++y, cursor.y += tileHeight)
        {
            m_collision = m_grid->getTileType(cursor);
        }
    }
    //LOGI("player collides %d", m_collision);

    m_groundCollision = false;
    cursor = m_pos;

#if _DEBUG
    GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z + 0.001f,
        m_size.x * 0.1f, m_size.y * 0.1f,
        0.0f, 1.0f, 0.0f,
        0.8f);
#endif

    cursor.y -= tileHeight * 0.2f;
    /*if (cursor.y < 0.0f)
    {
        LOGI("y < 0");
        m_groundCollision = true;
    }
    else*/
    {
        for (int x = 0;
             x < int(m_gridSize.x) + 1;
             ++x, cursor.x += tileWidth)
        {
            TileType t = m_grid->getTileType(cursor);
            if (t == Surface)
            {
                m_groundCollision = true;
                break;
            }
        }
    }

    if (m_groundCollision)
        m_gravityAcceleration = 0.1f;

    //LOGI("ground collision: %d", m_groundCollision);
}

void Player::render() const
{
    Drawable3DImage::render();

#ifdef _DEBUG
    GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z + 0.001f,
        m_size.x, m_size.y,
        0.6f, 0.0f, 0.0f,
        0.2f);
#endif
}

bool Player::collidesSurface() const
{
    return m_collision == Surface;
}

void Player::anticollisionUpdate()
{
    // find empty at top
    //TileType collision = Surface;
    glm::vec3 cursor;
    cursor = m_pos;
    float tileHeight = m_grid->getTileHeight();
    cursor.y += tileHeight;
    /*for (;
         collision == Surface && cursor.y < m_grid->getSize().y;
         cursor.y += tileHeight)
    {
        collision = m_grid->getTileType(cursor);
    }*/
    setPosition(cursor);
}

void Player::gravityUpdate()
{
    m_jumpAcceleration = 0.0f;

    if (m_gravityAcceleration <= 0.3f)
        m_gravityAcceleration += 0.01f;

    glm::vec3 cursor;
    cursor = m_pos;
    float tileHeight = m_grid->getTileHeight();
    cursor.y -= tileHeight * m_gravityAcceleration;
    //if (cursor.y > 0.0f)

    setPosition(cursor);
}

void Player::jumpUpdate()
{
    if (m_jumpAcceleration < 0.1f)
        m_jumpAcceleration += 0.02f;
    else
        m_jumpAcceleration = 0.0f;
    glm::vec3 cursor = m_pos;
    cursor.y += m_jumpAcceleration;
    setPosition(cursor);
    //CAMERA.lookAt(CAMERA.getX(), CAMERA.getY() + m_jumpAcceleration);
}

bool Player::flies() const
{
    return !m_groundCollision;
}
