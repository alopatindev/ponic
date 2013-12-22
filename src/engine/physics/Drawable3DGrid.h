#pragma once

#include <engine/drawables/Drawable3D.h>

static const size_t GRID_TILES_HORIZONTAL = 10;
static const size_t GRID_TILES_VERTICAL = 8;

class Drawable3DGrid : public Drawable3D
{
    enum TileType {Empty, Surface, Player};
    TileType m_tiles[GRID_TILES_HORIZONTAL][GRID_TILES_VERTICAL];

public:
    Drawable3DGrid();
    virtual ~Drawable3DGrid() override;
    virtual void render() const override;
    virtual void update() override;
};
