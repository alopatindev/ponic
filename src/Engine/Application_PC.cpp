#include "Application.h"
#include <GL/glut.h>
#include "Log.h"

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
    app->update();
}

void Application::render()
{
    app->render();
}
