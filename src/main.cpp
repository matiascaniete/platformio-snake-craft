#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Adafruit_NeoPixel.h>
#include <Tasker.h>

#include <Game.h>
#include <Notes.h>
#include <RGB.h>
#include <Control.h>

// Software SPI (slower updates, more flexible pin options):

//Nokia 5110 LCD Module Pins
#define BL_PIN 2  // Backlight
#define LCD_CLK 3 // Clock
#define LCD_DIN 4 // Data in
#define LCD_DC 5  // Data/Command select
#define LCD_CS 6  // Chip select
#define LCD_RST 7 // Reset

// Joystic Axis XY and Switch Pins
#define X_PIN A2
#define Y_PIN A3
#define S_PIN A1

// IR Remote Receiver
#define IR_PIN 10

// Random Seed
#define RANDOM_PIN A5

// RGB Led Strip
#define RGB_PIN 9

// Speaker
#define SPK_PIN 8

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_CLK, LCD_DIN, LCD_DC, LCD_CS, LCD_RST);
Adafruit_NeoPixel pixels(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

Tasker tasker;

Game game;
RGB rgb;
Control control;

void startRefresh(uint8_t level);
void refreshScreen();
void stopRefresh();

void setup()
{
  Serial.begin(9600);

  randomSeed(analogRead(RANDOM_PIN));

  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, 1);

  pinMode(SPK_PIN, OUTPUT);

  //pinMode(LED_BUILTIN, OUTPUT);

  control.initJoystic(X_PIN, Y_PIN, S_PIN);
  control.initIR(IR_PIN);
  rgb.init(pixels);
  game.init(display);
  game.welcome();

  startRefresh(game.getLevel());
}

void blinkAlert(uint16_t frec = 440, uint16_t wait = 100, uint32_t color = 0x888888)
{
  tone(SPK_PIN, frec);
  rgb.hex(color);
  delay(wait);

  rgb.hex(0x000000);
  noTone(SPK_PIN);
  delay(wait);
}

void roundOver()
{
  blinkAlert(NOTE_C4, 150, 0x440000);
  blinkAlert(NOTE_B3, 150, 0x880000);
  blinkAlert(NOTE_AS3, 150, 0xFF0000);
}

void success()
{
  blinkAlert(NOTE_C7, 25, 0xFFFFFF);
  blinkAlert(NOTE_E7, 25, 0xFFFFFF);
  blinkAlert(NOTE_G7, 25, 0xFFFFFF);
}

void refreshScores()
{
  rgb.scores(game.getScore(0), game.getScore(1));
}

void startRefresh(uint8_t level)
{
  int gameDelay = 200 - 10 * (game.getLevel() - 1);
  tasker.setInterval(refreshScreen, gameDelay);
  tasker.setInterval(refreshScores, 50);
}

void refreshScreen()
{
  display.clearDisplay();

  if (game.draw())
  {
    stopRefresh();
    roundOver();
    game.restart();
    startRefresh(game.getLevel());
  }

  if (game.someoneAte())
  {
    stopRefresh();
    success();
    startRefresh(game.getLevel());
  }
}

void stopRefresh()
{
  tasker.cancel(refreshScreen);
}

void loop()
{
  tasker.loop();

  game.doAction(0, control.actionFromJoystic());
  game.doAction(1, control.actionFromIR());
}
