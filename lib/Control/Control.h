#ifndef CONTROL_H
#define CONTROL_H

#include <IRremote.h>
#include <ezButton.h>

#define JOY_MID 520
#define JOY_THR 200

#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4
#define CENTER 5

class Control
{
private:
    IRrecv *ir;
    ezButton *btn;
    uint8_t xPin;
    uint8_t yPin;

public:
    Control();
    void initIR(uint8_t irPin);
    void initJoystic(uint8_t xPin, uint8_t yPin, uint8_t btnPin);
    uint32_t readIR();
    uint8_t actionFromIR();
    uint8_t actionFromJoystic();
};

#endif