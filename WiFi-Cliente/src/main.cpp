#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "credenciales.h"

#define BAUDIOS 115200
#define ESPERA_CONEXION 1000
#define PUERTO 80
#define IP_SERVIDOR "192.168.4.1"
#define INICIO_ENVIO "inicio envio"
#define FIN_ENVIO "fin envio"

WiFiClient client;

bool conectarARed(const char* ssid, const char* pass) {
  int cantidadRedes = WiFi.scanNetworks();
 
  Serial.print("Cantidad de redes encontradas: ");
  Serial.println(cantidadRedes);
 
  for (int i = 0; i < cantidadRedes; i++) {
    String ssidActual = WiFi.SSID(i);

    Serial.print("Nombre de red: ");
    Serial.println(ssidActual);
 
    Serial.print("Senial: ");
    Serial.println(WiFi.RSSI(i));

    if (ssidActual == ssid) {
      WiFi.begin(ssid, pass);
      return true;
    }
  }

  return false;
}

void setup() {
  Serial.begin(BAUDIOS);
  
  if (!conectarARed(NOMBRE_RED, PASSWORD)) {
    Serial.println("No se encontro la red");
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(ESPERA_CONEXION);
    Serial.println("Conectando a la red...");
  }

  Serial.println("Conectado");
  if (client.connect(IP_SERVIDOR, PUERTO)) {
    Serial.println("Conectado a servidor");
    client.println(INICIO_ENVIO);
    client.println();
  }
}

void loop() {}