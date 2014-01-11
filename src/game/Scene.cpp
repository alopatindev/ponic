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
    //m_player.setGrid(grid);
    //m_player.setSize(grid.getTileWidth() * 2.0f, grid.getTileHeight());
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
    m_player.render();
}

void Scene::update(int dt)
{
    auto& grid = Drawable3DGrid::get();
    grid.update(dt);
    m_player.update(dt);
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

    // update collisions
    m_player.fixedUpdate(dt);
    if (m_player.collidesGameObjects())
    {
        LOGI("game object collision detected");
        m_player.collisionGameObjectsUpdate();
    }
    else if (m_player.collidesSurface())
    {
        m_speed.x *= HILL_RESISTANCE;
        m_player.anticollisionUpdate();
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
        m_player.jumpUpdate();
    }
    else
    {
        m_pressJumpTimer = 0;
        if (m_player.flies())
        {
            m_player.gravityUpdate();
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
        if (!m_player.flies())
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
