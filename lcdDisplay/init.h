#define REFRESH_RATE 250
#define BLINK_TIME_ARROW 500
const byte RS = 9;
const byte enable = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
const byte contrastPin = 3;
unsigned long lastRefresh = 0;
unsigned long lastArrowBlink = 0;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

byte arrowUp[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B01110,
  B11111,
  B00000,
  B00000
};

byte arrowDown[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte clickArrow[] = {
  B00000,
  B11110,
  B11100,
  B11100,
  B10010,
  B00001,
  B00000,
  B00000
};