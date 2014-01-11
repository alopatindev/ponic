#include "Platform.h"
#include <Log.h>
#include <Graphics.h>

Platform::Platform(const glm::ivec2& pos, TileType type,
                   const glm::vec2& gridSize)
    : GameObject(pos, type)
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
    //m_currentPos = m_startPos;
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

    glm::ivec2 v = m_startPos - grid.getCursor();

    /*bool visible = v.x >= 0 && v.x <= GRID_WIDTH - 1 &&
                   v.y >= 0 && v.y <= GRID_HEIGHT - 1;
    setVisible(visible);
    if (!visible)
        return;*/

    glm::vec3 newPos = grid.indexesToCoords(v) + grid.getPosition();

    m_movementOffset += m_direction * m_speed;
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
/*    LOGI("neg(direction)=%d (true?)", negative(m_direction));
    LOGI("len(cp) < len(startPos): %d < %d -> %d\n",
         glm::length(cp), glm::length(m_startPos),
         (glm::length(cp) <= glm::length(m_startPos))
    );*/
    //m_currentPos = grid.coordsToIndexes(m_pos, true) + grid.getCursor();
    //LOGI("cp=(%d %d)\n", cp.x, cp.y);

    setPosition(newPos);

    /*glm::ivec2 v = m_currentPos - grid.getCursor();

    bool visible = v.x >= 0 && v.x <= GRID_WIDTH - 1 &&
                   v.y >= 0 && v.y <= GRID_HEIGHT - 1;
    setVisible(visible);
    if (!visible)
        return;

    //const glm::vec3& v3 = convertGridToScreen(m_currentPos);
    glm::vec2 v2 = glm::vec2(v.x, v.y);
    v2 *= grid.getTileSize();
    glm::vec3 v3 = glm::vec3(v2.x, v2.y, 0.0f) + grid.getPosition();

    // movement
    glm::vec3 movement = m_direction * m_speed * 2.0f;
    v3 += movement;
    LOGI("movement=(%f %f) m_speed=%f", movement.x, movement.y, m_speed);
    LOGI("v3=(%f %f)", v3.x, v3.y);

    //if (v3.x <= m_startPos.x || v3.x >= m_endPos.x ||*/
    /*if(v3.y <= m_startPos.y *  ||
       v3.y >= m_endPos.y)
        m_direction = -m_direction;*/

    //setPosition(v3);

    //m_currentPos = grid.coordsToIndexes(m_pos) - grid.getCursor();
//    LOGI("m_currentPos=(%d %d)", m_currentPos.x, m_currentPos.y);
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