#pragma once

#include "Player.h"
#include <engine/drawables/Drawable3D.h>
#include <engine/physics/Drawable3DGrid.h>
#include <engine/Input.h>
#include <engine/thirdparty/sigslot.h>


class Scene : public Drawable3D, public sigslot::has_slots<>
{
    //Player m_player;
    Drawable3DGrid m_grid;

public:
    Scene();
    virtual ~Scene();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);

    void onPress(Input_Class::Key key);
    void onRelease(Input_Class::Key key);
};
