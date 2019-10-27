/*
* Connect the SD card to the following pins:
*
* SD Card | ESP32
* CS D5
* MOSI D23
* 3.3V 3.3V
* CLK D18
* GND GND
* MISO D19
*/

#include "Arduino.h"
#include "SDController.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <string>

using namespace std;

SDController::SDController()
{
    if (checkStart())
    {
        File file = SD.open(path, FILE_WRITE);
        file.close();
    }
}

bool SDController::checkStart()
{
    if (!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return false;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return false;
    }
    return true;
}

char *SDController::readFile(unsigned int size)
{
    Serial.printf("Reading file: %s\n", path);

    File file = SD.open(path);
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return 0;
    }

    Serial.print("Read from file: ");
    // dataNumber es el número de registro de dato que quiero leer desde 0.
    char *value = new char[size + 1];
    // file.seek(position);

    unsigned long readed = 0;
    while (file.available())
    {
        value[readed++] = file.read();
    }
    value[readed] = '\0';
    Serial.println(value);
    return value;
}

void SDController::appendFile(string data)
{
    File file = SD.open(path, FILE_APPEND);
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.write((unsigned char *)data.c_str(), data.size() * 8))
    {
    }
    else
    {
        Serial.println("Append failed");
    }
    file.close();
}

void SDController::deleteFile()
{
    Serial.printf("Deleting file: %s\n", path);
    if (SD.remove(path))
    {
        Serial.println("File deleted");
    }
    else
    {
        Serial.println("Delete failed");
    }
}
