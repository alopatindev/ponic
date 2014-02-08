#include "AnimationManager.h"
#include <engine/System.h>
#include <engine/Log.h>
#include <fstream>
#include <sstream>

AnimationManager_Class::AnimationManager_Class()
{
    LOGI("initializing AnimationManager");

    std::string fn(SYSTEM.getResourcesPath() + "animations.txt");
    std::ifstream file(fn);

    if (file.fail())
    {
        LOGE("file %s cannot be open", fn.c_str());
        return;
    }

    Data data;
    std::string group;
    std::string name;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> group;
        iss >> name;
        iss >> data.fps;
        iss >> data.framesNumber;
        m_groupsDatas[group][name] = data;
        LOGI(" '%s' '%s' fps=%d framesNumber=%d",
             group.c_str(), name.c_str(), data.fps, data.framesNumber);
    }
}

AnimationManager_Class::~AnimationManager_Class()
{
}

void AnimationManager_Class::getData(const std::string& group,
                                     const std::string& name,
                                     int& framesNumber,
                                     int& fps)
{
    const Data& data = m_groupsDatas[group][name];
    framesNumber = data.framesNumber;
    fps = data.fps;
}
