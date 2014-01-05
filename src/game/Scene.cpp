#include "Scene.h"
#include <Log.h>

Scene::Scene()
    : m_pressedLeft(false)
    , m_pressedRight(false)
    , m_pressedJump(false)
    , m_pressDirectionTimer(0)
    , m_pressJumpTimer(0)
    , m_speed(glm::vec3(0.0f, 0.0f, 0.0f))
{
    m_grid.setGrid("level1");
    m_player.setGrid(m_grid);
    //m_player.setSize(m_grid.getTileWidth() * 2.0f, m_grid.getTileHeight());
    Input::get().press.connect(this, &Scene::onPress);
    Input::get().release.connect(this, &Scene::onRelease);
}

Scene::~Scene()
{
}

void Scene::render() const
{
    m_grid.render();
    m_player.render();
}

void Scene::update(int dt)
{
    m_grid.update(dt);
    m_player.update(dt);
}

void Scene::fixedUpdate(int dt)
{
    // update movements
    static const float MAX_SPEED = 0.08f;
    static const float SPEED_STEP = 0.01f;
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

    glm::vec3 newPos = m_grid.getPosition() + m_speed;
    m_grid.trySetPosition(newPos);
    m_grid.fixedUpdate(dt);

    // update collisions
    m_player.fixedUpdate(dt);
    if (m_player.collidesSurface())
        m_player.anticollisionUpdate();

    // update gravity
    if (m_pressedJump)
    {
        m_pressJumpTimer += dt;
        if (m_pressJumpTimer >= 100)
        {
            m_pressJumpTimer = 0;
            m_pressedJump = false;
        }
        m_player.jumpUpdate();
    }
    else
    {
        if (m_player.flies())
            m_player.gravityUpdate();
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
        if (!m_player.flies())
            m_pressedJump = true;
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