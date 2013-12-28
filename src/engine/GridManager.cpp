#include "GridManager.h"
#include <engine/System.h>
#include <engine/Log.h>
#include <fstream>
#include <sstream>

GridManager_Class::GridManager_Class()
{
}

GridManager_Class::~GridManager_Class()
{
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

    size_t width = 0;
    size_t height = 0;
    std::string line;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> width;
        iss >> height;
    }

    /*m_grids[grid].resize(width);
    for (size_t x = 0; x < width; ++x)
    {
        m_grids[grid][x].resize(height);
        for (size_t y = 0; y < height; ++y)
        {
            char c = file.get();
            int digit = c - '0';
            m_grids[grid][x][y] = static_cast<TileType>(digit);
        }
    }*/

    Grid& g = m_grids[grid];
    g.resize(width);
    //for (size_t y = 0; y < height; ++y)
    for (int32_t y = height - 1; y >= 0; --y)  // FIXME
    {
        for (int32_t x = 0; x < width; ++x)
        {
            char c = file.get();
            int digit = c - '0';
            g[x].resize(height);
            g[x][y] = static_cast<TileType>(digit);
        }
        char newLine = file.get();
        (void) newLine;
    }

    file.close();
}

void GridManager_Class::freeGrid(const std::string& grid)
{
    m_grids.erase(grid);
}

void GridManager_Class::freeAllGrids()
{
    m_grids.clear();
}

const Grid& GridManager_Class::getGrid(const std::string& grid)
{
    if (m_grids.find(grid) == m_grids.end())
        loadGrid(grid);
    return m_grids[grid];
}
