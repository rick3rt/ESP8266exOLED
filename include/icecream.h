
#define icecream_width  74
#define icecream_height 64

const uint8_t PROGMEM icecream_data[] = {
  B00001111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B00011111,B11100000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B00111111,B11110000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B01110000,B01111000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11000000,B00111000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11110000,B00011100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11111000,B00011110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11111100,B00011110,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11001100,B00001110,B00011111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B11001100,B00001111,B11111111,B10000000,B01110000,B00000000,B00000000,B00000000,B00000000,B00111111,
  B01001110,B00001111,B11111111,B11100111,B11111110,B00000000,B00000000,B00000000,B00000000,B00111111,
  B00001110,B00000111,B11100011,B11111111,B11111111,B00000000,B00000000,B00000000,B00000000,B00111111,
  B00001110,B00000111,B11100000,B11111111,B11111111,B11000000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000011,B11000000,B11111110,B01111111,B11000000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000001,B11000000,B01111100,B00001111,B11000000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000001,B11000000,B01111100,B00000111,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000001,B11100000,B01111100,B00000011,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B11100000,B01111100,B00000011,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B11100000,B01111100,B00000011,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B01110000,B01111100,B00000001,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B01110000,B01111100,B00001001,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B01110000,B01111000,B00001111,B11100000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B01110000,B01111000,B00001111,B11110000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B01110000,B01110000,B00000111,B11111000,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B11100000,B01110000,B00000111,B11111100,B00000000,B00000000,B00000000,B00111111,
  B00001100,B00000000,B11100000,B01110000,B00000111,B11111110,B00000000,B00000000,B00000000,B00111111,
  B00001110,B00000001,B11100000,B01110000,B00000111,B01111111,B00000000,B00000000,B00000000,B00111111,
  B00000110,B00000001,B11000000,B01110000,B00000111,B00111111,B10000000,B00000000,B00000000,B00111111,
  B00000111,B00000001,B11000000,B00110000,B00000111,B00011111,B10000000,B00000000,B00000000,B00111111,
  B00000011,B10000001,B11000000,B00011000,B00000111,B00001111,B11100000,B00000000,B00000000,B00111111,
  B00000001,B11111111,B10000000,B00011000,B00001111,B00001111,B11100000,B00000000,B00000000,B00111111,
  B00000000,B11111111,B10000000,B00001110,B00001111,B11110001,B11110000,B00000000,B00000000,B00111111,
  B00000000,B00111111,B10000000,B00000111,B00001110,B00000000,B11111000,B00000000,B00000000,B00111111,
  B00000000,B00000001,B10000000,B00000000,B00001100,B00010000,B01111100,B00000000,B00000000,B00111111,
  B00000000,B00000001,B10000000,B00000000,B00011100,B00010000,B00111110,B00000000,B00000000,B00111111,
  B00000000,B00000001,B10000000,B00000000,B00011100,B00011111,B00111110,B00000000,B00000000,B00111111,
  B00000000,B00000001,B11000000,B00000000,B00111011,B11111100,B00001111,B00000000,B00000000,B00111111,
  B00000000,B00000001,B11000000,B00000000,B01111111,B11110000,B01000111,B10000000,B00000000,B00111111,
  B00000000,B00000001,B11000000,B00000000,B01111000,B01110000,B01000011,B11000000,B00000000,B00111111,
  B00000000,B00000001,B11100000,B00000001,B11001000,B10110000,B01000001,B11100000,B00000000,B00111111,
  B00000000,B00000001,B11100000,B00000011,B10010000,B10110000,B01000001,B11100000,B00000000,B00111111,
  B00000000,B00000001,B11110001,B11111111,B00010001,B00110000,B01000001,B11110000,B00000000,B00111111,
  B00000000,B00000000,B11110001,B11111100,B00010011,B00110000,B11000111,B00111000,B00000000,B00111111,
  B00000000,B00000000,B11111100,B11111100,B00111100,B01100000,B11111001,B00011100,B00000000,B00111111,
  B00000000,B00000000,B01111111,B11111111,B11111100,B01100011,B11100001,B00011110,B00000000,B00111111,
  B00000000,B00000000,B00111111,B10011111,B11111100,B11111111,B10000001,B00011110,B00000000,B00111111,
  B00000000,B00000000,B00011110,B00001111,B11111111,B11100001,B10000001,B11110111,B00000000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00111111,B11000001,B10011111,B10000111,B10000000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00001111,B11110011,B11111111,B00000111,B11000000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000011,B11111011,B11110011,B00001101,B11000000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B00000110,B00001100,B11100000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,B11000110,B00011111,B01110000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11110111,B11111100,B00110000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B11111111,B10001100,B00111000,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111111,B10001100,B00011100,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11111000,B00111100,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11000110,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00111110,B00000111,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B11100011,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111011,B00111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00011111,B10111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111,B10111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,
  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B01111111,
};
