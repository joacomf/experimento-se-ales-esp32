#ifndef ISDManager_h
#define ISDManager_h

#include <iostream>
#include <vector>

class ISDManager {

    public:
        virtual ~ISDManager() {};
        virtual bool isValidSD() = 0;
        virtual void listDir(const char * dirname, uint8_t levels) = 0;
        virtual std::vector<std::string> getFiles(const char *dirname) = 0;
        virtual void createDir(const char * path) = 0;
        virtual void removeDir(const char * path) = 0;
        virtual std::string readLine(const char * path, unsigned int index) = 0;
        virtual std::vector<std::string> *readFileLines(const char * path) = 0;
        virtual bool writeFile(const char * path, const std::string data) = 0;
        virtual bool appendFile(const char * path, const std::string data) = 0;
        virtual bool renameFile(const char * path1, const char * path2) = 0;
        virtual bool deleteFile(const char * path) = 0;
        virtual uint64_t getCardSize() = 0;
        virtual bool fileExists(std::string filename) = 0;
        virtual size_t getFileSize(std::string filename) = 0;
        virtual std::string readFile(std::string filename) = 0;
};

#endif
