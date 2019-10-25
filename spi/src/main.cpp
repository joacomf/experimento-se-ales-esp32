#include "Arduino.h"
#include <SDController.h>
#define TAMANO_PAQUETES 20

SDController sdController = SDController();
int experimentos_tamanos[] = {20, 200, 2000, 20000};

long checkear_caracteres_validos(char *valores, long n)
{
  long resultado = 0;
  for (int i = 0; i < n; i++)
  {
    if (valores[i] == '1')
    {
      resultado++;
    }
  }
  return resultado;
}

void experimento(long bytes_a_escribir)
{
  sdController.deleteFile();
  int contador_datos_enviados = 0;
  unsigned long tiempo_inicio = millis();
  int tamano_paquetes = TAMANO_PAQUETES;
  while (contador_datos_enviados < bytes_a_escribir)
  {
    if (bytes_a_escribir - contador_datos_enviados < tamano_paquetes)
    {
      tamano_paquetes = bytes_a_escribir - contador_datos_enviados;
    }
    char str[tamano_paquetes];
    memset(str, '1', tamano_paquetes);
    sdController.appendFile(string(str));
    contador_datos_enviados += tamano_paquetes;
  }
  unsigned long tiempo_prueba = millis() - tiempo_inicio;
  long resultado = checkear_caracteres_validos(sdController.readFile(bytes_a_escribir), bytes_a_escribir);
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
