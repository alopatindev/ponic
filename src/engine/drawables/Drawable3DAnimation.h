#pragma once

#include "Drawable3DImage.h"
#include <vector>

class Drawable3DAnimation : public Drawable3DImage
{
    std::vector<std::string> m_frames;
    int m_currentFrame;
    int m_fps;
    int m_framesNumber;
    int m_timer;

public:
    Drawable3DAnimation();
    virtual ~Drawable3DAnimation();

    void setAnimation(const std::string& group,
                      const std::string& name,
                      int framesNumber,
                      int fps);
    virtual void update(int dt);
};
