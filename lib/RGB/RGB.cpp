#include "RGB.h"

RGB::RGB()
{
}

void RGB::init(uint8_t pin)
{
    pixels = new Adafruit_NeoPixel(NUMPIXELS, pin);
    pixels->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels->clear();
    pixels->show();
}

void RGB::hex(uint32_t c)
{
    pixels->clear();
    
    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels->setPixelColor(i, c);
    }
    
    pixels->show(); // Send the updated pixel colors to the hardware.
}

void RGB::scores(int score0, int score1)
{
    int maxInt = 64;
    int minInt = 0;

    pixels->clear();

    long pixelHue1 = micros() / 50;

    for (int i = 0; i < 4; i++)
    {
        int pixelIntensity1 = i < (score1 % 5) ? maxInt : minInt;
        int pixelIntensity0 = i < (score0 % 5) ? maxInt : minInt;

        pixels->setPixelColor(i, pixels->ColorHSV(pixelHue1, 255, pixelIntensity1));
        pixels->setPixelColor(7 - i, pixels->ColorHSV(pixelHue1, 255, pixelIntensity0));
    }

    pixels->show(); // Send the updated pixel colors to the hardware.
}
