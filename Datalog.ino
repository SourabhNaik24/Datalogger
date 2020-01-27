#include "thermo.h"
#include "lcd.h"
#include "rtd.h"

// RTD variables
float rtdTemp = 0;
int rtdRes = 0;

// Thermocouple variables
float thermoTemp = 0;


void setup() {
  Serial.begin(115200);
  setLCD();
  setThermo();
  setRTD();
}

void loop() {
  rtdTemp = readRtdTemp();
  rtdRes =  readRtdRes();
  thermoTemp =  (readThermoTemp() - readCJTemp());
  dispRTD(rtdTemp,rtdRes);
  dispThermo(thermoTemp);
  delay(500);

}
