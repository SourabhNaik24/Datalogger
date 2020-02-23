#include "thermo.h"
#include "lcd.h"
#include "rtd.h"
#include "log.h"

// RTD variables
float rtdTemp = 0;
int rtdRes = 0;

// Thermocouple variables
float thermoTemp = 0;


void setup() {
  Serial.begin(9600);
  //setLCD();
  setLog();
  delay(500);
  //setThermo();
  setRTD();
  delay(500);
 
}

void loop() {
  rtdTemp = readRtdTemp();
  rtdRes =  readRtdRes();
  //testing thermo
 
  //thermoTemp =  (readThermoTemp() - readCJTemp());
  //dispRTD(rtdTemp,rtdRes);
  //dispThermo(thermoTemp);
  dataLog(rtdTemp, rtdRes, thermoTemp);
  delay(1000);

}
