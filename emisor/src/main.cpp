#include <Arduino.h>
#include "../../main.h"

#define RXD2 16
#define TXD2 17

#define LED 2
#define LED_FIN 15

void setup() {
  Serial1.begin(BAUDIOS, SERIAL_8N1, RXD2, TXD2);

  pinMode(LED, OUTPUT);
  pinMode(LED_FIN, OUTPUT);
  pinMode(FLAG_DE_COMIENZO, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(FLAG_DE_COMIENZO, LOW);

  delay(3000);

}

void loop() {
  digitalWrite(LED, HIGH);
  digitalWrite(FLAG_DE_COMIENZO, HIGH);

  for (size_t i = 0; i < BYTES_A_ENVIAR && Serial1.available(); i++){
    byte datoAEnviar = 1;
    Serial1.write(datoAEnviar);
  }

  digitalWrite(LED_FIN, HIGH);
  while(true);
}