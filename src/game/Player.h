#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <engine/physics/Drawable3DGrid.h>
#include <glm/glm.hpp>

class Player : public Drawable3DImage
{
    const Drawable3DGrid* m_grid;
    glm::vec2 m_gridSize;
    TileType m_collision;
    bool m_groundCollision;
    float m_gravityAcceleration;
    float m_jumpAcceleration;

public:
    Player();
    virtual ~Player();

    void setGrid(const Drawable3DGrid& grid);

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render() const;

    bool collidesSurface() const;
    bool flies() const;
    //bool collidesEnemy() const; // TODO
    void anticollisionUpdate();
    void gravityUpdate();
    void jumpUpdate();
};
