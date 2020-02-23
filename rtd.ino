#include <Adafruit_MAX31865.h>
// For the Adafruit shield, these are the default.

#define RTD_CS PA3
#define TFT_MOSI PB15
#define TFT_CLK PB13
#define TFT_MISO PB14

Adafruit_MAX31865 thermo = Adafruit_MAX31865(RTD_CS, TFT_MOSI, TFT_MISO, TFT_CLK);
//Adafruit_MAX31865 thermo = Adafruit_MAX31865(RTD_CS);
// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0


void setRTD() {
   pinMode(RTD_CS, OUTPUT);
  digitalWrite(RTD_CS,HIGH);
  thermo.begin(MAX31865_4WIRE);  // set to 2WIRE or 4WIRE as necessary
  Serial.println("RTD intialised");

}

float readRtdTemp()
{
  digitalWrite(RTD_CS,LOW);
  uint16_t rtd = thermo.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  Serial.print("Temperature = "); Serial.println(thermo.temperature(RNOMINAL, RREF));
  rtdRes = RREF * ratio, 8;
  float rtdTemp = thermo.temperature(RNOMINAL, RREF);
  digitalWrite(RTD_CS,HIGH);
  return rtdTemp;
}

int readRtdRes() {
 // digitalWrite(RTD_CS,LOW);
  uint16_t rtd = thermo.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  int rtdRes = (RREF * ratio, 8);
  //digitalWrite(RTD_CS,HIGH);
  return rtdRes;
}

void getRtdFault() {
  // Check and print any faults
  uint8_t fault = thermo.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    thermo.clearFault();
  }
  Serial.println();
}
