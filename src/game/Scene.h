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

    bool m_pressedLeft;
    bool m_pressedRight;
    int m_pressTimer;

    glm::vec3 m_speed;

public:
    Scene();
    virtual ~Scene();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);

    void onPress(Input_Class::Key key);
    void onRelease(Input_Class::Key key);
};
