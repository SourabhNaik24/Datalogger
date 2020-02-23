#include <SPI.h>
#include <SD.h>

#define SD_CS PB0

void setLog(){
  if (!SD.begin(SD_CS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}


void dataLog(float rtdTemp, int rtdRes, float thermoTemp){
  String dataString = "";
  dataString += String(rtdTemp);
  dataString += "     ";
  dataString += String(rtdRes);
  dataString += "     ";
  dataString += String(thermoTemp);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
