#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define SENIAL_CONTROL 23
#define CANTIDAD_DE_EXPERIMENTOS 3

//int bytesAEnviar[8] = {2, 20, 200, 2048, 20480, 204800, 2097152, 20971520};
int bytesAEnviar[2] = {2, 20};
int indice = 0;

void setup() {
  pinMode(SENIAL_CONTROL, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop(){
  if(indice < CANTIDAD_DE_EXPERIMENTOS){
    Serial.print("Experimiento ");
    Serial.println(indice);
    digitalWrite(SENIAL_CONTROL, HIGH);
    byte buffer[bytesAEnviar[indice]];
    memset(buffer, 1, bytesAEnviar[indice]);
    Serial.println(Serial1.availableForWrite());
    Serial1.write(buffer, bytesAEnviar[indice]);
    Serial1.flush(); //En teoria, con esto no sigue el programa hasta que no envio todo
    indice++;
  }
  digitalWrite(SENIAL_CONTROL, LOW);
  delay(100);
}