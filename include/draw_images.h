// this file is auto generated. Do not change, changes will be undone on update.

#ifndef DRAW_IMAGES_H
#define DRAW_IMAGES_H

#include <Arduino.h>
#include "displayFunctions.h"
// Include all data, contains size definitions and data
#include "data\android.h"
#include "data\android2.h"
#include "data\bang.h"
#include "data\boat.h"
#include "data\boat2.h"
#include "data\boat3.h"
#include "data\broccoli.h"
#include "data\broccoli2.h"
#include "data\car.h"
#include "data\cat_walking.h"
#include "data\cat_walking2.h"
#include "data\crosshair.h"
#include "data\cyborg.h"
#include "data\diode.h"
#include "data\diode_led.h"
#include "data\electric.h"
#include "data\eye1.h"
#include "data\eye2.h"
#include "data\eye3.h"
#include "data\fries.h"
#include "data\gaming.h"
#include "data\graduated.h"
#include "data\icecream.h"
#include "data\icecream2.h"
#include "data\kano.h"
#include "data\mouse.h"
#include "data\nuke.h"
#include "data\pink_pant.h"
#include "data\rain.h"
#include "data\rowing.h"
#include "data\samsung.h"
#include "data\shock.h"
#include "data\speaker.h"
#include "data\star.h"
#include "data\target.h"
#include "data\target2.h"
#include "data\target3.h"
#include "data\transistor.h"
#include "data\tv.h"


// All functions to display the bitmaps
void display_android();
void display_android2();
void display_bang();
void display_boat();
void display_boat2();
void display_boat3();
void display_broccoli();
void display_broccoli2();
void display_car();
void display_cat_walking();
void display_cat_walking2();
void display_crosshair();
void display_cyborg();
void display_diode();
void display_diode_led();
void display_electric();
void display_eye1();
void display_eye2();
void display_eye3();
void display_fries();
void display_gaming();
void display_graduated();
void display_icecream();
void display_icecream2();
void display_kano();
void display_mouse();
void display_nuke();
void display_pink_pant();
void display_rain();
void display_rowing();
void display_samsung();
void display_shock();
void display_speaker();
void display_star();
void display_target();
void display_target2();
void display_target3();
void display_transistor();
void display_tv();


// Functions to draw the bitmaps at x,y
mysize draw_android(int x, int y);
mysize draw_android2(int x, int y);
mysize draw_bang(int x, int y);
mysize draw_boat(int x, int y);
mysize draw_boat2(int x, int y);
mysize draw_boat3(int x, int y);
mysize draw_broccoli(int x, int y);
mysize draw_broccoli2(int x, int y);
mysize draw_car(int x, int y);
mysize draw_cat_walking(int x, int y);
mysize draw_cat_walking2(int x, int y);
mysize draw_crosshair(int x, int y);
mysize draw_cyborg(int x, int y);
mysize draw_diode(int x, int y);
mysize draw_diode_led(int x, int y);
mysize draw_electric(int x, int y);
mysize draw_eye1(int x, int y);
mysize draw_eye2(int x, int y);
mysize draw_eye3(int x, int y);
mysize draw_fries(int x, int y);
mysize draw_gaming(int x, int y);
mysize draw_graduated(int x, int y);
mysize draw_icecream(int x, int y);
mysize draw_icecream2(int x, int y);
mysize draw_kano(int x, int y);
mysize draw_mouse(int x, int y);
mysize draw_nuke(int x, int y);
mysize draw_pink_pant(int x, int y);
mysize draw_rain(int x, int y);
mysize draw_rowing(int x, int y);
mysize draw_samsung(int x, int y);
mysize draw_shock(int x, int y);
mysize draw_speaker(int x, int y);
mysize draw_star(int x, int y);
mysize draw_target(int x, int y);
mysize draw_target2(int x, int y);
mysize draw_target3(int x, int y);
mysize draw_transistor(int x, int y);
mysize draw_tv(int x, int y);


#define NUM_POINTERS 39

void display_all_images(int delay_ms);

#endif

