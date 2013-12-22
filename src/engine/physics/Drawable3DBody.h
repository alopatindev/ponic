#pragma once

#include <engine/Drawable3D.h>

class Drawable3DBody : public Drawable3D
{
public:
    virtual ~Drawable3DBody() override = 0;
    virtual void render() const override = 0;
    virtual void update() override = 0;
};
