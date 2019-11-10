#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>

int tiempoInicial = 0;
int tiempoFinal = 0;

byte ledPin = 2;
long bytesValidos = 0;
char ssid[] = "ESP";               // SSID of your home WiFi
char pass[] = "12345678";
LiquidCrystal lcd(22, 23, 5, 18, 19, 21);               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(192, 168, 0, 80);            // IP address of the server
IPAddress gateway(192,168,0,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

int cantidadBytesValidos(String datos){
  int bytesValidos = 0;
  for(int i=0; i<datos.length(); i++){
    if(datos.charAt(0) == '1') {
      bytesValidos++;
    }
  }
  return bytesValidos;
}

void setup() {
  //Serial.begin(115200);
                     // only for debug
  //WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  //WiFi.begin(ssid, pass);                 // connects to the WiFi router
  lcd.begin(16,2);
  WiFi.softAP(ssid, pass);
  WiFi.softAPConfig(ip, gateway, subnet);
  server.begin();                         // starts the server

}

void loop () {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {

      Serial.println(".");
      tiempoInicial = millis();
      String request = client.readStringUntil('\r');
      
      client.println("OK\r");
      bytesValidos += cantidadBytesValidos(request);
    
      tiempoFinal = millis() - tiempoInicial;
      //Serial.print("From client: ");
      //Serial.println(request);
      //Serial.print("Tiempo ");
      //Serial.println(tiempoFinal);
      //Serial.print("Bytes validos: ");
      //Serial.println(bytesValidos);
      lcd.home();
      lcd.print("Bytes correctos: ");
      lcd.setCursor(0, 1);
      lcd.print(bytesValidos);
      client.flush();

    }
    client.stop();
    //bytesValidos = 0;                // tarminates the connection with the client
  }
}