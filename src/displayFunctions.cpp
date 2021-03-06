#include "displayFunctions.h"
#include "draw_images.h"

// =============================================================================
// Init display
// =============================================================================

// void InitDisplay(byte address /* = 0x3C */)
void InitDisplay()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // Default Address 0x3D for 128x64 (I2C scanner returned 0x3C)
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("SSD1306 allocation failed");
        Serial.println("Display gaat niet aan?");
    }
    display.clearDisplay(); // hide adafruit boot...
    display.display();
}

// =============================================================================
// My own draw functions
// =============================================================================
void scrollBitmap(int dir, mysize (*funToDraw)(int x, int y))
{
    // dir: 1 left      to      right
    //      2 right     to      left
    //      3 top       to      bottom
    //      4 bottom    to      top

    // first get size
    mysize s = (*funToDraw)(0, 0);
    int width = s.w;
    int height = s.h;
    int margin = 5;

    // TODO: Diagonal movements offset of center
    switch (dir)
    {
    case 1:
        // left to right
        for (int x = -width - margin; x < SCREEN_WIDTH + margin; x++)
        {
            display.clearDisplay();
            (*funToDraw)(x, (64 - height) / 2); // call the drawfunction
            display.display();
        }
        break;
    case 2:
        // right to left
        for (int x = SCREEN_WIDTH + margin; x > -width - margin; x--)
        {
            display.clearDisplay();
            (*funToDraw)(x, (64 - height) / 2); // call the drawfunction
            display.display();
        }
        break;
    case 3:
        // top to bottom
        for (int y = -height - margin; y < SCREEN_HEIGHT + margin; y++)
        {
            display.clearDisplay();
            (*funToDraw)((128 - width) / 2, y); // call the drawfunction
            display.display();
        }
        break;
    case 4:
        // bottom to top
        for (int y = SCREEN_HEIGHT + margin; y > -height - margin; y--)
        {
            display.clearDisplay();
            (*funToDraw)((128 - width) / 2, y); // call the drawfunction
            display.display();
        }
        break;
    case 5:
        // diagonal top left to bottom right
        for (int x = -width - margin; x < SCREEN_WIDTH + margin; x++)
        {
            display.clearDisplay();
            (*funToDraw)(x, x / 2); // call the drawfunction
            display.display();
        }
    case 6:
        // bottom right to top left
        for (int x = SCREEN_WIDTH + margin; x > -width - margin; x--)
        {
            display.clearDisplay();
            (*funToDraw)(x, x / 2); // call the drawfunction
            display.display();
        }
        break;
    case 7:
        // bottom left to top right
        for (int x = -width - margin; x < SCREEN_WIDTH + margin; x++)
        {
            display.clearDisplay();
            (*funToDraw)(x, 64 - x / 2); // call the drawfunction
            display.display();
        }
        break;
    case 8:
        // top right to bottom left
        for (int x = SCREEN_WIDTH + margin; x > -width - margin; x--)
        {
            display.clearDisplay();
            (*funToDraw)(x, 64 - x / 2); // call the drawfunction
            display.display();
        }
        break;

        break;
    }
}

/*
display.setTextSize(1);              // Normal 1:1 pixel scale
display.setTextColor(SSD1306_WHITE); // Draw white text
display.setCursor(0, 0);             // Start at top-left corner
display.println(F("Hello, world!"));

display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
display.println(3.141592);

display.setTextSize(2); // Draw 2X-scale text
display.setTextColor(SSD1306_WHITE);
display.print(F("0x"));
display.println(0xDEADBEEF, HEX);
*/

String convertToString(const char *a, int size)
{
    int i;
    String s = "";
    for (i = 0; i < size; i++)
    {
        s = s + a[i];
    }
    return s;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize(int arr[], int n)
{
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n - 1; i > 0; i--)
    {
        long j = ESP8266TrueRandom.random(0, n);
        swap(&arr[i], &arr[j]);
    }
}

void copy_array(int s[], int d[], int n)
{
    for (int i = 0; i < n; i++)
        d[i] = s[i];
} // s for source & d for destination

