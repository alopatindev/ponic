#include "Scene.h"
#include <Log.h>

Scene::Scene()
    : m_pressedLeft(false)
    , m_pressedRight(false)
    , m_pressTimer(0)
    , m_speed(glm::vec3(0.0f, 0.0f, 0.0f))
{
    m_grid.setGrid("level1");
    m_player.setSize(m_grid.getTileWidth() * 2.0f, m_grid.getTileHeight());
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
    static const float MAX_SPEED = 0.08f;
    static const float SPEED_STEP = 0.01f;
    m_pressTimer += dt;
    if (m_pressTimer >= 100)
    {
        m_pressTimer = 0;
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

    m_player.fixedUpdate(dt);
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
    }
}
