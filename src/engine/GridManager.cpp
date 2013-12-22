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

    /*size_t width = 0;
    size_t height = 0;

    file >> width >> height;

    m_grid.resize(width);
    for (size_t x = 0; x < width; ++x)
    {
        m_grid[x].resize(height);
        for (size_t y = 0; y < height; ++y)
        {
            //file >> m_grid[x][y];
        }
    }*/
}

void GridManager_Class::freeGrid(const std::string& grid)
{
    m_grids.erase(grid);
}

void GridManager_Class::freeAllGrids()
{
    m_grids.clear();
}
