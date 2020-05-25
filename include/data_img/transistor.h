
#define transistor_width  78
#define transistor_height 64

const uint8_t PROGMEM transistor_data[] = {
  B00000000,B00000000,B00000000,B00000000,B01111111,B11111000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000011,B11111111,B11111111,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00011111,B11111111,B11111111,B11100000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B01111111,B11111111,B11111111,B11111000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000001,B11111111,B10000000,B00000111,B11111100,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000011,B11111100,B00000000,B00000000,B11111111,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000111,B11110000,B00000000,B00000000,B00111111,B10000000,B00000000,B00000011,
  B00000000,B00000000,B00001111,B11000000,B00000000,B00000000,B00001111,B11000000,B00000000,B00000011,
  B00000000,B00000000,B00011111,B10000000,B00000000,B00000000,B00000111,B11100000,B00000000,B00000011,
  B00000000,B00000000,B00111110,B00000000,B00000000,B00000000,B00000001,B11110000,B00000000,B00000011,
  B00000000,B00000000,B01111100,B00000000,B00000000,B00000000,B00000000,B11111000,B00000000,B00000011,
  B11111111,B11111111,B11111000,B00000000,B00000000,B00000000,B00000000,B01111111,B11111111,B11111111,
  B11111111,B11111111,B11110000,B00000000,B00000000,B00000000,B00000000,B00111111,B11111111,B11111111,
  B11111111,B11111111,B11110000,B00000000,B00000000,B00000000,B00000000,B00111111,B11111111,B11111111,
  B11111111,B11111111,B11110000,B00000000,B00000000,B00000000,B00000000,B00111111,B11111111,B11111111,
  B00000000,B00000011,B11110000,B00000000,B00000000,B00000000,B00000000,B01111111,B00000000,B00000011,
  B00000000,B00000111,B11111000,B00000000,B00000000,B00000000,B00000000,B11111111,B10000000,B00000011,
  B00000000,B00001111,B11111000,B00000000,B00000000,B00000000,B00000011,B11111111,B11000000,B00000011,
  B00000000,B00001111,B00111100,B00000000,B00000000,B00000000,B00000111,B11111011,B11000000,B00000011,
  B00000000,B00001111,B00111110,B00000000,B00000000,B00000000,B00011111,B11111011,B11000000,B00000011,
  B00000000,B00001111,B00011110,B00000000,B00000000,B00000000,B00111111,B11111011,B11000000,B00000011,
  B00000000,B00011110,B00011111,B00000000,B00000000,B00000000,B11111111,B11111001,B11100000,B00000011,
  B00000000,B00011110,B00001111,B10000000,B00000000,B00000000,B00111111,B11111001,B11100000,B00000011,
  B00000000,B00011110,B00001111,B10000000,B00000000,B00000000,B00011111,B11111001,B11100000,B00000011,
  B00000000,B00011100,B00000111,B10000000,B00000000,B00000000,B00001111,B11111000,B11100000,B00000011,
  B00000000,B00011100,B00000111,B11000000,B00000000,B00000000,B00001111,B11111000,B11100000,B00000011,
  B00000000,B00011100,B00000011,B11100000,B00000000,B00000000,B00011111,B11111000,B11100000,B00000011,
  B00000000,B00011100,B00000001,B11100000,B00000000,B00000000,B00011110,B01111000,B11100000,B00000011,
  B00000000,B00011100,B00000001,B11110000,B00000000,B00000000,B00111110,B00010000,B11100000,B00000011,
  B00000000,B00011100,B00000000,B11110000,B00000000,B00000000,B00111100,B00000000,B11100000,B00000011,
  B00000000,B00011100,B00000000,B01111000,B00000000,B00000000,B01111000,B00000000,B11100000,B00000011,
  B00000000,B00011100,B00000001,B11111111,B11111111,B11111111,B11111110,B00000000,B11100000,B00000011,
  B00000000,B00011100,B00000001,B11111111,B11111111,B11111111,B11111110,B00000001,B11100000,B00000011,
  B00000000,B00011110,B00000001,B11111111,B11111111,B11111111,B11111110,B00000001,B11100000,B00000011,
  B00000000,B00011110,B00000001,B11111111,B11111111,B11111111,B11111110,B00000001,B11100000,B00000011,
  B00000000,B00011110,B00000001,B11111111,B11111111,B11111111,B11111110,B00000001,B11100000,B00000011,
  B00000000,B00001111,B00000001,B11111111,B11111111,B11111111,B11111110,B00000011,B11000000,B00000011,
  B00000000,B00001111,B00000001,B11111111,B11111111,B11111111,B11111110,B00000011,B11000000,B00000011,
  B00000000,B00001111,B00000001,B11111111,B11111111,B11111111,B11111110,B00000111,B11000000,B00000011,
  B00000000,B00001111,B10000000,B00000000,B00000111,B10000000,B00000000,B00000111,B10000000,B00000011,
  B00000000,B00000111,B11000000,B00000000,B00000111,B10000000,B00000000,B00001111,B10000000,B00000011,
  B00000000,B00000011,B11000000,B00000000,B00000111,B10000000,B00000000,B00001111,B00000000,B00000011,
  B00000000,B00000011,B11100000,B00000000,B00000111,B10000000,B00000000,B00011111,B00000000,B00000011,
  B00000000,B00000001,B11110000,B00000000,B00000111,B10000000,B00000000,B00111110,B00000000,B00000011,
  B00000000,B00000001,B11110000,B00000000,B00000111,B10000000,B00000000,B00111100,B00000000,B00000011,
  B00000000,B00000000,B11111000,B00000000,B00000111,B10000000,B00000000,B01111100,B00000000,B00000011,
  B00000000,B00000000,B01111100,B00000000,B00000111,B10000000,B00000000,B11111000,B00000000,B00000011,
  B00000000,B00000000,B00111110,B00000000,B00000111,B10000000,B00000001,B11110000,B00000000,B00000011,
  B00000000,B00000000,B00011111,B10000000,B00000111,B10000000,B00000111,B11100000,B00000000,B00000011,
  B00000000,B00000000,B00001111,B11000000,B00000111,B10000000,B00001111,B11000000,B00000000,B00000011,
  B00000000,B00000000,B00000111,B11110000,B00000111,B10000000,B00111111,B10000000,B00000000,B00000011,
  B00000000,B00000000,B00000011,B11111100,B00000111,B10000000,B11111111,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B11111111,B11000111,B10001111,B11111100,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B01111111,B11111111,B11111111,B11111000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00001111,B11111111,B11111111,B11000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000001,B11111111,B11111110,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00111111,B11110000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
  B00000000,B00000000,B00000000,B00000000,B00000111,B10000000,B00000000,B00000000,B00000000,B00000011,
};