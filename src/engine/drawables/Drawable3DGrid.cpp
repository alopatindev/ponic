#include "Drawable3DGrid.h"
#include <engine/GridManager.h>
#include <engine/Graphics.h>
#include <cstring>

Drawable3DGrid_Class::Drawable3DGrid_Class()
    : m_grid(nullptr)
    , m_cursor(glm::ivec2(0, 0))
{
    std::memset(m_gridBuffer, Empty, 1);
    setSize(GRAPHICS.getAspect(), 1.0f);
    m_startPos = glm::vec3(-0.7f, -0.5f, -0.6f);
    m_tryPos = m_pos;
    setPosition(m_startPos);
}

Drawable3DGrid_Class::~Drawable3DGrid_Class()
{
}

void Drawable3DGrid_Class::render() const
{
    if (!getVisible())
        return;

    float tileWidth = getTileWidth();
    float tileHeight = getTileHeight();

    glm::vec3 color;
    for (int32_t x = 0; x < GRID_WIDTH; ++x)
    {
        for (int32_t y = 0; y < GRID_HEIGHT; ++y)
        {
#ifdef _DEBUG
            switch (m_gridBuffer[x][y])
            {
            case Empty:
                color = glm::vec3(0.0f, 0.0f, 0.2f);
                break;
            case Surface:
                color = glm::vec3(0.0f, 0.9f, 0.0f);
                break;
            case Ponic:
            case Platformv:
            case Platformh:
            case PlatformV:
            case PlatformH:
            case EnemyWalker:
            case EnemyDropper:
            case EnemyClown:
            case EnemyEva:
                color = glm::vec3(0.4f, 0.0f, 0.0f);
                break;
            default:
                color = glm::vec3(1.0f, 1.0f, 1.0f);
                break;
            }

            GRAPHICS.drawRectangle3D(
                m_pos.x + tileWidth * x,
                m_pos.y + tileHeight * y,
                m_pos.z,

                tileWidth * 0.9f, tileHeight * 0.9f,
                color.x, color.y, color.z,
                0.4f);
#endif

            switch (m_gridBuffer[x][y])
            {
            case Surface:
            case Platformv:
            case Platformh:
            case PlatformV:
            case PlatformH:
                GRAPHICS.drawImage3D(
                    "game_common", "ground",
                    m_pos.x + tileWidth * x,
                    m_pos.y + tileHeight * y,
                    m_pos.z,

                    tileWidth, tileHeight);
                break;
            default:
                break;
            }

        }
    }

    GridManager::get().renderGameObjects(m_gridName);
}

void Drawable3DGrid_Class::update(int dt)
{
}

void Drawable3DGrid_Class::fixedUpdate(int dt)
{
    float tileWidth = getTileWidth();
    if (!canStepLeft() && m_tryPos.x > m_startPos.x)
        return;
    if (!canStepRight() && m_tryPos.x < m_startPos.x - tileWidth)
        return;

    glm::vec3 movement = m_tryPos - m_startPos;

    if (glm::abs(movement.x) >= tileWidth)
    {
        setPosition(m_startPos);
        if (movement.x < 0.0f)
            stepRight();
        else
            stepLeft();
    } else {
        setPosition(m_tryPos);
    }

    GridManager::get().fixedUpdateGameObjects(m_gridName, dt);
}

void Drawable3DGrid_Class::step(const glm::ivec2& vec)
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

void Drawable3DGrid_Class::stepUp()
{
    if (canStepUp())
        m_cursor.y++;
    updateBuffer();
}

void Drawable3DGrid_Class::stepDown()
{
    if (canStepDown())
        m_cursor.y--;
    updateBuffer();
}

void Drawable3DGrid_Class::stepLeft()
{
    if (canStepLeft())
        m_cursor.x--;
    updateBuffer();
}

void Drawable3DGrid_Class::stepRight()
{
    if (canStepRight())
        m_cursor.x++;
    updateBuffer();
}

void Drawable3DGrid_Class::setGrid(const std::string& grid)
{
    m_gridName = grid;
    m_grid = &GridManager::get().getGrid(grid);
    m_cursor = glm::ivec2(0, 0);
    updateBuffer();
}

