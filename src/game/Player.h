#pragma once

//#include <engine/physics/Drawable3DBody.h>
#include <engine/drawables/Drawable3DImage.h>
#include <glm/glm.hpp>

class Player : public Drawable3DImage
{
public:
    Player();
    virtual ~Player() override;

    //virtual void render() const override;
    virtual void update() override;
};