void animateNames(const char name_arr_og[][NUM_CHARS], const int name_inds_og[],
                  const int num_names, char const postfix[] /* = "" */,
                  int textSize /* = 1 */, int delayms /* = 100 */)
{
    // append somestring
    char name_arr[NUM_NAMES][30];
    for (int i = 0; i < NUM_NAMES; i++)
    {
        sprintf(name_arr[i], "%s%s", name_arr_og[i], postfix);
    }

    // set font size
    display.setTextSize(textSize); // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0); // Start at top-left corner

    // FIRST shuffle name order
    int name_inds[num_names];
    for (int i = 0; i < num_names; i++)
    {
        name_inds[i] = name_inds_og[i];
    }
    randomize(name_inds, num_names);

    // some data to use later
    // int name_len[num_names];
    int name_xpos[num_names];
    uint16_t name_ht[num_names];
    int inc_y = 1;   // value to increment cursor with each iteration
    int delta_y = 1; // distance between text

    // Initialize 'name' x positions
    for (int i = 0; i < num_names; i++)
    {
        int in = name_inds[i];
        int16_t x1, y1;
        uint16_t wt, ht;
        display.getTextBounds(name_arr[in], 0, 0, &x1, &y1, &wt, &ht);
        name_xpos[i] = ESP8266TrueRandom.random(0, SCREEN_WIDTH - wt);
        name_ht[i] = ht;
    }

    int name_y_pos_top[num_names];
    int name_y_pos_bot[num_names];
    name_y_pos_top[0] = -name_ht[0];
    name_y_pos_bot[0] = 0;
    // Initialize 'name' y positions
    for (int i = 1; i < num_names; i++)
    {
        name_y_pos_top[i] = name_y_pos_top[i - 1] - delta_y - name_ht[i];
        name_y_pos_bot[i] = name_y_pos_top[i] + name_ht[i];
    }

    // and now DRAW
    bool drawing_something = false;
    int num_iters = 0;
    while (drawing_something || num_iters < 100)
    {
        // start drawing names, first clear display
        display.clearDisplay();
        drawing_something = false;
        num_iters++;
        for (int i = 0; i < num_names; i++)
        {
            int in = name_inds[i];
            // check if in bounds
            int ytop = name_y_pos_top[i];
            int ybot = name_y_pos_bot[i];

            if ((ytop > 0 && ytop < SCREEN_HEIGHT) || (ybot > 0 && ybot < SCREEN_HEIGHT))
            {
                drawing_something = true;
                display.setCursor(name_xpos[i], ytop);
                display.print(name_arr[in]);
            }
            // increment y positions
            name_y_pos_top[i] += inc_y;
            name_y_pos_bot[i] += inc_y;
        }
        if (drawing_something)
        {
            display.display();
            delay(delayms); // and make bit slower
        }
    }
}

void whosNextAnimate()
{
    int margin = 10;
    char text[] = "Who's next???";
    // int16_t x1, y1;
    // uint16_t wt, ht;
    // display.getTextBounds(text, 0, 0, &x1, &y1, &wt, &ht);
    int wt = SCREEN_WIDTH * 2.1;
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setTextWrap(false);

    // init cursor
    int cursor_x = SCREEN_WIDTH;
    int cursor_y = 20;

    // and draw text and graduated img
    while (cursor_x > -wt - margin - graduated_width)
    {
        display.clearDisplay();
        display.setCursor(cursor_x, cursor_y);
        display.print(text);

        if (cursor_x < SCREEN_WIDTH - wt + margin)
        {
            display.drawBitmap(cursor_x + wt + margin, (64 - graduated_height) / 2, graduated_data, graduated_width, graduated_height, 1);
        }

        display.display();
        cursor_x -= 1;
    }

    display.setTextWrap(true); // and set wrapping on again
    delay(100);
    int r = ESP8266TrueRandom.random(0, 2);
    if (r == 1)
        animateNames(all_nicknames, whos_next_ind, NUM_NEXT_NAMES, "?", 2);
    else
        animateNames(all_names, whos_next_ind, NUM_NEXT_NAMES, "?", 2);

    // draw question mark
    display_quesstion2();
    bool isInvert = false;
    int i = 0;
    do
    {
        delay(500);
        isInvert = !isInvert;
        display.invertDisplay(isInvert);
        i++;
    } while (i < 6);
    display.invertDisplay(false);

    // graduation bitmap
    scrollBitmap(1, draw_graduated);
    scrollBitmap(2, draw_graduated);

    // draw heart
    display_heart1();
    isInvert = false;
    i = 0;
    do
    {
        delay(500);
        isInvert = !isInvert;
        display.invertDisplay(isInvert);
        i++;
    } while (i < 6);
    display.invertDisplay(false);

    // and names with hearts
    animateNames(all_nicknames, all_ind, NUM_NAMES, "<3", 1);

    // draw heart
    display_heart1();
    isInvert = false;
    i = 0;
    do
    {
        delay(500);
        isInvert = !isInvert;
        display.invertDisplay(isInvert);
        i++;
    } while (i < 6);
    display.invertDisplay(false);
}

