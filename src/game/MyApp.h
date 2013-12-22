#pragma once

class MyApp
{
    /*float m_angle;
    float m_scale;
    int m_timer;*/

public:
    MyApp();
    virtual ~MyApp();

    void init();
    void destroy();
    void update();
    void render() const;
};
