#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "credenciales.h"

#define BAUDIOS 115200
#define ESPERA_CONEXION 1000
#define PUERTO 80
#define IP_SERVIDOR "192.168.1.2"
#define INICIO "/inicio"
#define FIN "/fin"
#define OK "ok"

HTTPClient client;

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

String url(String metodo) {
  String resultado = "http://";
  resultado += IP_SERVIDOR;
  resultado += metodo;
  return resultado;
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
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(url(INICIO));
    http.addHeader("Content-Type", "text/plain");

    int httpResponseCode = http.POST("");

    if (httpResponseCode > 0) {
      String response = http.getString();
      
      if (response == OK) {
        Serial.println("Recibido correctamente del servidor");
      } else {
        Serial.print("No se recibio lo esperado. En cambio, se recibio: ");
        Serial.println(response);
      }

    } else {
      Serial.print("Error en el envio del POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  } else {
    Serial.println("Error en la conexion WiFi");   
  }

  delay(1000);
}