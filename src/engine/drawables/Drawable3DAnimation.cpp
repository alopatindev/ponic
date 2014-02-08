#include "Drawable3DAnimation.h"
#include <engine/Assert.h>
#include <engine/AnimationManager.h>

Drawable3DAnimation::Drawable3DAnimation()
    : m_currentFrame(0)
    , m_fps(0)
    , m_framesNumber(0)
    , m_timer(0)
{
}

Drawable3DAnimation::~Drawable3DAnimation()
{
}

void Drawable3DAnimation::setAnimation(const std::string& group,
                                       const std::string& name)
{
    LOGI("setAnimation group='%s' name='%s'", group.c_str(), name.c_str());

    AnimationManager::get().getData(group, name, m_framesNumber, m_fps);

    m_currentFrame = 0;
    m_timer = 0;

    ASSERT(m_framesNumber > 0, "framesNumber should be > 0");
    ASSERT(m_fps > 0, "fps should be > 0");

    m_frames.clear();
    m_frames.resize(m_framesNumber);

    static const size_t digitsNumber = 2;
    char buf[digitsNumber + 1];
    for (int i = 0; i < m_framesNumber; ++i)
    {
        if (std::snprintf(buf, digitsNumber + 1, "%02d", i) > 0)
        {
            m_frames[i] = name + std::string(buf);
        }
    }

    setImage(group, m_frames[0]);
}

void Drawable3DAnimation::update(int dt)
{
    m_timer += dt;
    if (m_timer >= 1000 / m_fps)
    {
        m_timer = 0;
        ++m_currentFrame;
        if (m_currentFrame >= m_framesNumber)
            m_currentFrame = 0;

        setImage(m_frames[m_currentFrame]);
    }
}
