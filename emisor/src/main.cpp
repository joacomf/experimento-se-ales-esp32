#include <Arduino.h>
#include "../../main.h"

#define RXD2 16
#define TXD2 17

#define LED 2
#define LED_FIN 15

int bytes_recibidos = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(BAUDIOS, SERIAL_8N1, RXD2, TXD2);

  pinMode(LED, OUTPUT);
  pinMode(LED_FIN, OUTPUT);

  digitalWrite(LED, LOW);

  Serial.println("Inicia");
}

void comenzarEnvio(){
  digitalWrite(LED, HIGH);
}

void esperarFlagDeRecepcion(){
  while (!Serial1.available());
  byte recibidos = Serial1.read();

  bytes_recibidos += recibidos;
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

  while (bytes_a_enviar != 0){
    esperarFlagDeRecepcion();
    enviarPorcionDeDatosEn(buffer);
    bytes_a_enviar -= BUFFER_SIZE;
  }
  esperarFlagDeRecepcion();
  terminarEnvio();
}