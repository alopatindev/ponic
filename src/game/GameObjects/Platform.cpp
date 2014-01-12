#include "Platform.h"
#include <Log.h>
#include <Graphics.h>
#include <game/Player.h>

Platform::Platform(const glm::ivec2& pos, TileType type,
                   const glm::vec2& gridSize)
    : GameObject(pos, type)
    , m_gridSize(gridSize)
{
    switch (type)
    {
    case Platformv:
        m_speed = 0.005f;
        m_endPos = m_startPos + glm::ivec2(0, 5);
        m_direction = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case PlatformV:
        m_speed = 0.01f;
        m_endPos = m_startPos + glm::ivec2(0, 8);
        m_direction = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case Platformh:
        m_speed = 0.005f;
        m_endPos = m_startPos + glm::ivec2(5, 0);
        m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case PlatformH:
        m_speed = 0.01f;
        m_endPos = m_startPos + glm::ivec2(8, 0);
        m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    }

    auto& grid = Drawable3DGrid::get();
    setSize(grid.getTileSize() * gridSize);
    setImage("game_common", "ground");

    glm::ivec2 v = m_startPos - grid.getCursor();
    glm::vec3 v3 = grid.indexesToCoords(v) + grid.getPosition();

    setPosition(v3);
}

Platform::~Platform()
{
}

void Platform::update(int dt)
{
}

void Platform::fixedUpdate(int dt)
{
    auto& grid = Drawable3DGrid::get();

    glm::ivec2 vstart = m_startPos - grid.getCursor();
    glm::ivec2 vend = m_endPos - grid.getCursor();

    // are we gonna calculate physics?
    bool active = vend.x + m_gridSize.x >= 0 &&
                  vstart.x - m_gridSize.x <= GRID_WIDTH - 1 &&
                  vend.y + m_gridSize.y >= 0 &&
                  vstart.y - m_gridSize.y <= GRID_HEIGHT - 1;
    setActive(active);
    if (!active)
    {
        setVisible(false);
        return;
    }

    // are we gonna show the object?
    glm::ivec2 checkPos = grid.coordsToIndexes(
        m_pos + glm::vec3(m_size.x, m_size.y, 0.0f)
    );
    bool visible = checkPos.x >= 0;
    setVisible(visible);

    // calculating new position
    glm::vec3 newPos = grid.indexesToCoords(vstart) + grid.getPosition();

    m_lastMovement = m_direction * m_speed;
    m_movementOffset += m_lastMovement;

    newPos += m_movementOffset;

    auto negative = [](const glm::vec3& v) {
        return v.x < 0.0f || v.y < 0.0f;
    };

    //glm::ivec2 cp = grid.coordsToIndexes(m_pos, true) + grid.getCursor();
    glm::ivec2 cp = grid.coordsToIndexes(newPos, true) + grid.getCursor();
    if (
        (!negative(m_direction) &&
            glm::length(cp) > glm::length(m_endPos) - 1) ||
        (negative(m_direction) &&
            glm::length(cp) <= glm::length(m_startPos))
    )
    {
        m_direction = -m_direction;
    }

    setPosition(newPos);
}

void Platform::render() const
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

bool Platform::collides(const glm::vec3& playerPos, const glm::vec2& gridSize)
{
    float tileWidth = Drawable3DGrid::get().getTileWidth();
    float tileHeight = Drawable3DGrid::get().getTileHeight();

    float y = playerPos.y - tileHeight;
    bool yCollision = y >= m_pos.y - tileHeight;
    if (!Player::get().flies())
    {
        yCollision &= y <= m_pos.y + 2.0f * tileHeight;
    }
    else
    {
        yCollision &= y <= m_pos.y + tileHeight;
    }

    if (yCollision)
    {
        for (int x = 0; x < int(gridSize.x); ++x)
        {
            float xx = x * tileWidth;
            if (playerPos.x + xx >= m_pos.x &&
                playerPos.x + xx <= m_pos.x + m_size.x)
            {
                return true;
            }
        }
    }
    return false;
}
