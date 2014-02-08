#pragma once

#include "Drawable3D.h"
#include <string>

class Drawable3DImage : public Drawable3D
{
    std::string m_group;
    std::string m_name;
    bool m_horizMirrored;
    bool m_ignoreCamera;

public:
    Drawable3DImage();
    virtual ~Drawable3DImage();

    virtual void render() const;
    virtual void fixedUpdate(int dt) {};
    virtual void update(int dt) {};

    void setImage(const std::string& group, const std::string& name);
    void setImage(const std::string& name);

    void setHorizMirrored(bool mirrored)
    {
        m_horizMirrored = mirrored;
    }
    void setIgnoreCamera(bool ignoreCamera)
    {
        m_ignoreCamera = ignoreCamera;
    }
};
