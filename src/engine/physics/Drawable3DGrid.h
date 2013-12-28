#pragma once

#include <engine/physics/Drawable3DGrid.h>
#include <all.h>

static const size_t GRID_WIDTH = 10;
static const size_t GRID_HEIGHT = 8;

class Drawable3DGrid : public Drawable3D
{
    TileType m_gridBuffer[GRID_WIDTH][GRID_HEIGHT];
    const Grid* m_grid;
    glm::i32vec2 m_cursor;  // left+up corner of the grid

public:
    Drawable3DGrid();
    virtual ~Drawable3DGrid();
    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    void setGrid(const std::string& grid);

    void step(const glm::i32vec2& vec);
    void stepUp();
    void stepDown();
    void stepLeft();
    void stepRight();

private:
    void updateBuffer();
};
