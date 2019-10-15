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

  byte buffer[BUFFER_SIZE] = {};
  boolean recibio = false;
  int iteraciones = 0;
  int iteraciones_esperadas = (int) (BYTES_A_ENVIAR / BUFFER_SIZE);

  while (Serial1.available() || iteraciones < 1000) {
    Serial1.readBytes(buffer, BUFFER_SIZE);
    int recibidos = 0;
    for (size_t i = 0; i < BUFFER_SIZE; i++){
      if (buffer[i] == 1){
        cantidad_bytes_recibidos++;
        recibidos++;
        recibio = true;
      }
    }
    if (recibio){
      iteraciones++;
      recibio = false;
    }

  }

  unsigned long tiempo_final = millis() - tiempo_inicio;

  Serial.println("Bytes Recibidos");
  Serial.println(cantidad_bytes_recibidos);
  Serial.println("Tiempo");
  Serial.println(tiempo_final);

  while (true);

}