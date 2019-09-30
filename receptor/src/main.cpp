#include <Arduino.h>
#include <Wire.h>


void setup() {
  Wire.begin(1);                // join i2c bus with address #8
  Serial.begin(9600);           // start serial for output
}

void loop() {
  while(Wire.available()){
    Serial.print(Wire.read());
    delay(1000);
  }
}