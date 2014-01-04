#include "Scene.h"
#include <Log.h>

Scene::Scene()
{
    m_grid.setGrid("level1");
    Input::get().press.connect(this, &Scene::onPress);
    Input::get().release.connect(this, &Scene::onRelease);
}

Scene::~Scene()
{
}

void Scene::render() const
{
    m_grid.render();
}

void Scene::update(int dt)
{
    m_grid.update(dt);
}

void Scene::fixedUpdate(int dt)
{
    m_grid.fixedUpdate(dt);
}

void Scene::onPress(Input_Class::Key key)
{
    LOGI("onPress key=%d", key);
}

void Scene::onRelease(Input_Class::Key key)
{
    LOGI("onRelease key=%d", key);
}
