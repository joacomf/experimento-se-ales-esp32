#include "Arduino.h"
#include <SDManager.h>
#include <NumberToString.h>
#include "FileIterator.h"
#define CHARACTER 'X'
#define TAMANO_PAQUETES 50000
#define SD_CARD_PIN 5

SDManager *sdManager;

int experimentos_tamanos[] = {20, 200, 2 * 1024, 20 * 1024, 200 * 1024};

long checkear_caracteres_validos(std::string filepath, long max)
{
  long contador = 0;
  long resultado = 0;
  FileIterator fileIterator = FileIterator(filepath.c_str(), sdManager);
  std::string line;
  while (fileIterator.hasNext()){
    line = fileIterator.nextLine();
    for (int i = 0; i < TAMANO_PAQUETES; i++)
    {
      contador++;
      if (contador > max)
      {
        break;
      }
      if (line.c_str()[i] == CHARACTER)
      {
        resultado++;
      }
    }
    if (contador > max)
    {
      break;
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
    for (int i = 0; i < tamano_paquetes; i++)
    {
      data += CHARACTER;
    }
    data += "\n";
    sdManager->appendFile(filepath.c_str(), data);
    contador_datos_enviados += tamano_paquetes;
  }
  unsigned long tiempo_prueba = millis() - tiempo_inicio;
  long resultado = checkear_caracteres_validos(filepath, bytes_a_escribir);
  Serial.print("Bytes a escribir: ");
  Serial.println(bytes_a_escribir);
  Serial.print("Bytes escritos correctamente: ");
  Serial.print(100 * float(resultado)/float(bytes_a_escribir));
  Serial.println(" %");
  Serial.print("Tiempo de Prueba: ");
  Serial.print(tiempo_prueba);
  Serial.println(" ms");
  Serial.print("Taza de transferencia: ");
  Serial.print(1000 * float(resultado) / float(tiempo_prueba) / 1024);
  Serial.println(" KB/s");
  Serial.println("|");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\n");
  Serial.println("--------------------------------");
  Serial.println("Iniciando experimento\n");
  sdManager = new SDManager(SD_CARD_PIN);
  int cantidad_experimentos = sizeof(experimentos_tamanos) / sizeof(int);
  for (int i = 0; i < cantidad_experimentos; i++)
  {
    experimento(experimentos_tamanos[i]);
  }

  Serial.println("Fin");
  Serial.println("--------------------------------");
}

void loop()
{
}
