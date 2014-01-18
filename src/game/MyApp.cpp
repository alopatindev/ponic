#include "MyApp.h"
#include "Effects.h"
#include <Graphics.h>
#include <ImageManager.h>
#include <FontManager.h>
#include <System.h>
#include <Camera.h>
#include <Log.h>
#include <GridManager.h>

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

void MyApp::init()
{
    //GRAPHICS.init();
    ImageManager::get().parseAtlasXML("atlases/atlasDictionary.xml");
    ImageManager::get().loadGroup("game_common");
    FontManager::get().loadFont("font.ttf", 16, 24, 38, 0);
    GridManager::get().loadGrid("level1");
    CAMERA.zoom(CAMERA_DEFAULT_ZOOM);
    CAMERA.setLookAtPlayer(true);
}

void MyApp::destroy()
{
    ImageManager::get().freeAllGroups();
}

void MyApp::update(int dt)
{
    m_scene.update(dt);
    EFFECTS.update(dt);
    float playerSpeed = glm::length(m_scene.getSpeed());
    CAMERA.setPlayerSpeed(playerSpeed);
    CAMERA.update(dt);
}

void MyApp::fixedUpdate(int dt)
{
    m_scene.fixedUpdate(dt);
}

void MyApp::render() const
{
    GRAPHICS.startFrame();
        m_scene.render();
        EFFECTS.render();
    GRAPHICS.endFrame();
    GRAPHICS.forceRedraw();
}
