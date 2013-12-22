#include "Drawable3DGrid.h"
//#include <engine/Log.h>
#include <engine/Graphics.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <engine/System.h>

Drawable3DGrid::Drawable3DGrid()
{
    std::memset(m_tiles, Empty, 1);
    setPosition(-0.7f, -0.5f, -0.6f);
    setSize(GRAPHICS.getAspect(), 1.0f);
    loadGrid("level1");
}

Drawable3DGrid::~Drawable3DGrid()
{
}

void Drawable3DGrid::render() const
{
    if (!getVisible())
        return;

#ifdef _DEBUG
    float tileWidth = m_size.x / GRID_TILES_HORIZONTAL;
    float tileHeight = m_size.y / GRID_TILES_VERTICAL;

    glm::vec3 color;
    for (size_t x = 0; x < GRID_TILES_HORIZONTAL; ++x)
    {
        for (size_t y = 0; y < GRID_TILES_VERTICAL; ++y)
        {
            switch (m_tiles[x][y])
            {
            case Empty:
                color = glm::vec3(0.0f, 0.0f, 0.2f);
                break;
            case Surface:
                color = glm::vec3(0.0f, 0.4f, 0.0f);
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

void Drawable3DGrid::update()
{
}

void Drawable3DGrid::loadGrid(const std::string& grid)
{
    clearGrid();

    /*std::string fn(SYSTEM.getResourcesPath() + "/grids/" + grid);
    std::ifstream file(fn);

    if (file.fail())
    {
        LOGE("file %s cannot be open", fn.c_str());
    }

    size_t width = 0;
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

void Drawable3DGrid::clearGrid()
{
    m_grid.clear();
}
