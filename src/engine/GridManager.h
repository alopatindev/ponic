#pragma once

#include "misc/Singleton.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "drawables/Drawable3DImage.h"

enum TileType
{
    Empty = '_',
    Surface = 'x',
    Ponic = 'P',
    Platformv = 'v',
    Platformh = 'h',
    PlatformV = 'V',
    PlatformH = 'H',
    EnemyWalker = 'W',
    EnemyDropper = 'D',
    EnemyClown = 'C',
    EnemyEva = 'E',
};

typedef std::vector<std::vector<TileType>> Grid;

class GameObject;

class GridManager_Class
{
    std::unordered_map<std::string, Grid> m_grids;
    /*std::unordered_map<
        std::string,
        std::vector<std::shared_ptr<GameObject>>
    > m_gameObjects;*/
    std::unordered_map<std::string, std::vector<GameObject*>> m_gameObjects;

public:
    GridManager_Class();
    virtual ~GridManager_Class();

    void loadGrid(const std::string& grid);
    void freeGrid(const std::string& grid);
    void freeAllGrids();

    const Grid& getGrid(const std::string& grid);

    void renderGameObjects(const std::string& grid) const;
    void fixedUpdateGameObjects(const std::string& grid, int dt);

    std::vector<GameObject*>& getGameObjects(const std::string grid)
    {
        return m_gameObjects[grid];
    }

private:
    void updateGameObjects(const std::string& grid, const glm::ivec2& vec);
};

typedef Singleton<GridManager_Class> GridManager;

class GameObject : public Drawable3DImage
{
    bool m_active;

protected:
    float m_speed;
    glm::ivec2 m_startPos;
    glm::ivec2 m_endPos;
    glm::vec3 m_direction;
    glm::vec3 m_movementOffset;

    TileType m_type;

public:
    GameObject(const glm::ivec2& pos, TileType type);
    virtual ~GameObject();

    virtual bool collides(const glm::vec3& playerPos,
                          const glm::vec2& gridSize) = 0;

    bool isActive() const
    {
        return m_active;
    }

    void setActive(bool active)
    {
        m_active = active;
    }
};
