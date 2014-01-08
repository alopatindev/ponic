#include "Platform.h"
#include <Log.h>

Platform::Platform(const glm::ivec2& pos, TileType type)
    : GameObject(pos, type)
{
    switch (type)
    {
    case Platformv:
        m_speed = 0.001f;
        m_endPos = m_startPos + glm::ivec2(0, 5);
        m_direction = glm::vec3(0, 1, 0);
        break;
    case PlatformV:
        m_speed = 0.2f;
        m_endPos = m_startPos + glm::ivec2(0, 8);
        m_direction = glm::vec3(0, 1, 0);
        break;
    case Platformh:
        m_speed = 0.1f;
        m_endPos = m_startPos + glm::ivec2(5, 0);
        m_direction = glm::vec3(1, 0, 0);
        break;
    case PlatformH:
        m_speed = 0.2f;
        m_endPos = m_startPos + glm::ivec2(8, 0);
        m_direction = glm::vec3(1, 0, 0); // TODO .f
        break;
    }

    m_currentPos = m_startPos;
    setSize(Drawable3DGrid::get().getTileSize());
    setImage("game_common", "ground");
}

Platform::~Platform()
{
}

void Platform::update(int dt)
{
}

void Platform::fixedUpdate(int dt)
{
    Drawable3DGrid_Class& grid = Drawable3DGrid::get();
    glm::ivec2 v = m_currentPos - grid.getCursor();

    bool visible = v.x >= 0 && v.x <= GRID_WIDTH - 1 &&
                   v.y >= 0 && v.y <= GRID_HEIGHT - 1;
    setVisible(visible);
    if (!visible)
        return;

    glm::vec2 v2 = glm::vec2(v.x, v.y);
    v2 *= grid.getTileSize();
    glm::vec3 v3 = glm::vec3(v2.x, v2.y, 0.0f) + grid.getPosition();

    // movement
    //glm::vec3 movement = m_direction * m_speed;
    //v3 += movement;

    //if (v3.x <= m_startPos.x || v3.x >= m_endPos.x ||
    /*if(v3.y <= m_startPos.y *  ||
       v3.y >= m_endPos.y)
        m_direction = -m_direction;*/

    LOGI("v3=(%f %f)", v3.x, v3.y);

    setPosition(v3);
}

void Platform::render() const
{
    Drawable3DImage::render();
}
