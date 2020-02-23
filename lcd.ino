#include <Adafruit_ILI9341.h>
#include "SPI.h"
#include <Fonts/FreeSerif24pt7b.h>  // Add a custom font
#define TFT_DC PA1
#define TFT_CS PA2
#define TFT_MOSI PA7
#define TFT_CLK PA5
#define TFT_RST PA0
#define TFT_MISO PA6

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setLCD() {
  tft.begin();
  Serial.println("Filling TFT Screen");
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 1, 239, 30, ILI9341_YELLOW);
  tft.drawRect(0, 35, 239, 285, ILI9341_RED);
  tft.drawLine(0, 102, 239, 102, ILI9341_RED);
  tft.drawLine(0, 174, 239, 174, ILI9341_RED);
  tft.drawLine(0, 250, 239, 250, ILI9341_RED);
  tft.drawLine(120, 35, 120, 320, ILI9341_RED);
  delay(100);
  Serial.println("Displaying constant parameters");
  constDisp();
  delay(100);
}

void dispRTD(float temp, float res) {
  tft.setCursor(140, 55);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(2);
  char string[10];
  // Convert float to a string:
  dtostrf(temp, 3, 2, string);
  tft.fillRect(139, 54, 84, 34, 0x0000);
  tft.println(temp);

  tft.setCursor(140, 125);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(2);
  dtostrf(res, 3, 2, string);
  tft.fillRect(139, 124, 84, 34, 0x0000);
  tft.println(res);
}

void dispThermo(float temp) {
  char string[10];
  tft.setCursor(140, 200);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(2);
  dtostrf(temp, 3, 2, string);
  tft.fillRect(139, 199, 84, 34, 0x0000);
  tft.println(temp);
}

void constDisp() {
  tft.setCursor(20, 4);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3.2);
  tft.println("DATA LOGGER");
  tft.setCursor(10, 55);
  tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println("RTD Temp: ");
  tft.setCursor(10, 125);
  tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println("RTD Res: ");
  tft.setCursor(10, 200);
  tft.setTextColor(ILI9341_CYAN); tft.setTextSize(2);
  tft.println("TC Temp: ");
}
