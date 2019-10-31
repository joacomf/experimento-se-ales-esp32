#include "Arduino.h"
#include <SDManager.h>
#include <NumberToString.h>
#include "FileIterator.h"
#define TAMANO_PAQUETES 20
#define SD_CARD_PIN 5

SDManager *sdManager;

int experimentos_tamanos[] = {20, 200, 2000, 20000};

long checkear_caracteres_validos(std::string filepath, long n)
{
  long resultado = 0;
  FileIterator fileIterator = FileIterator(filepath.c_str(), sdManager);
  for(std::string line; fileIterator.hasNext(); fileIterator.nextLine()){
    for (int i = 0; i < n; i++)
    {
      if (line.c_str()[i] == '1')
      {
        resultado++;
      }
    }
  }

  return resultado;
}

void experimento(long bytes_a_escribir)
{
  std::string filename = std::string(numberToString<long>(bytes_a_escribir));
  std::string filepath = std::string("/") + filename + std::string(".txt");
  sdManager->deleteFile(filepath.c_str());
  int contador_datos_enviados = 0;
  unsigned long tiempo_inicio = millis();
  int tamano_paquetes = TAMANO_PAQUETES;
  while (contador_datos_enviados < bytes_a_escribir)
  {
    if (bytes_a_escribir - contador_datos_enviados < tamano_paquetes)
    {
      tamano_paquetes = bytes_a_escribir - contador_datos_enviados;
    }
    std::string data = "";
    for(int i = 0; i < tamano_paquetes ; i++){
      data += "1";
    }
    sdManager->appendFile(filepath.c_str(), data);
    contador_datos_enviados += tamano_paquetes;
  }
  unsigned long tiempo_prueba = millis() - tiempo_inicio;
  long resultado = checkear_caracteres_validos(filepath, bytes_a_escribir);
  Serial.println("Bytes a escribir:");
  Serial.println(bytes_a_escribir);
  Serial.println("Bytes escritos correctamente: ");
  Serial.println(resultado);
  Serial.println("Tiempo de Prueba (msegundos): ");
  Serial.println(tiempo_prueba);
  Serial.println("Taza de transferencia (bytes/ms): ");
  Serial.println(resultado / tiempo_prueba);
}

void setup()
{
  sdManager = new SDManager(SD_CARD_PIN);
  Serial.begin(115200);
  delay(4000);

  for (int i = 0; i < sizeof(experimentos_tamanos) / sizeof(int); i++)
  {
    experimento(experimentos_tamanos[i]);
  }
}

void loop()
{
}
