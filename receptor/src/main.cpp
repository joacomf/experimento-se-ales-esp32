#include <Arduino.h>
#include <Wire.h>
#include "../../main.h"

#define RXD2 16
#define TXD2 17

long cantidad_bytes_recibidos = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUDIOS, SERIAL_8N1, RXD2, TXD2);
  pinMode(FLAG_DE_COMIENZO, INPUT);
}

void loop() {
  while (digitalRead(FLAG_DE_COMIENZO) == LOW) { Serial.println("esperando"); }

  unsigned long tiempo_inicio = millis();

  byte buffer[2000] = {};
  while (Serial1.available() || cantidad_bytes_recibidos <= 180000) {
    Serial1.readBytes(buffer, 2000);

    for (size_t i = 0; i < 2000; i++){
      if (buffer[i] == 1){
        cantidad_bytes_recibidos++;
      }
    }
  }

  unsigned long tiempo_final = millis() - tiempo_inicio;
  
  Serial.println("Bytes Recibidos");
  Serial.println(cantidad_bytes_recibidos);
  Serial.println("Tiempo");
  Serial.println(tiempo_final);

  while (true);

}