#include <Arduino.h>
#include <Wire.h>

 
#include <Arduino.h>
#include <Arduino.h>

#define RXD2 16
#define TXD2 17

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  while (Serial1.available()) {
    Serial.print(Serial1.read());
  }
}