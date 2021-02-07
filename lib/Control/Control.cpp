#include "Control.h"

Control::Control(){}

void Control::initIR(uint8_t irPin)
{
    ir = new IRrecv(irPin);
    ir->enableIRIn();  // Start the receiver
    ir->blink13(true); // Enable feedback LED
}

void Control::initJoystic(uint8_t xPin, uint8_t yPin, uint8_t btnPin)
{
    this->xPin = xPin;
    this->yPin = yPin;
    this->btn = new ezButton(btnPin);
}

uint32_t Control::readIR()
{
    decode_results results;

    if (ir->decode(&results))
    {
        Serial.println(results.value, HEX);
        ir->resume(); // Receive the next value
    }

    return results.value;
}

uint8_t Control::actionFromIR()
{
    // Códigos Sony DVD RMT-D178P
    switch (readIR())
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

    return 0;
}
/*
void Control::senseIRRemoteTV(uint8_t playerIndex, uint32_t value)
{
    // Códigos Sony TV RMT-TX300E
    switch (value)
    {

    case 0x2F0:
        player[1].up();
        break;
    case 0xAF0:
        player[1].down();
        break;
    case 0x2D0:
        player[1].left();
        break;
    case 0xCD0:
        player[1].right();
        break;
    case 0xA70:
        player[1].center();
        break;

    default:
        break;
    }
}
*/

uint8_t Control::actionFromJoystic()
{
    btn->loop();

    int joysticX = analogRead(xPin);
    int joysticY = analogRead(yPin);

    if (joysticX < JOY_MID - JOY_THR)
    {
        return RIGHT;
    }

    if (joysticX > JOY_MID + JOY_THR)
    {
        return LEFT;
    }

    if (joysticY > JOY_MID + JOY_THR)
    {
        return DOWN;
    }

    if (joysticY < JOY_MID - JOY_THR)
    {
        return UP;
    }

    if (btn->isPressed())
    {
        return CENTER;
    }

    return 0;
}
