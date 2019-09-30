#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define SENIAL_CONTROL 3

int bytesAEnviar[8] = {2, 20, 200, 2048, 20480, 204800, 2097152, 20971520};
int indice = 0;

void setup() {
  pinMode(SENIAL_CONTROL, OUTPUT);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop(){
  if(indice < 8){
    digitalWrite(SENIAL_CONTROL, HIGH);
    byte buffer[bytesAEnviar[indice]];
    memset(buffer, 1, bytesAEnviar[indice]);
    Serial1.write(buffer, bytesAEnviar[indice]);
    Serial1.flush(); //En teoria, con esto no sigue el programa hasta que no envio todo
    indice++;
    digitalWrite(SENIAL_CONTROL, LOW); 
  }
  delay(2000);
}