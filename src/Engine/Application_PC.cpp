#include "Application.h"
#include "Log.h"
#include "System.h"
#include <GL/glut.h>

MyApp* Application::app = 0;

void Application::init()
{
    std::atexit(Application::destroy);
    app = new MyApp();
    app->init();
    glutDisplayFunc(Application::render);
    glutIdleFunc(Application::update);
}

void Application::destroy()
{
    LOGI("exiting app");
    app->destroy();
    delete app;
}

void Application::run()
{
    glutMainLoop();
}

void Application::update()
{
    static int timeBase = -1;

    int time = glutGet(GLUT_ELAPSED_TIME);
    if (timeBase < 0)
        timeBase = time;

    app->update();

    SYSTEM.setDt(time - timeBase);
    timeBase = time;
}

void Application::render()
{
    app->render();
}
