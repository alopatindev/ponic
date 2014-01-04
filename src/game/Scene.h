#pragma once

#include "Player.h"
#include <engine/drawables/Drawable3D.h>
#include <engine/physics/Drawable3DGrid.h>


class Scene : public Drawable3D
{
    //Player m_player;
    Drawable3DGrid m_grid;

public:
    Scene();
    virtual ~Scene();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
};
