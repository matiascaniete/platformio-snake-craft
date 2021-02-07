#ifndef IR_H
#define IR_H

#include <IRremote.h>

#define UP 1
#define RIGHT 2
#define LEFT 3
#define DOWN 4
#define CENTER 5

class IR
{
private:
    IRrecv *ir;
    uint32_t value;

public:
    IR();
    void init(IRrecv &ir);
    void loop();
    uint32_t read();
    uint8_t action();
};

#endif