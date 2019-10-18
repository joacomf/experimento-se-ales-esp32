#include <Arduino.h>
#include <Wire.h>
#include "../../main.h"

#define RXD2 16
#define TXD2 17

long cantidad_bytes_recibidos = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUDIOS, SERIAL_8N1, RXD2, TXD2);
}

void enviarFlagDeRecepcionCon(byte recibidos) {
  Serial1.write(recibidos);
  Serial1.flush();
}

void loop() {

  byte buffer[BUFFER_SIZE] = {};
  delay(3000);
  enviarFlagDeRecepcionCon(0);

  unsigned long tiempo_inicio = millis();

  while (cantidad_bytes_recibidos < BYTES_A_ENVIAR) {
    byte recibidos_en_iteracion = Serial1.readBytes(buffer, BUFFER_SIZE);

    cantidad_bytes_recibidos += recibidos_en_iteracion;

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