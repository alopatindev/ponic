#include "Scene.h"
#include <Camera.h>
#include <Log.h>

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
    Player::get().render();
}

void Scene::update(int dt)
{
    auto& grid = Drawable3DGrid::get();
    grid.update(dt);
    Player::get().update(dt);
}

void Scene::fixedUpdate(int dt)
{
    static const float MAX_SPEED = 0.08f;
    static const float SPEED_STEP = 0.01f;
    static const float HILL_RESISTANCE = 0.8f;

    auto& grid = Drawable3DGrid::get();

    // update movements
    m_pressDirectionTimer += dt;
    if (m_pressDirectionTimer >= 100)
    {
        m_pressDirectionTimer = 0;
        if (m_pressedLeft)
        {
            if (m_speed.x < 0.0f)
                m_speed.x = 0.0f;
            if (m_speed.x < MAX_SPEED)
                m_speed += glm::vec3(SPEED_STEP, 0.0f, 0.0f);
        }
        else if (m_pressedRight)
        {
            if (m_speed.x > 0.0f)
                m_speed.x = 0.0f;
            if (m_speed.x > -MAX_SPEED)
                m_speed += glm::vec3(-SPEED_STEP, 0.0f, 0.0f);
        }
        else
            m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    glm::vec3 newPos = grid.getPosition() + m_speed;
    grid.trySetPosition(newPos);
    grid.fixedUpdate(dt);

    /*if (!grid.didMove())
    {
        Player::get().setPosition(Player::get().getPosition() - m_speed);
    }*/

    // update collisions
    Player::get().fixedUpdate(dt);
    if (Player::get().collidesSurface())
    {
        m_speed.x *= HILL_RESISTANCE;
        Player::get().anticollisionUpdate();
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
        Player::get().jumpUpdate();
    }
    else
    {
        m_pressJumpTimer = 0;
        if (Player::get().isFalling())
        {
            Player::get().gravityUpdate();
        }

        if (Player::get().collidesGameObjects())
        {
            Player::get().collisionGameObjectsUpdate();
        }
    }
}

void Scene::onPress(Input_Class::Key key)
{
    switch (key)
    {
    case Input_Class::Left:
        m_pressedLeft = true;
        break;
    case Input_Class::Right:
        m_pressedRight = true;
        break;
    case Input_Class::Jump:
        if (!Player::get().isFalling())
        {
            m_pressedJump = true;
        }
        break;
    }
}

void Scene::onRelease(Input_Class::Key key)
{
    switch (key)
    {
    case Input_Class::Left:
        m_pressedLeft = false;
        break;
    case Input_Class::Right:
        m_pressedRight = false;
        break;
    case Input_Class::Jump:
        m_pressedJump = false;
        break;
    }
}
