#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define SENIAL_CONTROL 23

//int bytesAEnviar[8] = {2, 20, 200, 2048, 20480, 204800, 2097152, 20971520};
int bytesAEnviar[] = {2, 20, 200, 2048, 20480};
int indice = 0;

byte cantidadDeExperimentos = sizeof(bytesAEnviar)/sizeof(int);

void setup() {
  pinMode(SENIAL_CONTROL, OUTPUT);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("\n*******************************\nIniciando Experimento\n*******************************");
}

void loop(){
  if(indice < cantidadDeExperimentos){
    int totalBytes = bytesAEnviar[indice];
    Serial.print("Experimiento: ");
    Serial.println(indice);
    Serial.print("Enviando bytes: ");
    Serial.println(totalBytes);
    digitalWrite(SENIAL_CONTROL, HIGH);
    int bytesAvailableForWrite;
    int bytesAEnviarIteracion;
    while(totalBytes != 0){
      bytesAvailableForWrite = Serial1.availableForWrite();
      if(bytesAvailableForWrite<totalBytes){
        bytesAEnviarIteracion = bytesAvailableForWrite;
      }else{
        bytesAEnviarIteracion = totalBytes;
      }
      byte buffer[bytesAEnviarIteracion];
      memset(buffer, 1, bytesAEnviarIteracion);
      totalBytes -=Serial1.write(buffer, bytesAEnviarIteracion);
    }
    Serial1.flush(); //En teoria, con esto no sigue el programa hasta que no envio todo
    indice++;
  }else{
    Serial.println("\n*******************************\nFin Experimento\n*******************************");
    while(true);
  }
  digitalWrite(SENIAL_CONTROL, LOW);
  delay(100);
}
