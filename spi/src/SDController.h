#pragma once

#include <string>

using namespace std;

class SDController
{
public:
  SDController();
  // Retorna el mensaje almacenado en la posicion "position"
  virtual char *readFile(unsigned int size);
  // Almacena en la SD el string "data" luego de la ultima informacion guardada
  virtual void appendFile(string data);
  virtual void deleteFile();
  virtual bool checkStart();

private:
  const char *path = "/pruebas.txt";
};
