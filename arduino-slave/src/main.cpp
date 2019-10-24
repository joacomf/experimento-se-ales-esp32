#include <Arduino.h>
#include <Wire.h>

#define FLAG_CONTROL 3
#define LED 13
#define ENABLE_CONVERSOR 10
#define DIRECCION_SLAVE 8
#define BAUDIOS 9600
#define EN_MICROS 0

unsigned long tiempoInicial = 0;
unsigned long tiempoFinal = 0;
int bytesRecibidos = 0;
uint8_t estadoLed = HIGH;

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void limpiarExperimento(){
  tiempoInicial = 0;
  tiempoFinal = 0;
  bytesRecibidos = 0;
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    byte c = Wire.read();
    bytesRecibidos++;
  }
}

void requestEvent() {
  estadoLed = estadoLed == HIGH ? LOW : HIGH;
  digitalWrite(LED, estadoLed);
}

unsigned long timestamp() {
  return EN_MICROS ? micros() : millis();
}

void iniciarTimer() {
  tiempoInicial = timestamp();
}

void detenerTimer(){
  tiempoFinal = timestamp() - tiempoInicial;
}

void realizarExperimento(){

  while (bytesRecibidos == 0) {
    while (digitalRead(FLAG_CONTROL) == LOW);
    Serial.println("HIGH flag control");
    iniciarTimer();
    while(digitalRead(FLAG_CONTROL) == HIGH);
  }
  
  detenerTimer();
  Serial.print("Bytes recibidos: ");
  Serial.println(bytesRecibidos);

  Serial.print("Tiempo: ");
  Serial.println(tiempoFinal);
  
  limpiarExperimento();
}

void setup() {
  pinMode(ENABLE_CONVERSOR, OUTPUT);
  pinMode(FLAG_CONTROL, INPUT);
  digitalWrite(ENABLE_CONVERSOR, HIGH);

  Wire.begin(DIRECCION_SLAVE);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(BAUDIOS);
  Serial.println("Hola...");
  realizarExperimento();
}

void loop() {
  delay(1000);
}
