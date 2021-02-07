#ifndef SNAKE_H
#define SNAKE_H

#include <Adafruit_PCD8544.h>
#include "SnakePart.h"
#include "Position.h"
#include "Player.h"

#define MAX_LENGTH 16
#define INI_LENGTH 5

class Snake
{

private:
    uint8_t stepSize = 4;
    uint8_t length = INI_LENGTH;
    uint16_t color = BLACK;
    SnakePart parts[MAX_LENGTH];
    uint8_t boxW, boxH;
    Position initPosition;
    Player player;

public:
    uint8_t killed = 0;
    uint8_t ate = 0;
    void init(uint8_t boxW, uint8_t boxH, uint8_t stepSize, uint8_t color, Position initPosition);
    void sense(bool upDir, bool downDir, bool leftDir, bool rightDir);
    void move(int dx, int dy);
    uint8_t radius(uint8_t partIndex);
    void draw(Adafruit_PCD8544 &display);
    void grow();
    void kill();
    void reset();
    bool isEatenBy(Snake &snake);
    SnakePart head();
    SnakePart teleport(SnakePart &part);
    void assignPlayer(Player &Player);
    Player getPlayer();
};

#endif
