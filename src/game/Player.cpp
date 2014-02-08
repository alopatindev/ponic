#include "Player.h"
#include <Camera.h>
#include <Graphics.h>
#include <game/MyApp.h>

Player_Class::Player_Class()
    : m_grid(nullptr)
    , m_gridSize(glm::vec2(2.0f, 2.0f))
    , m_collision(Empty)
    , m_groundCollision(true)
    , m_gravityAcceleration(0.1f)
    , m_jumpAcceleration(0.0f)
    , m_initializePos(false)
    , m_leftDirection(false)
{
    //setCenter(0.5f, 0.5f);
    m_grid = &Drawable3DGrid::get();
    setSize(m_grid->getTileSize() * m_gridSize);
    m_image.setImage("game_common", "horse_stands");
    m_image.setSize(getSize() * 1.4f);
}

Player_Class::~Player_Class()
{
}

void Player_Class::initPosition(const glm::ivec2& gridPos)
{
    LOGI("set init pos (%d %d)", gridPos.x, gridPos.y);
    m_initialPos = gridPos;
    m_initializePos = true;
}

void Player_Class::update(int dt)
{
}

void Player_Class::fixedUpdate(int dt)
{
    float tileWidth = m_grid->getTileWidth();
    float tileHeight = m_grid->getTileHeight();
    if (m_initializePos)
    {
        m_initializePos = false;

        if (m_initialPos.x < GRID_WIDTH / 2)
            m_initialPos.x = GRID_WIDTH / 2;

        for (int x = 1; x < m_initialPos.x - GRID_WIDTH / 2; ++x)
            m_grid->stepRight();

        m_pos.y += m_initialPos.y * tileHeight;
        m_pos.y -= (GRID_HEIGHT / 2) * tileHeight;
        //m_pos.y -= float(GRID_HEIGHT) / (2.0f * ASPECT_ADDITION) * tileHeight;

        m_pos.z = m_grid->getPosition().z;
    }

    m_image.setHorizMirrored(m_leftDirection);
    m_image.setPosition(m_pos - glm::vec3(0.0f, tileHeight * 0.4f, 0.0f));

    //LOGI("jump=%f gravity=%f m_pos=(%f %f)",
    //     m_jumpAcceleration, m_gravityAcceleration, m_pos.x, m_pos.y);
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

    glm::ivec2 debugPos2 = m_grid->coordsToIndexes(m_pos);
    glm::vec3 debugPos3 = m_grid->indexesToCoords(debugPos2);
    debugPos3 += Drawable3DGrid::get().getPosition();
    /*LOGI("m_pos=(%f %f %f) 3=(%f %f %f) 2=(%d %d)",
         m_pos.x, m_pos.y, m_pos.z,
         debugPos3.x, debugPos3.y, debugPos3.z,
         debugPos2.x, debugPos2.y);*/
    GRAPHICS.drawRectangle3D(
        debugPos3.x, debugPos3.y, debugPos3.z + 0.001f,
        m_size.x * 0.1f, m_size.y * 0.1f,
        0.0f, 1.0f, 1.0f,
        0.8f);
#endif

    cursor.y -= tileHeight * 0.2f;
    /*if (cursor.y < 0.0f)
    {
        LOGI("y < 0");
        m_groundCollision = true;
    }
    else*/

    if (!m_groundCollision)
    {
        for (int x = 0;
             x < int(m_gridSize.x) + 1;
             ++x, cursor.x += tileWidth)
        {
            TileType t = m_grid->getTileType(cursor);
            if (t == Surface)
            {
                // align to grid
                float y =
                    m_grid->getPosition().y +
                    m_grid->coordsToIndexes(getPosition()).y *
                        (tileHeight * 1.01f);
                setPosition(getPosition().x, y, getPosition().z);

                m_groundCollision = true;
                break;
            }
        }
    }

    if (m_groundCollision)
        m_gravityAcceleration = 0.1f;

    //LOGI("ground collision: %d", m_groundCollision);

    // collisions with game objects
    m_gameObjectsCollided.clear();
    for (auto it :
            GridManager::get().getGameObjects(
                Drawable3DGrid::get().getGridName()))
    {
        if (it->isActive() && it->collides(m_pos, m_gridSize))
        {
            m_gameObjectsCollided.push_back(it);
        }
    }
}

void Player_Class::collisionGameObjectsUpdate()
{
    float tileWidth = m_grid->getTileWidth();
    float tileHeight = m_grid->getTileHeight();
    for (auto it : m_gameObjectsCollided)
    {
        switch (it->getType())
        {
        case Platformv:
        case PlatformV:
            {
                m_groundCollision = true;
                setPosition(m_pos.x, it->getPosition().y + tileHeight, m_pos.z);
                break;
            }
        case Platformh:
        case PlatformH:
            {
                m_groundCollision = true;
                setPosition(
                    m_pos.x + it->getLastMovement().x,
                    it->getPosition().y + tileHeight,
                    m_pos.z
                );
                break;
            }
        // TODO
        }
    }
}

void Player_Class::render() const
{
    m_image.render();

#ifdef _DEBUG
    GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z + 0.001f,
        m_size.x, m_size.y,
        0.6f, 0.0f, 0.0f,
        0.2f);
#endif
}

bool Player_Class::collidesGameObjects() const
{
    return m_gameObjectsCollided.size() > 0;
}

const std::vector<GameObject*>& Player_Class::getGameObjects()
{
    return m_gameObjectsCollided;
}

bool Player_Class::collidesSurface() const
{
    return m_collision == Surface;
}

void Player_Class::anticollisionUpdate(bool& stopMovement)
{
    stopMovement = false;
    float tileWidth = m_grid->getTileWidth();
    float tileHeight = m_grid->getTileHeight();
    // find empty at top
    //TileType collision = Surface;
    glm::vec3 cursor;
    cursor = m_pos;
    cursor.y += tileHeight;

    // anti run-into-the-wall algorithm
    glm::vec3 cursor2 = cursor;
    for (int i = -1; i < int(m_gridSize.x); ++i)
    {
        if (m_grid->getTileType(cursor2) == Surface)
        {
            m_grid->stepCancel();
            stopMovement = true;
            return;
        }
        else
            cursor2.x += tileWidth;
    }

    setPosition(cursor);
}

void Player_Class::gravityUpdate()
{
    m_jumpAcceleration = 0.0f;

    if (m_gravityAcceleration <= 0.3f)
        m_gravityAcceleration += 0.01f * GLOBAL_SPEED;

    glm::vec3 cursor;
    cursor = m_pos;
    float tileHeight = m_grid->getTileHeight();
    cursor.y -= tileHeight * m_gravityAcceleration;

    setPosition(cursor);
}

void Player_Class::jumpUpdate()
{
    if (m_jumpAcceleration < 0.1f)
        m_jumpAcceleration += 0.013f * GLOBAL_SPEED;
    else
        m_jumpAcceleration = 0.0f;
    glm::vec3 cursor = m_pos;
    cursor.y += m_jumpAcceleration;
    setPosition(cursor);
}

bool Player_Class::isFalling() const
{
    return !m_groundCollision;
}
