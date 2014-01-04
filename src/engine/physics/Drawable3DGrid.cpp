#include "Drawable3DGrid.h"
#include <engine/GridManager.h>
#include <engine/Graphics.h>
#include <cstring>

Drawable3DGrid::Drawable3DGrid()
    : m_grid(nullptr)
    , m_cursor(glm::ivec2(0, 0))
{
    std::memset(m_gridBuffer, Empty, 1);
    setPosition(-0.7f, -0.5f, -0.6f);
    setSize(GRAPHICS.getAspect(), 1.0f);
}

Drawable3DGrid::~Drawable3DGrid()
{
}

void Drawable3DGrid::render() const
{
    if (!getVisible())
        return;

#ifdef _DEBUG
    float tileWidth = m_size.x / GRID_WIDTH;
    float tileHeight = m_size.y / GRID_HEIGHT;

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
            case Player:
                color = glm::vec3(0.4f, 0.0f, 0.0f);
                break;
            }

            GRAPHICS.drawRectangle3D(
                m_pos.x + tileWidth * x,
                m_pos.y + tileHeight * y,
                m_pos.z,

                tileWidth * 0.9f, tileHeight * 0.9f,
                color.x, color.y, color.z,
                0.2f); }
    }

    /*GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z,
        m_size.x, m_size.y,
        0.0f, 0.0f, 0.2f,
        0.3f);*/
#endif
}

void Drawable3DGrid::update(int dt)
{
}

void Drawable3DGrid::fixedUpdate(int dt)
{
    /*static int timer = 0;
    timer += dt;
    if (timer >= 500)
    {
        timer = 0;
        stepRight();
    }*/
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
    int32_t height = (*m_grid)[0].size();
    if (m_cursor.y < height - GRID_HEIGHT)
        m_cursor.y++;
    updateBuffer();
}

void Drawable3DGrid::stepDown()
{
    if (m_cursor.y > 0)
        m_cursor.y--;
    updateBuffer();
}

void Drawable3DGrid::stepLeft()
{
    if (m_cursor.x > 0)
        m_cursor.x--;
    updateBuffer();
}

void Drawable3DGrid::stepRight()
{
    int32_t width = (*m_grid).size();
    if (m_cursor.x < width - GRID_WIDTH)
        m_cursor.x++;
    updateBuffer();
}

void Drawable3DGrid::setGrid(const std::string& grid)
{
    m_grid = &GridManager::getInstance().getGrid(grid);
    m_cursor = glm::ivec2(0, 0);
    updateBuffer();
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
