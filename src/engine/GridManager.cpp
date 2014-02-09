#include "GridManager.h"
#include <engine/System.h>
#include <engine/Log.h>
#include <fstream>
#include <sstream>
#include <game/GameObjects/Platform.h>
#include <game/Player.h>

GridManager_Class::GridManager_Class()
{
}

GridManager_Class::~GridManager_Class()
{
    freeAllGrids();
}

void GridManager_Class::loadGrid(const std::string& grid)
{
    std::string fn(SYSTEM.getResourcesPath() + "grids/" + grid + ".txt");
    std::ifstream file(fn);

    if (file.fail())
    {
        LOGE("file %s cannot be open", fn.c_str());
        return;
    }

    if (m_grids.find(grid) != m_grids.end())
    //    m_grids[grid].clear();
        return;

    LOGI("loading grid %s", grid.c_str());

    int32_t width = 0;
    int32_t height = 0;
    std::string line;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> width;
        iss >> height;
    }

    Grid& g = m_grids[grid];
    g.resize(width);
    //for (size_t y = 0; y < height; ++y)
    for (int32_t y = height - 1; y >= 0; --y)  // FIXME
    {
        for (int32_t x = 0; x < width; ++x)
        {
            char c = file.get();
            g[x].resize(height);
            g[x][y] = static_cast<TileType>(c);
        }
        char newLine = file.get();
        (void) newLine;
    }

    for (int32_t y = height - 1; y >= 0; --y)  // FIXME
    {
        for (int32_t x = 0; x < width; ++x)
        {
            collectGameObjects(grid, glm::ivec2(x, y));
        }
    }
}

void GridManager_Class::collectGameObjects(const std::string& grid,
                                           const glm::ivec2& vec)
{
    Grid& g = m_grids[grid];
    TileType type = g[vec.x][vec.y];
    switch (type)
    {
    case Platformv:
    case Platformh:
    case PlatformV:
    case PlatformH:
        {
            int i;
            for (i = 0;
                i < vec.x + g.size() && g[vec.x + i][vec.y] == type;
                ++i)
            {
                g[vec.x + i][vec.y] = Empty;
            }
            GameObject* obj = new Platform(vec, type, glm::vec2(i, 1.0f));
            m_gameObjects[grid].push_back(obj);
        }
        break;
    case Ponic:
        g[vec.x][vec.y] = Empty;
        PLAYER.initPosition(vec);
        break;
    //case EnemyWalker:
    //case EnemyDropper:
    //case EnemyClown:
    //case EnemyEva:
    }
}

void GridManager_Class::freeGrid(const std::string& grid)
{
    LOGI(" freeing grid '%s'", grid.c_str());
    m_grids.erase(grid);
    for (auto itg : m_gameObjects[grid])
    {
        delete itg;
    }
    m_gameObjects[grid].clear();
    m_gameObjects.erase(grid);
}

void GridManager_Class::freeAllGrids()
{
    /*LOGI("freeing all grids");
    for (auto itg : m_grids)
    {
        freeGrid(itg.first);
    }*/

    for (auto it : m_grids)
    {
        for (auto itg : m_gameObjects[it.first])
        {
            delete itg;
        }
    }
    m_grids.clear();
    m_gameObjects.clear();
}

const Grid& GridManager_Class::getGrid(const std::string& grid)
{
    if (m_grids.find(grid) == m_grids.end())
        loadGrid(grid);
    return m_grids[grid];
}

void GridManager_Class::renderGameObjects(const std::string& grid) const
{
    auto itg = m_gameObjects.find(grid);
    while (itg != m_gameObjects.end())
    {
        for (auto it : itg->second)
        {
            it->render();
        }
        ++itg;
    }
}

void GridManager_Class::fixedUpdateGameObjects(const std::string& grid, int dt)
{
    for (auto it : m_gameObjects[grid])
    {
        it->fixedUpdate(dt);
    }
}

GameObject::GameObject(const glm::ivec2& pos, TileType type)
    : m_active(false)
    , m_gridPos(pos)
    , m_type(type)
{
}

GameObject::~GameObject()
{
}
