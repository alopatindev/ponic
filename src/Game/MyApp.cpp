#include "MyApp.h"
#include <Graphics.h>
#include <ImageManager.h>

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
}

void MyApp::destroy()
{
    ImageManager::getInstance().freeAllGroups();
}

void MyApp::update()
{
}

void MyApp::render() const
{
    GRAPHICS.prepareFrame();
    GRAPHICS.drawImage(
        "game_common",
        //"horse_runs01",
        "horse_stands",
        0.0f,
        0.0f,
        GRAPHICS.getWidth() / 2,
        GRAPHICS.getHeight() / 2
    );
    GRAPHICS.endFrame();
}
