/**
 * To put ESP-01 in flash mode: https://medium.com/@aallan/getting-started-with-the-esp8266-270e30feb4d1
 * Boot in flash mode: upload program
 * Then reboot without GPIO2 HIGH and GPIO0 LOW, to start run mode
 * Always have CH_PD HIGH
 * 
 * 
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266TrueRandom.h>
#include "displayFunctions.h"
#include "draw_images.h"

// init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 4000000UL, 400000UL); // try extra 0?
// array with function pointers
extern mysize (*FunctionPointers[])(int, int);

void setup()
{
    // Serial.begin(115200);
    Wire.begin(2, 0); // start I2C
    InitDisplay();
    display.clearDisplay();
}

void loop()
{
    // Serial.print("looping\n");
    // display_all_images(500);

    // scrollBitmap(1, draw_android);
    // scrollBitmap(2, draw_android);
    // scrollBitmap(3, draw_android);
    // scrollBitmap(4, draw_android);
    int dir = ESP8266TrueRandom.random(1, 9); //
    int fun = ESP8266TrueRandom.random(0, NUM_POINTERS);
    scrollBitmap(dir, FunctionPointers[fun]);
}