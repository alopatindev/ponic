#include "Drawable3DImage.h"
#include <engine/Graphics.h>

Drawable3DImage::Drawable3DImage()
    : m_horizMirrored(false)
    , m_ignoreCamera(false)
{
}

Drawable3DImage::~Drawable3DImage()
{
}

void Drawable3DImage::render() const
{
    if (!getVisible())
        return;

    GRAPHICS.drawImage3D(
        m_group,
        m_name,
        m_pos.x, m_pos.y, m_pos.z,
        m_size.x, m_size.y,
        m_angle,
        m_center.x, m_center.y,
        m_scaleFactor,
        m_opacity,
        m_horizMirrored,
        m_ignoreCamera
    );
}

void Drawable3DImage::setImage(const std::string& group, const std::string& name)
{
    m_group = group;
    m_name = name;
}
