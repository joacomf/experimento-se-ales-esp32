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

  int bytes_a_enviar = BYTES_A_ENVIAR;
  byte buffer[BUFFER_SIZE];
  memset(buffer, 1, BUFFER_SIZE);

  while (bytes_a_enviar > 0){
    Serial1.write(buffer, BUFFER_SIZE);
    Serial1.flush();
    bytes_a_enviar -= BUFFER_SIZE;
    delay(1);
  }

  Serial1.end();

  digitalWrite(LED_FIN, HIGH);
  while(true);
}