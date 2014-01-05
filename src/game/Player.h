#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <engine/physics/Drawable3DGrid.h>
#include <glm/glm.hpp>

class Player : public Drawable3DImage
{
    TileType m_collision;
    const Drawable3DGrid* m_grid;
    glm::vec2 m_gridSize;

public:
    Player();
    virtual ~Player();

    void setGrid(const Drawable3DGrid& grid);

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render() const;

    bool collidesSurface() const;
    //bool collidesEnemy() const; // TODO
    void refixPosition();
};
