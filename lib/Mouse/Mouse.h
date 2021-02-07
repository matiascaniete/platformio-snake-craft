#ifndef MOUSE_H
#define MOUSE_H

#include <Adafruit_PCD8544.h>
#include "Snake.h"
#include "Position.h"

class Mouse
{
private:
    uint8_t boxW, boxH;
    bool isAlive = false;

public:
    uint8_t killed = 0;
    Position position;
    uint8_t radius = 3;
    uint8_t stepSize;
    void init(uint8_t boxW, uint8_t boxH, uint8_t stepSize);
    void born();
    void kill();
    void draw(Adafruit_PCD8544 &display);
    bool isEatenBy(Snake &snake);
};

#endif