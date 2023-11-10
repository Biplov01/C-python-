// Huge thanks to Adafruit for the library and tutorial this is modified from.
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other */
#define i2c_Address 0x3c // initialize with the I2C addr 0x3C Typically eBay OLED's

// Update the display size configurations
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define XPOS 0
#define YPOS 1
#define LOGO16_GLCD_HEIGHT 64
#define LOGO16_GLCD_WIDTH 16

void setup() {
  Serial.begin(9600);

  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
  //display.setContrast (0); // dim display

  display.clearDisplay();
}

void loop() {
  // Angry Eye's
  display.fillTriangle(56, 36, 12, 36, 16, 16, SH110X_WHITE);
  display.fillTriangle(72, 36, 112, 36, 108, 16, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Center Eye
  display.fillCircle(display.width() / 2 - 25, display.height() / 2, 15, SH110X_WHITE);
  display.fillCircle(display.width() / 2 + 25, display.height() / 2, 15, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Right Eyes
  display.fillCircle(display.width() / 2 - 15, display.height() / 2, 15, SH110X_WHITE);
  display.fillCircle(display.width() / 2 + 35, display.height() / 2, 15, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Center Eyes
  display.fillCircle(display.width() / 2 - 25, display.height() / 2, 15, SH110X_WHITE);
  display.fillCircle(display.width() / 2 + 25, display.height() / 2, 15, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Blink
  display.fillRoundRect(display.width() / 2 - 40, display.height() / 2, 30, 8, 8, SH110X_WHITE);
  display.fillRoundRect(display.width() / 2 + 2, display.height() / 2, 30, 8, 8, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Center Eyes
  display.fillCircle(display.width() / 2 - 25, display.height() / 2, 15, SH110X_WHITE);
  display.fillCircle(display.width() / 2 + 25, display.height() / 2, 15, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Left Eyes
  display.fillCircle(display.width() / 2 - 35, display.height() / 2, 15, SH110X_WHITE);
  display.fillCircle(display.width() / 2 + 15, display.height() / 2, 15, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
  // Blink Left
  display.fillRoundRect(display.width() / 2 - 60, display.height() / 2, 30, 8, 8, SH110X_WHITE);
  display.fillRoundRect(display.width() / 2 - 15, display.height() / 2, 30, 8, 8, SH110X_WHITE);
  display.display();
  delay(500);
  display.clearDisplay();
}

void testdrawcircle(void) {
  for (int16_t i = 0; i < display.height(); i += 2) {
    display.drawCircle(display.width() / 2, display.height() / 2, i, SH110X_WHITE);
    display.display();
    delay(1);
  }
}

void drawRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
void fillRoundRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint16_t radius, uint16_t color);
void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void fillTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
