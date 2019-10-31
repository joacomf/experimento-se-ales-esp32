#include "SDManager.h"

SDManager::SDManager(uint8_t ssPin) : ssPin(ssPin)
{
}

bool SDManager::isValidSD()
{
    if (!SD.begin(this->ssPin))
    {
        Serial.println("SD Card Mount Failed");
        LedBlinker::blink(2, 500, 1000);
        return false;
    }
    if (SD.cardType() == CARD_NONE)
    {
        Serial.println("No SD card attached");
        LedBlinker::blink(2, 500, 1000);
        return false;
    }
    return true;
}

bool SDManager::writeFile(const char *path, const std::string data)
{
    if (!isValidSD())
    {
        return false;
    }
    File file = SD.open(path, FILE_WRITE);
    bool result = file && file.print(data.c_str());
    file.close();

    return result;
}

std::vector<std::string> SDManager::getFiles(const char *dirname)
{
    std::vector<std::string> files = std::vector<std::string>();
    if (!isValidSD())
    {

        return files;
    }
    File root = SD.open(dirname);
    if (!root || !root.isDirectory())
    {

        return files;
    }
    File file = root.openNextFile();
    while (file)
    {
        if (!file.isDirectory())
        {
            files.push_back(file.name());
        }
        file.close();
        file = root.openNextFile();
    }
    file.close();
    root.close();

    return files;
}

void SDManager::listDir(const char *dirname, uint8_t levels)
{
    if (!isValidSD())
    {
        return;
    }
    Serial.printf("Listing directory: %s\n", dirname);

    File root = SD.open(dirname);

    if (!root)
    {
        Serial.println("Failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        root.close();
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (file.isDirectory())
        {
            Serial.print(" DIR : ");
            Serial.println(file.name());
            if (levels)
            {
                listDir(file.name(), levels - 1);
            }
        }
        else
        {
            Serial.print(" FILE: ");
            Serial.print(file.name());
            Serial.print(" SIZE: ");
            Serial.println(file.size());
        }
        file.close();
        file = root.openNextFile();
    }
    file.close();
    root.close();

    return;
}

void SDManager::createDir(const char *path)
{
    if (!isValidSD())
    {
        return;
    }
    Serial.printf("Creating Dir: %s\n", path);
    if (SD.mkdir(path))
    {
        Serial.println("Dir created");
    }
    else
    {
        Serial.println("mkdir failed");
    }
    return;
}

void SDManager::removeDir(const char *path)
{
    if (!isValidSD())
    {
        return;
    }
    Serial.printf("Removing Dir: %s\n", path);
    if (SD.rmdir(path))
    {
        Serial.println("Dir removed");
    }
    else
    {
        Serial.println("rmdir failed");
    }
    return;
}

std::vector<std::string> *SDManager::readFileLines(const char *path)
{
    std::vector<std::string> *list = new std::vector<std::string>();
    if (!isValidSD())
    {
        return list;
    }
    File file = SD.open(path);
    if (!file)
    {
        return list;
    }
    while (file.available())
    {
        std::string data = file.readStringUntil('\n').c_str();
        list->push_back(data);
    }
    file.close();

    return list;
}

std::string SDManager::readLine(const char *path, unsigned int index)
{
    if (!isValidSD())
    {
        return "ERR";
    }
    File file = SD.open(path);
    if (!file)
    {
        return "ERR";
    }
    size_t recNum = 1;
    while (file.available())
    {
        std::string list = file.readStringUntil('\n').c_str();
        if (recNum == index)
        {
            file.close();
            return list;
        }
        recNum++;
    }
    file.close();

    return "EOF";
}

bool SDManager::appendFile(const char *path, const std::string data)
{
    if (!isValidSD())
    {
        return false;
    }
    File file = SD.open(path, FILE_APPEND);
    bool result = file && file.print(data.c_str());
    file.close();

    return result;
}

bool SDManager::renameFile(const char *path1, const char *path2)
{
    if (!isValidSD())
    {
        return false;
    }
    bool result = SD.rename(path1, path2);

    return result;
}

bool SDManager::deleteFile(const char *path)
{
    if (!isValidSD())
    {
        return false;
    }
    bool result = SD.remove(path);

    return result;
}

uint64_t SDManager::getCardSize()
{
    if (!isValidSD())
    {
        return false;
    }
    uint64_t result = SD.cardSize() / (1024 * 1024);

    return result;
}

bool SDManager::fileExists(std::string filename)
{
    if (!isValidSD())
    {
        return false;
    }
    File file = SD.open(filename.c_str());
    bool exists = file && !file.isDirectory();
    file.close();

    return exists;
}

size_t SDManager::getFileSize(std::string filename)
{
    size_t size = -1;
    if (!isValidSD())
    {
        return size;
    }
    File file = SD.open(filename.c_str());
    size = file.size();
    file.close();
    return size;
}

std::string SDManager::readFile(std::string filename)
{
    if (!isValidSD())
    {
        return "";
    }
    File file = SD.open(filename.c_str());
    if (!file)
    {
        return "";
    }
    std::string fileContent = "";
    while (file.available())
    {
        std::string line = file.readStringUntil('\n').c_str();
        fileContent.append(line);
        fileContent.append("\\n");
    }
    file.close();
    return fileContent;
}
