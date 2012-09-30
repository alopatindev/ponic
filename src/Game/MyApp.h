#pragma once

class MyApp
{
public:
    MyApp();
    virtual ~MyApp();

    void init();
    void destroy();
    void update();
    void render() const;
};
