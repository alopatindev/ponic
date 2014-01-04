#include "Player.h"
#include <Graphics.h>

Player::Player()
{
    setImage("game_common", "horse_stands");
    setPosition(-0.5f, -0.5f, -0.6f);
    //setSize(0.5f, 0.5f);
    //setCenter(0.5f, 0.5f);
    //setOpacity(1.0f);
}

Player::~Player()
{
}

void Player::update(int dt)
{
}

void Player::fixedUpdate(int dt)
{
}

void Player::render() const
{
    Drawable3DImage::render();

#ifdef _DEBUG
    GRAPHICS.drawRectangle3D(
        m_pos.x, m_pos.y, m_pos.z,
        m_size.x, m_size.y,
        0.4f, 0.0f, 0.0f,
        0.7f);
#endif
}
