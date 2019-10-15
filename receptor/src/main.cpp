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

void enviarFlagDeRecepcionCon(int recibidos) {
  Serial.println("Esperando a enviar");
  Serial1.availableForWrite();
  Serial.println("Enviando");

  int capacidad = sizeof(int);
  byte buffer[capacidad] = {};
  memcpy(buffer, &recibidos, capacidad);
 
  Serial1.write(buffer, capacidad);
  Serial.println("Listo envio");
  Serial1.flush();
}

void loop() {
  while (digitalRead(FLAG_DE_COMIENZO) == LOW) { Serial.println("esperando"); }

  unsigned long tiempo_inicio = millis();
  int recibidos_en_iteracion = 0;

  byte buffer[BUFFER_SIZE] = {};

  while (cantidad_bytes_recibidos <= BYTES_A_ENVIAR - 50) {
    recibidos_en_iteracion = 0;
    Serial1.readBytes(buffer, BUFFER_SIZE);

    for (size_t i = 0; i < BUFFER_SIZE; i++){
      if (buffer[i] == 1){
        cantidad_bytes_recibidos++;
        recibidos_en_iteracion++;
      }
    }

    if(recibidos_en_iteracion > 0){
      enviarFlagDeRecepcionCon(recibidos_en_iteracion);
    }
  }

  unsigned long tiempo_final = millis() - tiempo_inicio;
  
  Serial.println("Bytes Recibidos");
  Serial.println(cantidad_bytes_recibidos);
  Serial.println("Tiempo");
  Serial.println(tiempo_final);

  while (true);

}