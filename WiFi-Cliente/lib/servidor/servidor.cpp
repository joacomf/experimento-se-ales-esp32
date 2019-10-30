#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"
#include "credenciales.h"

WiFiClient cliente;
WiFiServer servidor(PUERTO);
unsigned long tiempoInicial;
unsigned long tiempoFinal;
unsigned long bytesRecibidos = 0;

void iniciarTimer() {
  tiempoInicial = millis();
}

void detenerTimer() {
  tiempoFinal = millis() - tiempoInicial;
}

void enviarEncabezado() {
  cliente.println("HTTP/1.1 200 OK");
  cliente.println("Content-type:text/html");
  cliente.println("Connection: close");
}

void enviarRespuesta(unsigned long respuesta) {
  enviarEncabezado();
  cliente.println(respuesta);
  cliente.println();
}

void setup() {
  Serial.begin(BAUDIOS);
  WiFi.softAP(NOMBRE_RED, PASSWORD);
  Serial.print("IP de servidor: ");
  Serial.println(WiFi.softAPIP());
  servidor.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  cliente = servidor.available();

  if (cliente != NULL) {
    String mensaje = cliente.readStringUntil('\r');
    
    if (mensaje == INICIO_ENVIO) {
      enviarEncabezado();
      iniciarTimer();
      Serial.println("Inicio envio");
    } else if (mensaje == FIN_ENVIO) {
      detenerTimer();
      enviarRespuesta(bytesRecibidos);
    } else {
      bytesRecibidos++;
    }
  }
}