void Drawable3DGrid_Class::trySetPosition(const glm::vec3& vec)
{
    m_tryPos = vec;
}

void Drawable3DGrid_Class::updateBuffer()
{
    const Grid& grid = *m_grid;
    int32_t gridWidth = grid.size();
    int32_t gridHeight = grid[0].size();
    for (int32_t x = 0; x < GRID_WIDTH; ++x)
    {
        for (int32_t y = 0; y < GRID_HEIGHT; ++y)
        {
            int32_t xx = x + m_cursor.x;
            int32_t yy = y + m_cursor.y;
            if (xx >= gridWidth || yy >= gridHeight || xx < 0 || yy < 0)
                m_gridBuffer[x][y] = Empty;
            else
                m_gridBuffer[x][y] = grid[xx][yy];
        }
    }
}

bool Drawable3DGrid_Class::canStepUp() const
{
    int32_t height = (*m_grid)[0].size();
    return m_cursor.y < height - GRID_HEIGHT;
}

bool Drawable3DGrid_Class::canStepDown() const
{
    return m_cursor.y > 0;
}

bool Drawable3DGrid_Class::canStepLeft() const
{
    return m_cursor.x > 0;
}

bool Drawable3DGrid_Class::canStepRight() const
{
    int32_t width = (*m_grid).size();
    return m_cursor.x < width - GRID_WIDTH;
}

float Drawable3DGrid_Class::getTileWidth() const
{
    return m_size.x / GRID_WIDTH;
}

float Drawable3DGrid_Class::getTileHeight() const
{
    return m_size.y / GRID_HEIGHT;
}

const glm::vec2& Drawable3DGrid_Class::getTileSize() const
{
    static glm::vec2 size;
    size.x = m_size.x / GRID_WIDTH;
    size.y = m_size.y / GRID_HEIGHT;
    return size;
}

TileType Drawable3DGrid_Class::getTileType(const glm::vec2& vec) const
{
    return getTileType(vec.x, vec.y);
}

TileType Drawable3DGrid_Class::getTileType(const glm::vec3& vec) const
{
    return getTileType(vec.x, vec.y);
}

TileType Drawable3DGrid_Class::getTileType(float x, float y) const
{
    if (x < m_pos.x || x > m_pos.x + m_size.x ||
        y < m_pos.x || y > m_pos.y + m_size.y)
    {
        LOGE("wrong coords: %f %f", x, y);
        return Empty;
    }

    glm::ivec2 cursor = coordsToIndexes(x, y);
    return m_gridBuffer[cursor.x][cursor.y];
}

const glm::ivec2& Drawable3DGrid_Class::coordsToIndexes(float x, float y, bool offsetHack) const
{
    float tileWidth = getTileWidth();
    float tileHeight = getTileHeight();
    if (offsetHack)
    {
        x += tileWidth / 50.0f;
        y += tileHeight / 50.0f;
    }
    static glm::ivec2 cursor;
    cursor.x = glm::floor((x - m_pos.x) / tileWidth);
    cursor.y = glm::floor((y - m_pos.y) / tileHeight);
    return cursor;
}

const
glm::ivec2& Drawable3DGrid_Class::coordsToIndexes(const glm::vec2& vec, bool offsetHack) const
{
    return coordsToIndexes(vec.x, vec.y, offsetHack);
}

const
glm::ivec2& Drawable3DGrid_Class::coordsToIndexes(const glm::vec3& vec, bool offsetHack) const
{
    return coordsToIndexes(vec.x, vec.y, offsetHack);
}

const glm::vec3& Drawable3DGrid_Class::indexesToCoords(int x, int y) const
{
    glm::vec2 v(x, y);
    v *= getTileSize();
    static glm::vec3 cursor;
    cursor = glm::vec3(v.x, v.y, 0.0f);
    return cursor;
}

const
glm::vec3& Drawable3DGrid_Class::indexesToCoords(const glm::ivec2& vec) const
{
    return indexesToCoords(vec.x, vec.y);
}
