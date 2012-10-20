#include "Application.h"
#include <GL/glew.h>
#include "Log.h"
#include "System.h"
#include "Graphics.h"
#include <GL/glut.h>

MyApp* Application::m_app = 0;

void Application::init()
{
    std::atexit(Application::destroy);
    m_app = new MyApp();
    m_app->init();
    glutDisplayFunc(Application::onRender);
    glutIdleFunc(Application::onUpdate);
    glutReshapeFunc(Application::onReshape);
    Application::onReshape(glutGet(GLUT_WINDOW_WIDTH),
                           glutGet(GLUT_WINDOW_HEIGHT));
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

void Application::onUpdate()
{
    static int timeBase = -1;

    int time = glutGet(GLUT_ELAPSED_TIME);
    if (timeBase < 0)
        timeBase = time;

    m_app->update();

    SYSTEM.setDt(time - timeBase);
    timeBase = time;
}

void Application::onRender()
{
    m_app->render();
}

void Application::onReshape(int width, int height)
{
    GRAPHICS.onReshape(width, height);
}