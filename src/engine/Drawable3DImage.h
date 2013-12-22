#pragma once

#include <string>
#include "Drawable3D.h"

class Drawable3DImage : public Drawable3D
{
    std::string m_group;
    std::string m_name;

public:
    Drawable3DImage();
    virtual ~Drawable3DImage() override;

    virtual void render() const override;
    void setImage(const std::string& group, const std::string& name);
};
