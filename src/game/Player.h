#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <glm/glm.hpp>

class Player : public Drawable3DImage
{
public:
    Player();
    virtual ~Player();

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    void render() const;
};
