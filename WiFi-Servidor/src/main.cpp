#include <WiFi.h>
#include <WebServer.h>
#include "credenciales.h"

#define BAUDIOS 115200
#define ESPERA_CONEXION 1000
#define PUERTO 80
#define INICIO "/inicio"
#define DATOS "/datos"
#define FIN "/fin"
#define OK "ok"
#define ARGUMENTO_DATOS "datos"

IPAddress local_ip(192, 168, 1, 2);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(PUERTO);
unsigned long bytesRecibidos = 0;

void manejarInicio() {
  Serial.println("Recibido INICIO");
  server.send(200, "text/plain", OK);
}

void manejarDatos() {

  if (server.hasArg(ARGUMENTO_DATOS)) {
    bytesRecibidos += server.arg(ARGUMENTO_DATOS).length();
  } else {
    Serial.println("Argumento datos no encontrado");
  }
}

void manejarFin() {
  Serial.println("Recibido FIN");
  server.send(200, "text/plain", String(bytesRecibidos));
}

void manejarNotFound(){
  server.send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(BAUDIOS);

  WiFi.softAP(NOMBRE_RED, PASSWORD);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on(INICIO, manejarInicio);
  server.on(DATOS, manejarDatos);
  server.on(FIN, manejarFin);
  server.onNotFound(manejarNotFound);
  
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
