// initializes the LCD screen used for the demo and defines
// c-level bindings to be used to print and get info
// from the screen

// First include everything to initialize the screen
// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin

//Touch For New ILI9341 TP
#define TS_MINX 70
#define TS_MAXX 920

#define TS_MINY 120
#define TS_MAXY 900

// Button variables
#define BUTTON_W 80
#define BUTTON_H 25
#define BUTTON_TEXTSIZE 2

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Elegoo_GFX_Button incSolarButton;   // Button to increase solar setup speed.
Elegoo_GFX_Button decSolarButton;   // Button to decrease solar setup speed.

// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;
void init_LCD() {
  Serial.println(F("TFT LCD test"));

  // detect if we are using the shield or board and print out the appropriate response to alert user
  #ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
  #else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
  #endif

  // print out specs for the actual touchscreen -- in pixels
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  // this command actually resets the entire arduino
  tft.reset();

  // grab and print the version of the driver for the shield screen from the chip
   uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;

  }

  // initializes the arduino LED screen
  tft.begin(identifier);

  // Initiate the two buttons.
  incSolarButton.initButton(&tft, 200, 270, BUTTON_W, BUTTON_H, BLACK, GREEN, BLACK, "INC", BUTTON_TEXTSIZE);
  decSolarButton.initButton(&tft, 200, 300, BUTTON_W, BUTTON_H, BLACK, RED, BLACK, "DEC", BUTTON_TEXTSIZE);
}

// create tft bindings for C functions
extern "C" {
  #include "LCD.h"
  int tft_get_height() {
    return tft.height();
  }

  int tft_get_width() {
    return tft.width();
  }

  // Displays str for  aprox. num_secs seconds to console. Max char* length of 20 characters.
  void tft_display_top(const char* str, int cursorX, int cursorY) {
    tft.setCursor(cursorX, cursorY);
    tft.print(str);
  }

  void tft_display_bottom(const char* str, int cursorX, int cursorY) {
    tft.setCursor(cursorX, cursorY + tft_get_height()/2);
    tft.print(str);
  }

  void tft_clear_top(int color) {
    tft_fill_rect(0, 0, tft_get_width(), tft_get_height()/2, color);
  }

  void tft_clear_bottom(int color) {
    tft_fill_rect(0, tft_get_height()/2, tft_get_width(), tft_get_height()/2, color);
  }

  void tft_fill_rect(int upper_left_x, int upper_left_y, int lower_right_x, int lower_right_y, int color) {
    tft.fillRect(upper_left_x, upper_left_y, lower_right_x, lower_right_y, color);
  }

  void tft_set_fontsize(int size) {
    tft.setTextSize(size);
  }

  void tft_set_color(int color) {
    tft.setTextColor(color);
  }

  void draw_buttons() {
    incSolarButton.drawButton();
    decSolarButton.drawButton();
  }

  int inc_button_pressed() {
    // credit below to example 6 in tft folder of website
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    // Check if the screen has been touched.
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      int oldX = p.x;
      p.x = map(p.y, TS_MINX, TS_MAXX, tft.width(), 0);
      p.y = (tft.height()- map(oldX, TS_MINY, TS_MAXY, tft.height(), 0)) - 20;
    }

    if (incSolarButton.contains(p.x, p.y)) {
      incSolarButton.press(true);
    } else {
      incSolarButton.press(false);
    }

    if (incSolarButton.justPressed()) {
      incSolarButton.drawButton(true);
      incSolarButton.press(false);
      return 1;
    }

    if (incSolarButton.justReleased()) {
      incSolarButton.drawButton();
    }

    return 0;
  }

  int dec_button_pressed() {
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    // Check if the screen has been touched.
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      int oldX = p.x;
      p.x = map(p.y, TS_MINX, TS_MAXX, tft.width(), 0);
      p.y = (tft.height() - map(oldX, TS_MINY, TS_MAXY, tft.height(), 0)) - 20;
    }

    if (decSolarButton.contains(p.x, p.y)) {
      decSolarButton.press(true);
    } else {
      decSolarButton.press(false);
    }

    if (decSolarButton.justPressed()) {
      decSolarButton.drawButton(true);
      decSolarButton.press(false);
      return 1;
    }

    if (decSolarButton.justReleased()) {
      decSolarButton.drawButton();
    }
    return 0;
  }
}
