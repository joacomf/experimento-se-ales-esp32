// https://www.instructables.com/id/WiFi-Communication-Between-Two-ESP8266-Based-MCU-T/
#include <Arduino.h>
#include <WiFi.h>

byte ledPin = 2;
char ssid[] = "ESP";           
char pass[] = "12345678";

unsigned long askTimer = 0;

IPAddress server(192,168,0,80);       // the fix IP address of the server
WiFiClient client;
unsigned long tiempoInicial = 0;
unsigned long tiempoIntermedio = 0;
unsigned long tiempoFinal = 0;

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

}

String datos(int cantidad){
  String salida = "";
  for(int i=0; i < cantidad; i++){
    salida += "1";
  }
  return salida + "\r";
}

void loop () {
  int datosAEnviar = 2000000;
  String data = datos(5000);
  String answer;
  while(datosAEnviar > 0){
    client.connect(server, 80);   // Connection to the server

    tiempoInicial = millis();
    client.println(data);
    answer = client.readStringUntil('\r');
    tiempoIntermedio = millis() - tiempoInicial;
    
    //Serial.println("from server: " + answer);
    tiempoFinal += tiempoIntermedio;
    client.flush();
    datosAEnviar -= 5000;
  }
  Serial.print("Bytes validos: ");
  Serial.println(answer);
  Serial.print("Tiempo: ");
  Serial.println(tiempoFinal);
  while(true);
  delay(2000);                  // client will trigger the communication after two seconds
}