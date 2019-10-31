#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "credenciales.h"

#define BAUDIOS 115200
#define ESPERA_CONEXION 1000
#define PUERTO 80
#define IP_SERVIDOR "192.168.1.2"
#define INICIO "/inicio"
#define DATOS "/datos"
#define FIN "/fin"
#define OK "ok"
#define CANTIDAD_BYTES 20

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

String datos() {
  String resultado = "datos=";

  for (int i = 0; i < CANTIDAD_BYTES; i++) {
    resultado += "1";
  }

  return resultado;
}

bool enviarInicio() {
  HTTPClient http;
  http.begin(url(INICIO));
  http.addHeader("Content-Type", "text/plain");

  int codigoRespuestaHttp = http.POST("");

  if (codigoRespuestaHttp > 0) {
    String respuesta = http.getString();
    
    if (respuesta == OK) {
      Serial.println("Recibido correctamente del servidor");
    } else {
      Serial.print("No se recibio lo esperado. En cambio, se recibio: ");
      Serial.println(respuesta);
      return false;
    }

  } else {
    Serial.print("Error en el envio del POST: ");
    Serial.println(codigoRespuestaHttp);
    return false;
  }

  http.end();
  return true;
}

void enviarDatos() {
  HTTPClient http;
  http.begin(url(DATOS));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(datos());
  http.end();
}

bool enviarFin() {
  HTTPClient http;
  http.begin(url(FIN));
  http.addHeader("Content-Type", "text/plain");

  int codigoRespuestaHttp = http.POST("");

  if (codigoRespuestaHttp > 0) {
    String respuesta = http.getString();
    int indiceSeparador = respuesta.indexOf(",");
    String cantidadBytes = respuesta.substring(0, indiceSeparador);
    String tiempo = respuesta.substring(indiceSeparador + 1);
    Serial.print("Cantidad de bytes recibidos por el servidor: ");
    Serial.println(cantidadBytes);
    Serial.print("Tiempo transcurrido: ");
    Serial.println(tiempo);
  } else {
    Serial.print("Error en el envio del POST: ");
    Serial.println(codigoRespuestaHttp);
    return false;
  }

  http.end();
  return true;
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

  if (WiFi.status() == WL_CONNECTED) {
    if (!enviarInicio()) return;
    enviarDatos();
    enviarFin();
  } else {
    Serial.println("Error en la conexion WiFi");   
  }
}

void loop() {}
