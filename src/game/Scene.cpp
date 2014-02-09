#include "Scene.h"
#include <Camera.h>
#include <Log.h>
#include <game/MyApp.h>

Scene::Scene()
    : m_pressedLeft(false)
    , m_pressedRight(false)
    , m_pressedJump(false)
    , m_pressDirectionTimer(0)
    , m_pressJumpTimer(0)
    , m_speed(glm::vec3(0.0f, 0.0f, 0.0f))
{
    auto& grid = Drawable3DGrid::get();
    grid.setGrid("level1");

    Input::get().press.connect(this, &Scene::onPress);
    Input::get().release.connect(this, &Scene::onRelease);
}

Scene::~Scene()
{
    Input::get().press.disconnect(this);
    Input::get().release.disconnect(this);
}

void Scene::render() const
{
    auto& grid = Drawable3DGrid::get();
    grid.render();
    PLAYER.render();
    m_background.render();
}

void Scene::update(int dt)
{
    auto& grid = Drawable3DGrid::get();
    grid.update(dt);
    PLAYER.update(dt);
    if (!PLAYER.isFrozen())
    {
        m_background.updateSpeed(m_speed);
        m_background.update(dt);
    }
}

void Scene::fixedUpdate(int dt)
{
    static const float MAX_SPEED = 0.025f * GLOBAL_SPEED;
    static const float SPEED_STEP = 0.005f * GLOBAL_SPEED;
    static const float HILL_RESISTANCE = 0.8f;

    auto& grid = Drawable3DGrid::get();

    // update movements
    m_pressDirectionTimer += dt;
    if (m_pressDirectionTimer >= 100)
    {
        m_pressDirectionTimer = 0;
        if (m_pressedLeft)
        {
            if (!PLAYER.isFalling())
            {
                PLAYER.setAnimationState(Player_Class::AnimationStates::Run);
            }
            PLAYER.setLeftDirection(true);
            if (m_speed.x < 0.0f)
                m_speed.x = 0.0f;
            if (m_speed.x < MAX_SPEED)
                m_speed += glm::vec3(SPEED_STEP, 0.0f, 0.0f);
        }
        else if (m_pressedRight)
        {
            if (!PLAYER.isFalling())
            {
                PLAYER.setAnimationState(Player_Class::AnimationStates::Run);
            }
            PLAYER.setLeftDirection(false);
            if (m_speed.x > 0.0f)
                m_speed.x = 0.0f;
            if (m_speed.x > -MAX_SPEED)
                m_speed += glm::vec3(-SPEED_STEP, 0.0f, 0.0f);
        }
        else
        {
            if (!PLAYER.isFalling())
            {
                PLAYER.setAnimationState(Player_Class::AnimationStates::Stand);
            }
            m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }

    if (!PLAYER.isFrozen())
    {
        glm::vec3 newPos = grid.getPosition() + m_speed;
        grid.trySetPosition(newPos);
    }
    grid.fixedUpdate(dt);

    /*if (!grid.didMove())
    {
        PLAYER.setPosition(PLAYER.getPosition() - m_speed);
    }*/

    // update collisions
    PLAYER.fixedUpdate(dt);
    if (PLAYER.collidesSurface())
    {
        m_speed.x *= HILL_RESISTANCE;

        bool stopMovement;
        PLAYER.anticollisionUpdate(stopMovement);
        if (stopMovement)
        {
            m_pressedLeft = false;
            m_pressedRight = false;
        }
    }

    // update gravity
    if (m_pressedJump)
    {
        m_pressJumpTimer += dt;
        if (m_pressJumpTimer >= 100)
        {
            m_pressJumpTimer = 0;
            m_pressedJump = false;
        }
        else
        {
            PLAYER.setAnimationState(Player_Class::AnimationStates::Jump);
        }
        PLAYER.jumpUpdate();
    }
    else
    {
        m_pressJumpTimer = 0;
        if (PLAYER.isFalling())
        {
            PLAYER.setAnimationState(Player_Class::AnimationStates::Jump);
            PLAYER.gravityUpdate();
        }

        if (PLAYER.collidesGameObjects())
        {
            PLAYER.collisionGameObjectsUpdate();
            if (m_pressedLeft || m_pressedRight)
            {
                PLAYER.setAnimationState(Player_Class::AnimationStates::Run);
            }
        }
    }
}

void Scene::onPress(Input_Class::Key key)
{
    switch (key)
    {
    case Input_Class::Key::Left:
        m_pressedLeft = true;
        break;
    case Input_Class::Key::Right:
        m_pressedRight = true;
        break;
    case Input_Class::Key::Jump:
        if (!PLAYER.isFalling())
        {
            m_pressedJump = true;
        }
        break;
    case Input_Class::Key::Freeze:
        if (PLAYER.isFalling())
        {
            PLAYER.setFrozen(true);
        }
        break;
    }
}

void Scene::onRelease(Input_Class::Key key)
{
    switch (key)
    {
    case Input_Class::Key::Left:
        m_pressedLeft = false;
        break;
    case Input_Class::Key::Right:
        m_pressedRight = false;
        break;
    case Input_Class::Key::Jump:
        m_pressedJump = false;
        break;
    case Input_Class::Key::Freeze:
        PLAYER.setFrozen(false);
        break;
    }
}