// array with function pointers (defined extern in draw_images.cpp)
extern mysize (*ImgDrawPointers[])(int, int);
extern void (*BlinkDrawPointers[])();
extern void (*StickDrawPointers[])();

// draw all images and animation categories random
void AnimateAllStick()
{
    int ind_arr[NUM_STICK_POINTERS];
    for (int i = 0; i < NUM_STICK_POINTERS; i++)
    {
        ind_arr[i] = i;
    }
    // shuffle array
    randomize(ind_arr, NUM_STICK_POINTERS);
    // and animate all
    for (int i = 0; i < NUM_STICK_POINTERS; i++)
    {
        StickDrawPointers[ind_arr[i]]();
    }
}

void AnimateAllBlink()
{
    int ind_arr[NUM_BLINK_POINTERS];
    for (int i = 0; i < NUM_BLINK_POINTERS; i++)
    {
        ind_arr[i] = i;
    }
    // shuffle array
    randomize(ind_arr, NUM_BLINK_POINTERS);
    // and animate all
    for (int i = 0; i < NUM_BLINK_POINTERS; i++)
    {
        BlinkDrawPointers[ind_arr[i]]();
    }
}

// =============================================================================
// test draw functions
// =============================================================================
/*


// declare funtions
void testdrawline()
{
    int16_t i;

    display.clearDisplay(); // Clear display buffer

    for (i = 0; i < display.width(); i += 4)
    {
        display.drawLine(0, 0, i, display.height() - 1, SSD1306_WHITE);
        display.display(); // Update screen with each newly-drawn line
        delay(1);
    }
    for (i = 0; i < display.height(); i += 4)
    {
        display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = 0; i < display.width(); i += 4)
    {
        display.drawLine(0, display.height() - 1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = display.height() - 1; i >= 0; i -= 4)
    {
        display.drawLine(0, display.height() - 1, display.width() - 1, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = display.width() - 1; i >= 0; i -= 4)
    {
        display.drawLine(display.width() - 1, display.height() - 1, i, 0, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = display.height() - 1; i >= 0; i -= 4)
    {
        display.drawLine(display.width() - 1, display.height() - 1, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    delay(250);

    display.clearDisplay();

    for (i = 0; i < display.height(); i += 4)
    {
        display.drawLine(display.width() - 1, 0, 0, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }
    for (i = 0; i < display.width(); i += 4)
    {
        display.drawLine(display.width() - 1, 0, i, display.height() - 1, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000); // Pause for 2 seconds
}

void testdrawrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2; i += 2)
    {
        display.drawRect(i, i, display.width() - 2 * i, display.height() - 2 * i, SSD1306_WHITE);
        display.display(); // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testfillrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2; i += 3)
    {
        // The INVERSE color is used so rectangles alternate white/black
        display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
        display.display(); // Update screen with each newly-drawn rectangle
        delay(1);
    }

    delay(2000);
}

void testdrawcircle(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 2)
    {
        display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillcircle(void)
{
    display.clearDisplay();

    for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 3)
    {
        // The INVERSE color is used so circles alternate white/black
        display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
        display.display(); // Update screen with each newly-drawn circle
        delay(1);
    }

    delay(2000);
}

void testdrawroundrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2 - 2; i += 2)
    {
        display.drawRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
                              display.height() / 4, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfillroundrect(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < display.height() / 2 - 2; i += 2)
    {
        // The INVERSE color is used so round-rects alternate white/black
        display.fillRoundRect(i, i, display.width() - 2 * i, display.height() - 2 * i,
                              display.height() / 4, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawtriangle(void)
{
    display.clearDisplay();

    for (int16_t i = 0; i < max(display.width(), display.height()) / 2; i += 5)
    {
        display.drawTriangle(
            display.width() / 2, display.height() / 2 - i,
            display.width() / 2 - i, display.height() / 2 + i,
            display.width() / 2 + i, display.height() / 2 + i, SSD1306_WHITE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testfilltriangle(void)
{
    display.clearDisplay();

    for (int16_t i = max(display.width(), display.height()) / 2; i > 0; i -= 5)
    {
        // The INVERSE color is used so triangles alternate white/black
        display.fillTriangle(
            display.width() / 2, display.height() / 2 - i,
            display.width() / 2 - i, display.height() / 2 + i,
            display.width() / 2 + i, display.height() / 2 + i, SSD1306_INVERSE);
        display.display();
        delay(1);
    }

    delay(2000);
}

void testdrawchar(void)
{
    display.clearDisplay();

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.cp437(true);                 // Use full 256 char 'Code Page 437' font

    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    for (int16_t i = 0; i < 256; i++)
    {
        if (i == '\n')
            display.write(' ');
        else
            display.write(i);
    }

    display.display();
    delay(2000);
}

void testdrawstyles(void)
{
    display.clearDisplay();

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(F("Hello, world!"));

    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println(3.141592);

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(F("0x"));
    display.println(0xDEADBEEF, HEX);

    display.display();
    delay(2000);
}

void testscrolltext(void)
{
    display.clearDisplay();

    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    display.println(F("Hee Joooooost! :) "));
    display.display(); // Show initial text
    delay(100);

    // Scroll in various directions, pausing in-between:
    display.startscrollright(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrollleft(0x00, 0x0F);
    delay(2000);
    display.stopscroll();
    delay(1000);
    display.startscrolldiagright(0x00, 0x07);
    delay(2000);
    display.startscrolldiagleft(0x00, 0x07);
    delay(2000);
    display.stopscroll();
    delay(1000);
}

void testdrawbitmap(void)
{
    display.clearDisplay();
    display.drawBitmap(
        (display.width() - LOGO_WIDTH) / 2,
        (display.height() - LOGO_HEIGHT) / 2,
        logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
    delay(1000);
}

#define XPOS 0 // Indexes into the 'icons' array in function below
#define YPOS 1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
    int8_t f, icons[NUMFLAKES][3];

    // Initialize 'snowflake' positions
    for (f = 0; f < NUMFLAKES; f++)
    {
        icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS] = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
        Serial.print(F("x: "));
        Serial.print(icons[f][XPOS], DEC);
        Serial.print(F(" y: "));
        Serial.print(icons[f][YPOS], DEC);
        Serial.print(F(" dy: "));
        Serial.println(icons[f][DELTAY], DEC);
    }

    for (;;)
    {                           // Loop forever...
        display.clearDisplay(); // Clear the display buffer

        // Draw each snowflake:
        for (f = 0; f < NUMFLAKES; f++)
        {
            display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
        }

        display.display(); // Show the display buffer on the screen
        delay(200);        // Pause for 1/10 second

        // Then update coordinates of each flake...
        for (f = 0; f < NUMFLAKES; f++)
        {
            icons[f][YPOS] += icons[f][DELTAY];
            // If snowflake is off the bottom of the screen...
            if (icons[f][YPOS] >= display.height())
            {
                // Reinitialize to a random position, just off the top
                icons[f][XPOS] = random(1 - LOGO_WIDTH, display.width());
                icons[f][YPOS] = -LOGO_HEIGHT;
                icons[f][DELTAY] = random(1, 6);
            }
        }
    }
}


*/