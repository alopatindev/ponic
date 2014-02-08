#pragma once

#include "misc/Singleton.h"
#include <unordered_map>
#include <string>

class AnimationManager_Class
{
    struct Data
    {
        int framesNumber;
        int fps;
    };

    std::unordered_map<std::string,
                       std::unordered_map<std::string, Data>> m_groupsDatas;
public:
    AnimationManager_Class();
    virtual ~AnimationManager_Class();

    void getData(const std::string& group,
                 const std::string& name,
                 int& framesNumber,
                 int& fps);
};

typedef Singleton<AnimationManager_Class> AnimationManager;
