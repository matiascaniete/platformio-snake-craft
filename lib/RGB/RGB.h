#ifndef RGB_H
#define RGB_H

#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 8

class RGB
{
private:
    Adafruit_NeoPixel *pixels;

public:
    RGB();
    void init(uint8_t pin);
    void hex(uint32_t c);
    void scores(int score0, int score1);
};

#endif