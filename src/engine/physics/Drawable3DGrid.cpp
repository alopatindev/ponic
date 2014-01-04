#include "Drawable3DGrid.h"
#include <engine/GridManager.h>
#include <engine/Graphics.h>
#include <cstring>

Drawable3DGrid::Drawable3DGrid()
    : m_grid(nullptr)
    , m_cursor(glm::ivec2(0, 0))
{
    std::memset(m_gridBuffer, Empty, 1);
    setSize(GRAPHICS.getAspect(), 1.0f);
    m_startPos = glm::vec3(-0.7f, -0.5f, -0.6f);
    m_tryPos = m_pos;
    setPosition(m_startPos);
}

Drawable3DGrid::~Drawable3DGrid()
{
}

void Drawable3DGrid::render() const
{
    if (!getVisible())
        return;

#ifdef _DEBUG
    float tileWidth = getTileWidth();
    float tileHeight = getTileHeight();

    glm::vec3 color;
    for (size_t x = 0; x < GRID_WIDTH; ++x)
    {
        for (size_t y = 0; y < GRID_HEIGHT; ++y)
        {
            switch (m_gridBuffer[x][y])
            {
            case Empty:
                color = glm::vec3(0.0f, 0.0f, 0.2f);
                break;
            case Surface:
                color = glm::vec3(0.0f, 0.9f, 0.0f);
                break;
            case Animal:
                color = glm::vec3(0.4f, 0.0f, 0.0f);
                break;
            }

            GRAPHICS.drawRectangle3D(
                m_pos.x + tileWidth * x,
                m_pos.y + tileHeight * y,
                m_pos.z,

                tileWidth * 0.9f, tileHeight * 0.9f,
                color.x, color.y, color.z,
                0.2f);
        }
    }
#endif
}

void Drawable3DGrid::update(int dt)
{
}

void Drawable3DGrid::fixedUpdate(int dt)
{
    float tileWidth = getTileWidth();
    if (!canStepLeft() && m_tryPos.x > m_startPos.x)
        return;
    if (!canStepRight() && m_tryPos.x < m_startPos.x - tileWidth)
        return;

    glm::vec3 movement = m_tryPos - m_startPos;

    if (std::abs(movement.x) >= tileWidth)
    {
        setPosition(m_startPos);
        if (movement.x < 0.0f)
            stepRight();
        else
            stepLeft();
    } else {
        setPosition(m_tryPos);
    }
}

void Drawable3DGrid::step(const glm::ivec2& vec)
{
    glm::ivec2 newCursor = m_cursor;
    newCursor += vec;

    int32_t width = (*m_grid).size();
    if ((newCursor.x > 0) && (newCursor.x < width - GRID_WIDTH))
        m_cursor.x = newCursor.x;

    int32_t height = (*m_grid)[0].size();
    if ((newCursor.y > 0) && (newCursor.y < height - GRID_HEIGHT))
        m_cursor.y = newCursor.y;
}

void Drawable3DGrid::stepUp()
{
    if (canStepUp())
        m_cursor.y++;
    updateBuffer();
}

void Drawable3DGrid::stepDown()
{
    if (canStepDown())
        m_cursor.y--;
    updateBuffer();
}

void Drawable3DGrid::stepLeft()
{
    if (canStepLeft())
        m_cursor.x--;
    updateBuffer();
}

void Drawable3DGrid::stepRight()
{
    if (canStepRight())
        m_cursor.x++;
    updateBuffer();
}

void Drawable3DGrid::setGrid(const std::string& grid)
{
    m_grid = &GridManager::get().getGrid(grid);
    m_cursor = glm::ivec2(0, 0);
    updateBuffer();
}

void Drawable3DGrid::trySetPosition(const glm::vec3& vec)
{
    m_tryPos = vec;
}

void Drawable3DGrid::updateBuffer()
{
    const Grid& grid = *m_grid;
    for (int32_t x = 0; x < GRID_WIDTH; ++x)
    {
        for (int32_t y = 0; y < GRID_HEIGHT; ++y)
        {
            m_gridBuffer[x][y] = grid[x + m_cursor.x][y + m_cursor.y];
        }
    }
}

bool Drawable3DGrid::canStepUp() const
{
    int32_t height = (*m_grid)[0].size();
    return m_cursor.y < height - GRID_HEIGHT;
}

bool Drawable3DGrid::canStepDown() const
{
    return m_cursor.y > 0;
}

bool Drawable3DGrid::canStepLeft() const
{
    return m_cursor.x > 0;
}

bool Drawable3DGrid::canStepRight() const
{
    int32_t width = (*m_grid).size();
    return m_cursor.x < width - GRID_WIDTH;
}

float Drawable3DGrid::getTileWidth() const
{
    return m_size.x / GRID_WIDTH;
}

float Drawable3DGrid::getTileHeight() const
{
    return m_size.y / GRID_HEIGHT;
}
