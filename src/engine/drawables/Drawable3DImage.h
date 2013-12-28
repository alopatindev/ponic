#pragma once

#include "Drawable3D.h"
#include <string>

class Drawable3DImage : public Drawable3D
{
    std::string m_group;
    std::string m_name;

public:
    Drawable3DImage();
    virtual ~Drawable3DImage();

    virtual void render() const;
    void setImage(const std::string& group, const std::string& name);
};
