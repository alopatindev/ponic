#pragma once

#include <engine/physics/Drawable3DGrid.h>
#include <all.h>

static const size_t GRID_TILES_HORIZONTAL = 10;
static const size_t GRID_TILES_VERTICAL = 8;

class Drawable3DGrid : public Drawable3D
{
    GridManager_Class::TileType m_tiles[GRID_TILES_HORIZONTAL][GRID_TILES_VERTICAL];
    GridManager_Class::Grid m_grid;

public:
    Drawable3DGrid();
    virtual ~Drawable3DGrid() override;
    virtual void render() const override;
    virtual void update() override;
};
