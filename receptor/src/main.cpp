#include <Arduino.h>

#define RXD2 16
#define TXD2 17
#define INTERRUPT_PIN 23
#define CANTIDAD_EXPERIMENTOS 3

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
    while(digitalRead(INTERRUPT_PIN) == LOW);
    iniciarContador();
    byte buffer[64];
    while (digitalRead(INTERRUPT_PIN) == HIGH && Serial1.available()) {
      size_t lectura = Serial1.readBytes(buffer, 64);
      for (size_t i = 0; i < lectura; i++){
          Serial.print(buffer[i]);
      }
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

// void loopa() {
//   //if(digitalRead(INTERRUPT_PIN) == HIGH && numeroExperimento < CANTIDAD_EXPERIMENTOS){
//     while(digitalRead(INTERRUPT_PIN) == LOW && !Serial1.available());
//     byte buffer[64];
//     iniciarContador();
//     while (Serial1.available()) {
//       Serial.print("aca");
//       Serial.print(Serial1.read());
//       bytesRecibidos = Serial1.readBytes(buffer, 64);
//       for (size_t i = 0; i < bytesRecibidos; i++)
//       {
//         Serial.print(buffer[i]);
//       }
//     }
//     detenerContador();
//     Serial.print("Bytes recibidos: ");
//     Serial.println(bytesRecibidos);
//     Serial.print("Tiempo experimento [ms]: ");
//     Serial.println(tiempos[numeroExperimento]);
//     Serial.println(numeroExperimento);
//     reiniciarExperimento();
//   //}
//   delay(4000);
// }