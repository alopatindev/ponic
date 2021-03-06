#pragma once

#include "Player.h"
#include <engine/drawables/Drawable3D.h>
#include <game/Background3D.h>
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/Input.h>
#include <engine/thirdparty/sigslot.h>

class Scene : public Drawable3D, public sigslot::has_slots<>
{
    //Player m_player;
    //Drawable3DGrid m_grid;

    bool m_pressedLeft;
    bool m_pressedRight;
    bool m_pressedJump;
    int m_pressDirectionTimer;
    int m_pressJumpTimer;
    glm::vec3 m_speed;

    Background3D m_background;

public:
    Scene();
    virtual ~Scene();

    virtual void render() const;
    virtual void update(int dt);
    virtual void fixedUpdate(int dt);

    void onPress(Input_Class::Key key);
    void onRelease(Input_Class::Key key);

    const glm::vec3& getSpeed() const
    {
        return m_speed;
    }
};
