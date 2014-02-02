#include "Background3D.h"
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/Log.h>

Background3D::Background3D()
{
    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_images[i].setImage("game_common", "background");
    }
}

Background3D::~Background3D()
{
}

void Background3D::render() const
{
    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_images[i].render();
    }
}

void Background3D::update(int dt)
{
    auto& grid = Drawable3DGrid::get();
    int curX = grid.getCursor().x;
    int frame = 0;
    frame = curX / (GRID_WIDTH / 1.3f);

    float size = m_images[0].getSize().x;
    float x = m_pos.x + size * float(IMAGES_NUMBER-1 + frame);
    if (x < -2.5f)
        frame += 3;
    else if (x < -1.7f)
        frame += 2;
    else if (x < -0.55f)
        ++frame;

    setPosition(
        -curX * grid.getTileWidth() + grid.getPosition().x,
        grid.getPosition().y - 0.09f,
        -0.7f);

    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_images[i].setPosition(
            m_pos.x + size * float(i + frame),
            m_pos.y,
            m_pos.z
        );
    }
}
