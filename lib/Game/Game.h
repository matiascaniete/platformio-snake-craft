#ifndef GAME_H
#define GAME_H

#include <Adafruit_PCD8544.h>
#include "Snake.h"
#include "Mouse.h"
#include "Player.h"
#include "Control.h"

#define FLAG_SOMEONE_ATE 0

class Game
{
private:
    uint8_t level = 1;
    int stepSize = 4;
    Player player[2];
    Snake snake[2];
    Mouse mouse;
    Adafruit_PCD8544 *display;
    bool flags[1];

public:
    Game();
    void init(Adafruit_PCD8544 &display);
    void welcome();
    void restart();
    //void senseJoystick(uint8_t playerIndex, int joystickX, int joystickY, bool button);
    //void senseIRRemoteDVD(uint8_t playerIndex, uint32_t value);
    //void senseIRRemoteTV(uint8_t playerIndex, uint32_t value);
    void doAction(uint8_t playerIndex, uint8_t action);
    bool compute(Snake &snake);
    bool compute(Snake &snake, Snake &otherSnake);
    bool draw();
    int getScore(uint8_t snakeIndex);
    bool someoneAte();
    uint8_t getLevel();
};

#endif