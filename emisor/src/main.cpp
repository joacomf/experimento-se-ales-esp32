#include <Arduino.h>

#define RXD2 16
#define TXD2 17

void setup() {
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2); 
}

void loop() {
  while (Serial1.available()) {
    Serial1.write(2);
    delay(1000);
  }
}