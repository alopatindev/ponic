#pragma once

//#include <engine/physics/Drawable3DBody.h>
#include "../engine/Drawable3D.h"
#include <glm/glm.hpp>

class Player : public Drawable3D
{
public:
    Player();
    virtual ~Player() override;

    //virtual void render() const override;
    virtual void update() override;
};
