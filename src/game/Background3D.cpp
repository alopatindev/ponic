#include "Background3D.h"
#include <engine/drawables/Drawable3DGrid.h>
#include <engine/Log.h>
#include <engine/Camera.h>

Background3D::Background3D()
{
    m_sky.setPosition(-0.5f, -0.59f, -0.7);
    m_sky.setSize(1.3f, 1.0f);
    m_sky.setImage("game_unfiltered", "background");
    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_layer0[i].setImage("game_common", "background_trees");
        m_layer1[i].setImage("game_common", "background_trees2");
        m_layer1[i].setSize(0.5f, 1.0f);
    }

    auto& grid = Drawable3DGrid::get();
    setPosition(grid.getPosition().x, grid.getPosition().y - 0.09f, -0.7f);
}

Background3D::~Background3D()
{
}

void Background3D::render() const
{
    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_layer1[i].render();
        m_layer0[i].render();
    }
    m_sky.render();
}

void Background3D::update(int dt)
{
    auto& grid = Drawable3DGrid::get();
    int curX = grid.getCursor().x;
    int frame0 = 0;
    int frame1 = 0;

    float imageSize0 = m_layer0[0].getSize().x;
    float imageSize1 = m_layer1[0].getSize().x;

    m_pos += m_speed * 0.2f;

    static const float speed0 = 1.0f;
    static const float speed1 = 1.08f;
    frame0 = int(-((m_pos.x-grid.getPosition().x) / imageSize0) * speed0);
    frame1 = int(-((m_pos.x-grid.getPosition().x) / imageSize1) * speed1);

    for (int i = 0; i < IMAGES_NUMBER; ++i)
    {
        m_layer0[i].setPosition(
            (m_pos.x + imageSize0 * float(i + frame0)) * speed0,
            m_pos.y,
            m_pos.z + 0.0001f
        );

        m_layer1[i].setPosition(
            (m_pos.x + imageSize1 * float(i + frame1)) * speed1,
            m_pos.y,
            m_pos.z + 0.0002f
        );
    }
}
