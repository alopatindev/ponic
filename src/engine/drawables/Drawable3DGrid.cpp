#include "Drawable3DGrid.h"
#include <engine/GridManager.h>
#include <engine/Graphics.h>
#include <cstring>
#include <game/Player.h>
#include <engine/Camera.h>

Drawable3DGrid_Class::Drawable3DGrid_Class()
    : m_grid(nullptr)
    , m_cursor(glm::ivec2(0, 0))
    , m_lastStep(glm::ivec2(0, 0))
{
    std::memset(m_gridBuffer, Empty, 1);
    //setSize(GRAPHICS.getAspect() * ASPECT_ADDITION, 1.0f);
    setSize(1.3f * ASPECT_ADDITION, 1.0f);
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
/*#ifdef _DEBUG
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
#endif*/

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
    bool canMove = true;
    float tileWidth = getTileWidth();

    if (PLAYER.isFrozen())
        canMove = false;
    if (canMove && !canStepLeft() && m_tryPos.x > m_startPos.x)
        canMove = false;
    if (canMove && !canStepRight() && m_tryPos.x < m_startPos.x - tileWidth)
        canMove = false;

    if (canMove)
    {
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

/*void Drawable3DGrid_Class::stepUp()
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
}*/

void Drawable3DGrid_Class::stepLeft()
{
    m_lastStep = glm::ivec2(-1, 0);
    if (canStepLeft())
        m_cursor += m_lastStep;
    updateBuffer();
}

void Drawable3DGrid_Class::stepRight()
{
    m_lastStep = glm::ivec2(1, 0);
    if (canStepRight())
        m_cursor += m_lastStep;
    updateBuffer();
}

void Drawable3DGrid_Class::stepCancel()
{
    m_cursor -= m_lastStep;
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

void Drawable3DGrid_Class::repairBuffer()
{
    float tileWidth = getTileWidth();
    float tileHeight = getTileHeight();

    glm::vec3 playerPos = PLAYER.getPosition();
    int playerPosX = coordsToIndexes(playerPos).x;
    //LOGI("playerPosX=%d", playerPosX);
    int goodPlayerPos = GRID_WIDTH / 2 + int(PLAYER.getGridSize().x) / 2;
    if (glm::abs(playerPosX - goodPlayerPos) > 2)
    //if (playerPosX != goodPlayerPos)
    {
        //LOGI("fixing");
        if (playerPosX > goodPlayerPos)
        {
            PLAYER.setPosition(playerPos.x - tileWidth,
                                      playerPos.y,
                                      playerPos.z);
            m_cursor.x++;
            CAMERA.lookAt(CAMERA.getPosition().x - tileWidth,
                          CAMERA.getPosition().y);
        }
        else
        {
            PLAYER.setPosition(playerPos.x + tileWidth,
                                      playerPos.y,
                                      playerPos.z);
            CAMERA.lookAt(CAMERA.getPosition().x + tileWidth,
                          CAMERA.getPosition().y);
            m_cursor.x--;
        }
    }
}

void Drawable3DGrid_Class::updateBuffer()
{
    repairBuffer();

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

/*bool Drawable3DGrid_Class::canStepUp() const
{
    int32_t height = (*m_grid)[0].size();
    return m_cursor.y < height - GRID_HEIGHT;
}

bool Drawable3DGrid_Class::canStepDown() const
{
    return m_cursor.y > 0;
}*/

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

TileType
Drawable3DGrid_Class::getTileType(const glm::vec2& vec, bool offsetHack) const
{
    return getTileType(vec.x, vec.y, offsetHack);
}

TileType
Drawable3DGrid_Class::getTileType(const glm::vec3& vec, bool offsetHack) const
{
    return getTileType(vec.x, vec.y, offsetHack);
}

TileType
Drawable3DGrid_Class::getTileType(float x, float y, bool offsetHack) const
{
    if (x < m_pos.x || x > m_pos.x + m_size.x ||
        y < m_pos.x || y > m_pos.y + m_size.y)
    {
        LOGE("wrong coords: %f %f", x, y);
        return Empty;
    }

    glm::ivec2 cursor = coordsToIndexes(x, y, offsetHack);
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

/*void Drawable3DGrid_Class::calculateSlopeVertexes(
    const glm::vec3& pos, glm::ivec2& leftVertex, glm::ivec2& rightVertex) const
{
    glm::ivec2 ipos = coordsToIndexes(pos);
    leftVertex = glm::ivec2(-1, -1);
    rightVertex = glm::ivec2(-1, -1);

    //  /
    // /  slope searching
    int i = ipos.x + int(PLAYER.getGridSize().x);
    if (ipos.y - 1 < 0)
        return;
    while (i > 0)
    {
        --i;
        if (m_gridBuffer[i][ipos.y - 1] != Surface)
            //|| m_gridBuffer[ipos.x][ipos.y - 1] != Surface
        {
            leftVertex = glm::ivec2(i + 1, ipos.y - 1);
            break;
        }
    }

    if (ipos.y + 1 > GRID_HEIGHT)
        return;
    //i = ipos.x;
    while (i < GRID_WIDTH - 1)
    {
        ++i;
        if (m_gridBuffer[i][ipos.y + 1] == Surface)
        {
            rightVertex = glm::ivec2(i, ipos.y + 1);
            break;
        }
    }

    if (leftVertex != glm::ivec2(-1, -1) &&
        rightVertex != glm::ivec2(-1, -1))
        return;


    // \
    //  \ slope searching
    i = ipos.x;
    if (ipos.y - 3 < 0)
        return;
    while (i < GRID_WIDTH - 1)
    {
        ++i;
        if (m_gridBuffer[i][ipos.y - 1] != Surface)
        {
            leftVertex = glm::ivec2(i - 1, ipos.y - 1);
            break;
        }
    }
    if (ipos.y - 3 < 0)
        return;
    while (i < GRID_WIDTH - 1)
    {
        ++i;
        if (m_gridBuffer[i][ipos.y - 3] != Surface)
        {
            rightVertex = glm::ivec2(i - 1, ipos.y - 3);
            break;
        }
    }
}

bool
Drawable3DGrid_Class::getNextSlopeOffset(const glm::vec3& pos, float& yOut) const
{
    glm::ivec2 leftVertex;
    glm::ivec2 rightVertex;
    calculateSlopeVertexes(pos, leftVertex, rightVertex);

    if (leftVertex == glm::ivec2(-1, -1) ||
        rightVertex == glm::ivec2(-1, -1))
    {
        return false;
    }

    glm::vec3 leftVertexCoords = indexesToCoords(leftVertex) + m_pos;
    glm::vec3 rightVertexCoords = indexesToCoords(rightVertex) + m_pos;

    //m_leftVertexCoords = leftVertexCoords;
    //m_rightVertexCoords = rightVertexCoords;

#if _DEBUG
    glm::vec2 playerSize = PLAYER.getSize();
    GRAPHICS.drawRectangle3D(
        leftVertexCoords.x, leftVertexCoords.y, leftVertexCoords.z + 0.001f,
        playerSize.x * 0.1f, playerSize.y * 0.1f,
        1.0f, 0.0f, 0.0f,
        0.8f);

    GRAPHICS.drawRectangle3D(
        rightVertexCoords.x, rightVertexCoords.y, rightVertexCoords.z + 0.001f,
        playerSize.x * 0.1f, playerSize.y * 0.1f,
        1.0f, 0.0f, 0.0f,
        0.8f);
#endif

//    glm::vec3 newPos = indexesToCoords(ipos);
//    float x = newPos.x;
    float x = pos.x + m_pos.x;
    float x1 = leftVertexCoords.x;
    float y1 = leftVertexCoords.y;
    float x2 = rightVertexCoords.x;
    float y2 = rightVertexCoords.y;

    float y = (x - x1) * y2 / (x2 - x1);

    LOGI("y=%f dx=%f-%f=%f", y, x, x1, x-x1);

    yOut = pos.y + y;
    return true;
}*/
