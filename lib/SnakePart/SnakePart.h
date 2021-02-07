#ifndef SNAKEPART_H
#define SNAKEPART_H

#include "Position.h"

class SnakePart
{
public:
    Position position;
    int radius = 3;
    bool inside(SnakePart &snakePart);
    bool intersects(SnakePart &snakePart);
};

#endif