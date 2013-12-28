#include "Player.h"

Player::Player()
{
    setImage("game_common", "horse_stands");
    setPosition(-0.5f, -0.5f, -1.2f);
    setSize(0.5f, 0.5f);
    //setAngle(90.0f);
    setCenter(0.5f, 0.5f);
    setScaleFactor(2.0f);
    setOpacity(0.30f);
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
}
