#pragma once

#include <engine/drawables/Drawable3D.h>
#include <all.h>

class Drawable3DBody : public Drawable3D
{
public:
    virtual ~Drawable3DBody() override = 0;
    virtual void render() const override = 0;
    virtual void update() override = 0;
};
