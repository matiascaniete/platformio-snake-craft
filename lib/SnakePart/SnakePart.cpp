#include "SnakePart.h"

bool SnakePart::intersects(SnakePart &snakePart)
{
    return snakePart.inside(*this) || this->inside(snakePart);
}

bool SnakePart::inside(SnakePart &snakePart)
{
    if (snakePart.position.x <= position.x + radius &&
        snakePart.position.x >= position.x - radius &&
        snakePart.position.y <= position.y + radius &&
        snakePart.position.y >= position.y - radius)
    {
        return true;
    }

    return false;
}
