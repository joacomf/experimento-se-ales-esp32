#include "Arduino.h"
#include <SDController.h>

SDController sdController = SDController();
int n = 0;

void setup()
{
  Serial.begin(115200);
  delay(4000);
  sdController.deleteFile();
}

void loop()
{
  while (n < 100) {
    sdController.appendFile("a");
    n++;
  }
  Serial.println(sdController.readFile());
  while (true);
}