#include <Arduino.h>
#include <Wire.h>

#include <Game.h>
#include <Control.h>

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

//Adafruit_PCD8544 display = Adafruit_PCD8544();

Game game;
Control control;

void setup()
{
  Serial.begin(9600);

  randomSeed(analogRead(RANDOM_PIN));

  control.initJoystic(X_PIN, Y_PIN, S_PIN);
  control.initIR(IR_PIN);

  game.initDisplay(LCD_CLK, LCD_DIN, LCD_DC, LCD_CS, LCD_RST, BL_PIN);
  game.initSpeaker(SPK_PIN);
  game.initRGBStrip(RGB_PIN);
  
  game.welcome();
  game.start();
}

void loop()
{
  game.loop();

  game.doAction(0, control.actionFromJoystic());
  game.doAction(1, control.actionFromIR());
}
