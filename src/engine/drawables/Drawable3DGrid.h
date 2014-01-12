#pragma once

#include <engine/drawables/Drawable3D.h>
#include <engine/GridManager.h>
#include <engine/misc/Singleton.h>
#include <glm/glm.hpp>
#include <cstdlib>

static const size_t GRID_WIDTH = 20;
static const size_t GRID_HEIGHT = 12;

class Drawable3DGrid_Class : public Drawable3D
{
    TileType m_gridBuffer[GRID_WIDTH][GRID_HEIGHT];
    const Grid* m_grid;
    std::string m_gridName;
    glm::ivec2 m_cursor;  // left+up corner of the grid
    glm::vec3 m_startPos;
    glm::vec3 m_tryPos;
    //bool m_canMove;

public:
    Drawable3DGrid_Class();
    virtual ~Drawable3DGrid_Class();
    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    void setGrid(const std::string& grid);

    void step(const glm::ivec2& vec);
    void stepUp();
    void stepDown();
    void stepLeft();
    void stepRight();

    void trySetPosition(const glm::vec3& vec);
    /*bool didMove()
    {
        return m_canMove;
    }*/

    float getTileWidth() const;
    float getTileHeight() const;
    const glm::vec2& getTileSize() const;

    TileType getTileType(const glm::vec2& vec) const;
    TileType getTileType(const glm::vec3& vec) const;
    TileType getTileType(float x, float y) const;

    const glm::ivec2& getCursor() const
    {
        return m_cursor;
    }

    const std::string& getGridName() const
    {
        return m_gridName;
    }

    const glm::ivec2& coordsToIndexes(float x, float y, bool offsetHack = false) const;
    const glm::ivec2& coordsToIndexes(const glm::vec2& vec, bool offsetHack = false) const;
    const glm::ivec2& coordsToIndexes(const glm::vec3& vec, bool offsetHack = false) const;
    const glm::vec3& indexesToCoords(int x, int y) const;
    const glm::vec3& indexesToCoords(const glm::ivec2& vec) const;

private:
    void updateBuffer();

    bool canStepUp() const;
    bool canStepDown() const;
    bool canStepLeft() const;
    bool canStepRight() const;
};

typedef Singleton<Drawable3DGrid_Class> Drawable3DGrid;
