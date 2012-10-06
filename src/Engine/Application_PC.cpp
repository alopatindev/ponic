#include "Application.h"
#include "Log.h"
#include "System.h"
#include <GL/glut.h>

MyApp* Application::m_app = 0;

void Application::init()
{
    std::atexit(Application::destroy);
    m_app = new MyApp();
    m_app->init();
    glutDisplayFunc(Application::render);
    glutIdleFunc(Application::update);
    glutReshapeFunc(Application::reshape);
}

void Application::destroy()
{
    LOGI("exiting app");
    m_app->destroy();
    delete m_app;
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

    m_app->update();

    SYSTEM.setDt(time - timeBase);
    timeBase = time;
}

void Application::render()
{
    m_app->render();
}

void Application::reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}
