#include "Arduino.h"
// #include <SDController.hpp>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define RXD2 16
#define TXD2 17

// SDController *sdController = new SDController();
int n = 0;

void setup()
{
  Serial.begin(115200);
  delay(4000);
}

void loop()
{
  // while (n < 1000) {
  //   sdController->appendFile("a");
  //   n++;
  // }
  // Serial.println(sdController->readFile(1000));
  while (true);
}