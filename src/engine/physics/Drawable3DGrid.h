#pragma once

#include <engine/Drawable3DGrid.h>

class Drawable3DGrid : public Drawable3D
{
public:
    virtual ~Drawable3DGrid() override;
    //virtual void render();
    virtual void update();
};
