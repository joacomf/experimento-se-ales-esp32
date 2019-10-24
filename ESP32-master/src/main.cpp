#include <Arduino.h>
#include <Wire.h>

#define FLAG_CONTROL 19
#define CANTIDAD_BYTES_A_ENVAR 204800
#define CANTIDAD_INTERRUPCIONES 0
#define TAMANIO_MAXIMO_BUFFER 32
#define DELAY_ENTRE_ENVIOS 100

byte buffer[TAMANIO_MAXIMO_BUFFER];

void enviarBytes(int cantidadBytes, int cantidadInterrupciones, int delayEntreEnvios) {
  while (cantidadBytes > 0) {
    //Serial.print("Cantidad de bytes restantes:");
    //Serial.println(cantidadBytes);
    int tamanioBuffer = TAMANIO_MAXIMO_BUFFER;

    if (cantidadBytes < TAMANIO_MAXIMO_BUFFER) {
      tamanioBuffer = cantidadBytes;
    }
    //Serial.print("Tamanio buffer:");
    //Serial.println(tamanioBuffer);

    Wire.beginTransmission(8); // transmit to device #8
    //Serial.println("Transmitiendo...");
    Wire.write(buffer, tamanioBuffer);
    Wire.endTransmission();    // stop transmitting
    cantidadBytes -= tamanioBuffer;

    if (delayEntreEnvios > 0) {
      delay(delayEntreEnvios);
    }

    if (cantidadInterrupciones > 0) {
      Wire.requestFrom(8, 32);
      cantidadInterrupciones--;
    }
  }
}

void setup() {
  pinMode(FLAG_CONTROL, OUTPUT);
  memset(buffer, 1, TAMANIO_MAXIMO_BUFFER);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);
  digitalWrite(FLAG_CONTROL, HIGH);
  enviarBytes(CANTIDAD_BYTES_A_ENVAR, CANTIDAD_INTERRUPCIONES, DELAY_ENTRE_ENVIOS);
  digitalWrite(FLAG_CONTROL, LOW);
}

void loop() {
  delay(1000);
}