#include "Player.h"
#include <Graphics.h>

Player::Player()
    : m_grid(nullptr)
    , m_gridSize(glm::vec2(2.0f, 2.0f))
{
    setImage("game_common", "horse_stands");
    setPosition(-0.5f, -0.5f, -0.6f);
    //setCenter(0.5f, 0.5f);
    //setOpacity(1.0f);
}

Player::~Player()
{
}

void Player::setGrid(const Drawable3DGrid& grid)
{
    m_grid = &grid;
    setSize(m_grid->getTileSize() * m_gridSize);
}

void Player::update(int dt)
{
}

void Player::fixedUpdate(int dt)
{
    m_collision = Empty;
    glm::vec3 cursor;
    cursor = m_pos;
    for (int x = 0;
         m_collision == Empty && x < int(m_gridSize.x);
         ++x, cursor.x += m_grid->getTileWidth())
    {
        cursor.y = m_pos.y;
        for (int y = 0;
             m_collision == Empty && y < int(m_gridSize.y);
             ++y, cursor.y += m_grid->getTileHeight())
        {
            m_collision = m_grid->getTileType(cursor);
        }
    }
    LOGI("player collides %d", m_collision);
}

void Player::render() const
{
    Drawable3DImage::render();

#ifdef _DEBUG
    GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z + 0.001f,
        m_size.x, m_size.y,
        0.6f, 0.0f, 0.0f,
        0.5f);
#endif
}

bool Player::collidesSurface() const
{
    return m_collision == Surface;
}

void Player::refixPosition()
{
    // find empty at top
}
