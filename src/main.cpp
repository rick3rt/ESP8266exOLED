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
#include "displayFunctions.h"

// init display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000UL, 100000UL);

void setup()
{
    Serial.begin(115200);
    Wire.begin(2, 0); // start I2C
    InitDisplay();
    delay(2000);
    display.clearDisplay();
}

int disparr[SCREEN_WIDTH] = {0};

void loop()
{
    Serial.print("looping\n");
    delay(1000);
    testdrawroundrect();
}