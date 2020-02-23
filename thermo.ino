#include <Adafruit_MAX31856.h>
// For the Adafruit shield, these are the default.
#define TC_CS PA4
#define TFT_MOSI PA7
#define TFT_CLK PA5
#define TFT_MISO PA6
// Use software SPI: CS, DI, DO, CLK

//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(TC_CS, TFT_MOSI, TFT_MISO, TFT_CLK);
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(TC_CS);

void setThermo() {
  maxthermo.begin();
  

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);
  pinMode(TC_CS, OUTPUT);
  digitalWrite(TC_CS,HIGH);
}
void getThermoType() {
  Serial.print("Thermocouple type: ");
  switch (maxthermo.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }
}

float readCJTemp() {
  digitalWrite(TC_CS,LOW);
  float CJTemp = 0;
  Serial.print("Cold Junction Temp: ");
  Serial.println(maxthermo.readCJTemperature());
  CJTemp = maxthermo.readCJTemperature();
  digitalWrite(TC_CS,HIGH);
  return CJTemp;
}

float readThermoTemp() {
  float ThermoTemp = 0;
  Serial.print("Thermocouple Temp: ");
  Serial.println(maxthermo.readThermocoupleTemperature());
  ThermoTemp = maxthermo.readThermocoupleTemperature();
  return ThermoTemp;
}

void getThermoFault() {
  uint8_t fault = maxthermo.readFault();
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range Fault");
    if (fault & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range Fault");
    if (fault & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High Fault");
    if (fault & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low Fault");
    if (fault & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High Fault");
    if (fault & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low Fault");
    if (fault & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage Fault");
    if (fault & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open Fault");
  }
}
