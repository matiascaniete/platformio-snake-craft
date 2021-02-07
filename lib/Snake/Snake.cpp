#include "Snake.h"

void Snake::init(uint8_t boxW, uint8_t boxH, uint8_t stepSize, uint8_t color, Position initPosition)
{
    this->boxW = boxW;
    this->boxH = boxH;
    this->color = color;
    this->initPosition = initPosition;

    this->reset();
}

void Snake::reset()
{
    length = INI_LENGTH;

    for (uint8_t i = 0; i < length; i++)
    {
        parts[i] = SnakePart();
        parts[i].position.x = initPosition.x;
        parts[i].position.y = initPosition.y;
    }
}

uint8_t Snake::radius(uint8_t partIndex)
{
    if (partIndex == 0)
    {
        return 3;
    }

    if (partIndex < length / 3)
    {
        return 2;
    }

    if (partIndex < 2 * length / 3)
    {
        return 1;
    }

    return 0;
}

void Snake::draw(Adafruit_PCD8544 &display)
{
    for (int i = length - 1; i >= 0; i--)
    {
        display.fillCircle(parts[i].position.x, parts[i].position.y, radius(i), color);
        display.drawCircle(parts[i].position.x, parts[i].position.y, radius(i), BLACK);
    }

    // Dibuja ojos
    display.drawPixel(parts[0].position.x - 1, parts[0].position.y, !color);
    display.drawPixel(parts[0].position.x - 2, parts[0].position.y, !color);
    display.drawPixel(parts[0].position.x + 1, parts[0].position.y, !color);
    display.drawPixel(parts[0].position.x + 2, parts[0].position.y, !color);
}

void Snake::move(int dx, int dy)
{
    for (uint8_t i = length - 1; i > 0; i--)
    {
        parts[i].position.x = parts[i - 1].position.x;
        parts[i].position.y = parts[i - 1].position.y;
    }

    parts[0].position.x += dx;
    parts[0].position.y += dy;

    parts[0] = teleport(parts[0]);
}

SnakePart Snake::teleport(SnakePart &part)
{
    if (part.position.y > boxH)
    {
        part.position.y = 0;
    }

    if (part.position.y < 0)
    {
        part.position.y = boxH;
    }

    if (part.position.x > boxW)
    {
        part.position.x = 0;
    }

    if (part.position.x < 0)
    {
        part.position.x = boxW;
    }

    return part;
}

SnakePart Snake::head()
{
    return parts[0];
}

void Snake::grow()
{
    ate++;
    if (length < MAX_LENGTH)
    {
        length++;
    }
}

void Snake::kill()
{
    reset();
    killed++;
}

bool Snake::isEatenBy(Snake &snake)
{
    SnakePart head = snake.head();
    uint8_t initAt = (this == &snake) ? 1 : 0;

    for (uint8_t i = initAt; i < length; i++)
    {
        if (parts[i].intersects(head))
        {
            return true;
        }
    }

    return false;
}

void Snake::assignPlayer(Player &player)
{
    this->player = player;
}

Player Snake::getPlayer()
{
    return player;
}
