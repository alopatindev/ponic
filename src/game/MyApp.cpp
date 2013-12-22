#include "MyApp.h"
#include "Effects.h"
#include <Graphics.h>
#include <ImageManager.h>
#include <FontManager.h>
#include <System.h>
#include <Camera.h>
#include <Log.h>

#include "Player.h"
#include <engine/physics/Drawable3DGrid.h>

MyApp::MyApp()
{
    /*m_angle = 0.0f;
    m_scale = 1.0f;
    m_timer = 0;*/
}

MyApp::~MyApp()
{
}

void MyApp::init()
{
    GRAPHICS.init();
    ImageManager::getInstance().parseAtlasXML("atlases/atlasDictionary.xml");
    ImageManager::getInstance().loadGroup("game_common");
    FontManager::getInstance().loadFont("font.ttf", 16, 24, 38, 0);
    ImageManager::getInstance().loadGroup("test1");
    GridManager::getInstance().loadGrid("level1");
}

void MyApp::destroy()
{
    ImageManager::getInstance().freeAllGroups();
}

void MyApp::update()
{
    //m_timer += SYSTEM.getDt();

    //EFFECTS.startFadeIn();
    //EFFECTS.startFadeOut();
    EFFECTS.update(SYSTEM.getDt());
    
    /*static float sign = 1;
    if (m_timer >= 10)
    {
        //CAMERA.lookAt(CAMERA.getX() - 0.01f, 0.0f);
        m_timer = 0;
        m_angle += 5.0f;
        m_scale += 0.1f * sign;
        if (m_scale >= 2.0f || m_scale <= 0.5f)
            sign = -sign;
    }*/
}

void MyApp::render() const
{
    static Player player;
    static Drawable3DGrid grid;

    GRAPHICS.startFrame();
        player.render();
        grid.render();
        /*GRAPHICS.drawImage3D(
            "game_common",
            "back",
            -0.5f, -0.5f, -5.0f,
            1.0f, 1.0f,

            0.0f,
            0.0f, 0.0f,
            1.0f * 15.0f,
            1.0f
        );

        GRAPHICS.drawImage3D(
            "game_common",
            //"horse_runs01",
            "horse_stands",
            -0.5f, -0.5f, -1.2f,
            0.5f, 0.5f,
            90.0f,
            0.5f, 0.5f,
            2.0f,
            0.30f
        );

        GRAPHICS.drawImage3D(
            "game_common",
            //"horse_runs01",
            "horse_stands",
            -0.5f, -0.5f, -1.8f,
            0.5f, 0.5f,
            m_angle,
            0.5f, 0.5f,
            m_scale,
            0.2f
        );

        GRAPHICS.drawImage2D(
            "game_common",
            "horse_runs01",
            -1.0f, -0.5f,
            1.0f, 1.0f
        );

        GRAPHICS.drawImage3D(
            "test1",
            "stacktrace",
            0.0f, 0.0f, -1.8f,
            //0.0f, 0.0f, -9.9f,
            1.0f, 1.0f,

            30.0f
        );*/

        //CAMERA.lookAt(0.2f, 0.0f);
        //CAMERA.setZoom(-5.0f);
        EFFECTS.render();
        CAMERA.update();
    GRAPHICS.endFrame();
    GRAPHICS.forceRedraw();
}
