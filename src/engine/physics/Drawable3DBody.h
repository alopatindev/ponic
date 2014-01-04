#pragma once

#include <engine/drawables/Drawable3D.h>

class Drawable3DBody : public Drawable3D
{
public:
    virtual ~Drawable3DBody() = 0;
    virtual void render() const = 0;
    virtual void update(int dt) = 0;
    virtual void fixedUpdate(int dt) = 0;
};
