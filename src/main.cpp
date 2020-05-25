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
#include "names.h"

// init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 4000000UL, 400000UL); // try extra 0?

// pointer arrays to functions
extern mysize (*ImgDrawPointers[])(int, int);
extern void (*BlinkDrawPointers[])();
extern void (*StickDrawPointers[])();

void setup()
{
    Serial.begin(115200);
    Wire.begin(2, 0); // start I2C
    InitDisplay();
    display.clearDisplay();
}

void loop()
{
    display.clearDisplay();

    AnimateAllStick();
    AnimateAllBlink();
    whosNextAnimate();

    // generate some random numbers to see what to do
    int whatToDo = ESP8266TrueRandom.random(0, 7);
    switch (whatToDo)
    {
    case 1:
    {
        AnimateAllStick();
        break;
    }
    case 2:
    {
        AnimateAllBlink();
        break;
    }
    case 3:
    {
        whosNextAnimate();
        break;
    }
    case 4:
    {
        int dir = ESP8266TrueRandom.random(1, 9); // change drawing direction
        int fun = ESP8266TrueRandom.random(0, NUM_IMG_POINTERS);
        scrollBitmap(dir, ImgDrawPointers[fun]);
        break;
    }
    default:
        AnimateAllBlink();
        break;
    }
}

// TODO diagonal drawing center offset
// TODO run length endoding?
// TODO wifi, if not wifi, AP mode
// TODO save drawing as uint8_t array. (how to write from other program?)
// TODO file browser with upload
// TODO create web interface