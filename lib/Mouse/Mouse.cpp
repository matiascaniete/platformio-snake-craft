#include "Mouse.h"

void Mouse::init(uint8_t boxW, uint8_t boxH, uint8_t stepSize)
{
    this->stepSize = stepSize;
    this->boxW = boxW;
    this->boxH = boxH;
    this->born();
}

void Mouse::kill()
{
    isAlive = false;
    killed++;
}

void Mouse::born()
{
    position.x = random(stepSize, boxW - stepSize);
    position.y = random(stepSize, boxH - stepSize);
    isAlive = true;
}

void Mouse::draw(Adafruit_PCD8544 &display)
{
    if (isAlive)
    {
        display.drawCircle(position.x, position.y, radius, BLACK);
    }
}

bool Mouse::isEatenBy(Snake &snake)
{
    if (isAlive &&
        snake.head().position.x <= position.x + radius &&
        snake.head().position.x >= position.x - radius &&
        snake.head().position.y <= position.y + radius &&
        snake.head().position.y >= position.y - radius)

    {
        return true;
    }

    return false;
}
