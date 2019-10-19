#pragma once

#include <string>

using namespace std;

class SDController
{
public:
  SDController();
  // Retorna el mensaje almacenado en la posicion "position"
  virtual char *readFile();
  // Almacena en la SD el string "data" luego de la ultima informacion guardada
  virtual void appendFile(string data);
  virtual void deleteFile();
  virtual bool checkStart();
  // Retorna el ultimo indice donde se almaceno informacion
  virtual unsigned long getNumberOfData();

private:
  // dataSize es al tamaño de dato almacenado en el registro.
  unsigned long dataSize = 1;
  unsigned long lastDataStore = 0;
  const char *path = "/pruebas.txt";
};
