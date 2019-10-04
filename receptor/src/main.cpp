#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define INTERRUPT_PIN 23
#define CANTIDAD_EXPERIMENTOS 5

long tiempos[CANTIDAD_EXPERIMENTOS];
int numeroExperimento = 0;
long tiempoInicial = 0;
long tiempoFinal = 0;
int bytesRecibidos = 0;

void iniciarContador(){
  tiempoInicial = millis();
}

void detenerContador(){
  tiempoFinal = millis() - tiempoInicial;
  tiempos[numeroExperimento] = tiempoFinal;
}

void reiniciarExperimento(){
  numeroExperimento++;
  tiempoFinal = 0;
  tiempoInicial = 0;
  bytesRecibidos = 0;
}

void setup() {
  memset(tiempos, 0, CANTIDAD_EXPERIMENTOS);
  pinMode(INTERRUPT_PIN, INPUT);
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), iniciarContador, RISING);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop(){
  if(numeroExperimento < CANTIDAD_EXPERIMENTOS){
    Serial.print("Iniciando experimento: ");
    Serial.println(numeroExperimento);
    while(digitalRead(INTERRUPT_PIN) == LOW);
    byte cantidadBytesALeer;
    iniciarContador();
    while (digitalRead(INTERRUPT_PIN) == HIGH && Serial1.available()) {
        cantidadBytesALeer = Serial1.available();
        byte buffer[cantidadBytesALeer];
        Serial1.readBytes(buffer, cantidadBytesALeer);
    }
    detenerContador();
    reiniciarExperimento();
    delay(500);
  } else {
    Serial.print("Tiempos de los experimentos: ");
    for (size_t i = 0; i < CANTIDAD_EXPERIMENTOS; i++){
      Serial.print(tiempos[i]);
      Serial.print(", ");
    }
    delay(2000);
  }
}
