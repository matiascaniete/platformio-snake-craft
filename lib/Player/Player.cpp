#include "Player.h"

Player::Player() {}

int Player::getDX()
{
    return dx;
}

int Player::getDY()
{
    return dy;
}

void Player::up()
{
    dx = 0;
    dy = -1;
}

void Player::down()
{
    dx = 0;
    dy = 1;
}

void Player::left()
{
    dx = -1;
    dy = 0;
}

void Player::right()
{
    dx = 1;
    dy = 0;
}

void Player::center()
{
    dx = 0;
    dy = 0;
}

void Player::loose()
{
    looses++;
}

void Player::win()
{
    wins++;
}

int Player::getScore()
{
    return wins - looses;
}
