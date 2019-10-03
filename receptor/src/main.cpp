#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define INTERRUPT_PIN 23
#define CANTIDAD_EXPERIMENTOS 3

long tiempos[CANTIDAD_EXPERIMENTOS];
int numeroExperimento = 0;
volatile long tiempoInicial = 0;
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
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), iniciarContador, RISING);
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  if(digitalRead(INTERRUPT_PIN) == HIGH && numeroExperimento < CANTIDAD_EXPERIMENTOS){
    while (Serial1.available()) {
      Serial1.read();
      bytesRecibidos++;
    }
    detenerContador();
    Serial.print("Bytes recibidos: ");
    Serial.println(bytesRecibidos);
    Serial.print("Tiempo experimento [ms]: ");
    Serial.println(tiempos[numeroExperimento]);
    Serial.println(numeroExperimento);
    reiniciarExperimento();
  }
  delay(4000);
}