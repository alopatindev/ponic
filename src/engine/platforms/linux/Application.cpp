#include <GL/glew.h>
#include "Application.h"
#include "Log.h"
#include "System.h"
#include "Graphics.h"
#include "Input.h"
#include <GL/glut.h>

MyApp* Application::m_app = 0;

void Application::init()
{
    std::atexit(Application::destroy);
    GRAPHICS.init();
    Input::get();
    m_app = new MyApp();
    m_app->init();
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
    static int timeBaseFixed = -1;

    int time = glutGet(GLUT_ELAPSED_TIME);
    if (timeBase < 0)
    {
        timeBase = time;
        timeBaseFixed = time;
    }

    int dt = time - timeBase;
    m_app->update(dt);
    timeBase = time;

    static int fixedTimer = 0;;
    fixedTimer += time;
    if (fixedTimer >= FIXED_TIMER_FREQ)
    {
        fixedTimer = 0;
        int dtFixed = time - timeBaseFixed;
        m_app->fixedUpdate(dtFixed);
        timeBaseFixed = time;
    }
}

void Application::onRender()
{
    m_app->render();
}

void Application::onReshape(int width, int height)
{
    GRAPHICS.onReshape(width, height);
}

static Input_Class::Key convertKey(unsigned char key)
{
    switch (key)
    {
    case 0x61: return Input_Class::Left;
    case 0x64: return Input_Class::Right;
    case 0x68: return Input_Class::Attack;
    case 0x6a: return Input_Class::Jump;
    case 0x6b: return Input_Class::Freeze;
    }

    return Input_Class::None;
}

void Application::onKeyUp(unsigned char key, int x, int y)
{
    (void) x;
    (void) y;
    Input::get().release(convertKey(key));
}

void Application::onKeyDown(unsigned char key, int x, int y)
{
    (void) x;
    (void) y;
    Input::get().press(convertKey(key));
}
