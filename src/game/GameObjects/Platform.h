#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include "GridManager.h"
#include <glm/glm.hpp>

class Platform : public GameObject, public Drawable3DImage
{
public:
    Platform(const glm::ivec2& pos, TileType type);
    virtual ~Platform();

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render();
};
