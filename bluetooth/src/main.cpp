//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

const uint8_t * buffer = (const uint8_t*) ("aaaaaaaaaaaaaaaaaaaa");
int count = 0;
int tamanios[] = {20, 200, 2000, 20000, 200000, 2000000};
unsigned long tiempo;

void modo_de_prueba(int modo)
{
    if (modo <= 6 && modo >= 1) {
        Serial.println("-------------");
        Serial.print("MODO ");
        Serial.print(modo);
        Serial.print(":  ");
        Serial.print(tamanios[modo - 1]);
        Serial.print("Bytes\n");

        while (count < tamanios[modo - 1])
        {
            unsigned long start = micros();
            SerialBT.write(buffer, 20);
            tiempo += micros() - start;
            count += 20;
        }
        delay(100);
        SerialBT.write('0');
    } else {
        Serial.println("Error en el modo elegido");
    }
}

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("ESP32test"); //Bluetooth device name
    Serial.println("El ESP está listo para aparearse con otro dispositivo bluetooth");
    Serial.println("Esperando confirmación del dispositivo receptor");
}

void loop()
{   
    if (SerialBT.available()) {
        int modo = SerialBT.read();
        SerialBT.flush();
        tiempo = 0;
        count = 0;
        Serial.println("BT Serial disponible");
        Serial.println("Comenzando prueba");
        
        modo_de_prueba(modo - 48);

        Serial.println("Tiempo total envío:");
        Serial.println(tiempo);
        Serial.println("-------------");
        SerialBT.flush();
    }
}