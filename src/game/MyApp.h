#pragma once

#include "Scene.h"

const float GLOBAL_SPEED = 0.5f;

class MyApp
{
    Scene m_scene;

public:
    MyApp();
    virtual ~MyApp();

    void init();
    void destroy();
    void update(int dt);
    void fixedUpdate(int dt);
    void render() const;
};
