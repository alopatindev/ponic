#pragma once

#include <engine/drawables/Drawable3DImage.h>
#include <engine/drawables/Drawable3DGrid.h>
#include "GridManager.h"
#include <glm/glm.hpp>

class Platform : public GameObject
{
    glm::vec2 m_gridSize;
    bool m_vertical;

public:
    Platform(const glm::ivec2& pos, TileType type, const glm::vec2& gridSize);
    virtual ~Platform();

    virtual void update(int dt);
    virtual void fixedUpdate(int dt);
    virtual void render() const;
    virtual bool collides(const glm::vec3& playerPos, const glm::vec2& gridSize);
};
