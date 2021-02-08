#ifndef GAME_H
#define GAME_H

#include <Adafruit_PCD8544.h>

#include <Notes.h>

#include "Snake.h"
#include "Mouse.h"
#include "Player.h"
#include "Control.h"
#include "RGB.h"
#include <AsyncDelay.h>

#define FLAG_SOMEONE_ATE 0

class Game
{
private:
    Adafruit_PCD8544 *display;
    RGB *rgb;
    uint8_t level = 1;
    uint8_t stepSize = 4;
    Player player[2];
    Snake snake[2];
    Mouse mouse;
    AsyncDelay displayTimer;
    AsyncDelay rgbTimer;
    uint8_t spkPin;
    bool flags[1];

public:
    Game();
    void initDisplay(int8_t SCLK, int8_t DIN, int8_t DC, int8_t CS, int8_t RST, uint8_t BL);
    void initSpeaker(uint8_t pin);
    void initRGBStrip(uint8_t pin);
    
    void welcome();
    void start();
    void restart();

    void roundOver();
    void success();

    void updateRefreshRate();
    void refreshScreen();
    void refreshScores();
    void blinkAlert(uint16_t frec = 440, uint16_t wait = 100, uint32_t color = 0x888888);
    void loop();

    void doAction(uint8_t playerIndex, uint8_t action);
    bool compute(Snake &snake);
    bool compute(Snake &snake, Snake &otherSnake);
    bool draw();
    int getScore(uint8_t snakeIndex);
    bool someoneAte();
    uint8_t getLevel();
};

#endif