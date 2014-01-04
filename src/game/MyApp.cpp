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

void MyApp::update(int dt)
{
    m_scene.update(dt);
    EFFECTS.update(dt);
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
        CAMERA.update();
    GRAPHICS.endFrame();
    GRAPHICS.forceRedraw();
}
