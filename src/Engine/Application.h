#pragma once

#include "../Game/MyApp.h"

class MyApp;

class Application
{
    static MyApp* m_app;  // virtual functions are so slow,
                          // I won't use them here

public:
    static void init();
    static void destroy();
    static void run();
    static void onUpdate();
    static void onRender();
    static void onReshape(int width, int height);
};
