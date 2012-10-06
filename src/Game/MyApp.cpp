#include "MyApp.h"
#include <Graphics.h>
#include <ImageManager.h>
#include <System.h>

MyApp::MyApp()
{
    m_angle = 0.0f;
    m_scale = 1.0f;
    m_timer = 0;
}

MyApp::~MyApp()
{
}

void MyApp::init()
{
    GRAPHICS.init();
    ImageManager::getInstance().parseAtlasXML("atlases/atlasDictionary.xml");
    ImageManager::getInstance().loadGroup("game_common");
}

void MyApp::destroy()
{
    ImageManager::getInstance().freeAllGroups();
}

void MyApp::update()
{
    m_timer += SYSTEM.getDt();
    
    static float sign = 1;
    if (m_timer >= 10)
    {
        m_timer = 0;
        m_angle += 5.0f;
        m_scale += 0.1f * sign;
        if (m_scale >= 2.0f || m_scale <= 0.5f)
            sign = -sign;
    }
}

void MyApp::render() const
{
    GRAPHICS.startFrame();

        GRAPHICS.start3D();

            GRAPHICS.drawImage3D(
                "game_common",
                //"horse_runs01",
                "horse_stands",
                -0.5f, -0.5f, -1.8f,
                0.5f, 0.5f,
                m_angle,
                0.5f, 0.5f,
                m_scale
            );

            GRAPHICS.drawImage3D(
                "game_common",
                "horse_runs01",
                -0.5f, -0.5f, -1.4f,
                1.0f, 1.0f
            );
        GRAPHICS.end3D();

        /*GRAPHICS.start2D();
        GRAPHICS.drawImage2D(
            "game_common",
            "horse_stands",
            0.0f, 0.0f,
            1.0f/2, 1.0f/2
        );
        GRAPHICS.end2D();*/

    GRAPHICS.endFrame();
    GRAPHICS.forceRedraw();
}
