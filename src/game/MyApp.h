#pragma once

#include "Scene.h"

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
