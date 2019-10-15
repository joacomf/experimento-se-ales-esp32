#include <Arduino.h>
#include "../../main.h"

#define RXD2 16
#define TXD2 17

#define LED 2
#define LED_FIN 15

uint32_t bytes_recibidos = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUDIOS, SERIAL_8N1, RXD2, TXD2);

  pinMode(LED, OUTPUT);
  pinMode(LED_FIN, OUTPUT);
  pinMode(FLAG_DE_COMIENZO, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(FLAG_DE_COMIENZO, LOW);

  delay(1500);
  Serial.println("Inicia");
}

void comenzarEnvio(){
  digitalWrite(LED, HIGH);
  digitalWrite(FLAG_DE_COMIENZO, HIGH);
}

void esperarFlagDeRecepcion(){
  Serial.println("Esperando recepción");
  byte bytes[4] = {0, 0, 0, 0};

  while (!Serial1.available());

  bytes[0] = Serial1.read();
  bytes[1] = Serial1.read();
  bytes[2] = Serial1.read();
  bytes[3] = Serial1.read();

  bytes_recibidos += bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
  Serial.println(bytes_recibidos);
}

void enviarPorcionDeDatosEn(byte buffer[]){
  Serial1.availableForWrite();
  Serial1.write(buffer, BUFFER_SIZE);
  Serial1.flush();
}

void terminarEnvio(){
  digitalWrite(LED_FIN, HIGH);
  Serial.println("RECIBIDOS");
  Serial.println(bytes_recibidos);
  while(true);
}

void loop() {
  comenzarEnvio();

  int bytes_a_enviar = BYTES_A_ENVIAR;
  byte datoAEnviar = 1;
  byte buffer[BUFFER_SIZE];
  memset(buffer, datoAEnviar, BUFFER_SIZE);

  delay(500);
  while (bytes_a_enviar != 0){
    enviarPorcionDeDatosEn(buffer);
    esperarFlagDeRecepcion();
    bytes_a_enviar -= BUFFER_SIZE;
  }

  terminarEnvio();
}