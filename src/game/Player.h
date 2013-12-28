#pragma once

//#include <engine/physics/Drawable3DBody.h>
#include <engine/drawables/Drawable3DImage.h>
#include <glm/glm.hpp>

class Player : public Drawable3DImage
{
public:
    Player();
    virtual ~Player();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
};
