#include "IR.h"

IR::IR(){};

void IR::init(IRrecv &ir)
{
    this->ir = &ir;
    this->ir->enableIRIn();  // Start the receiver
    this->ir->blink13(true); // Enable feedback LED
}

uint32_t IR::read()
{
    decode_results results;

    if (ir->decode(&results))
    {
        Serial.println(results.value, HEX);
        ir->resume(); // Receive the next value
    }

    return results.value;
}

void IR::loop()
{
    value = read();
}

uint8_t IR::action()
{
    // Códigos Sony DVD RMT-D178P
    switch (value)
    {
    case 0x9EB92:
        return UP;
        break;
    case 0x5EB92:
        return DOWN;
        break;
    case 0xDEB92:
        return LEFT;
        break;
    case 0x3EB92:
        return RIGHT;
        break;
    case 0xD0B92:
        return CENTER;
        break;

    default:
        break;
    }
}
