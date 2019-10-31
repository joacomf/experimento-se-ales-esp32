#ifndef FileIterator_h
#define FileIterator_h

#include "SDManager.h"
#include <iostream>

class FileIterator {

    public:
        FileIterator(const char *path, SDManager *sdManager);
        std::string nextLine();
        bool hasNext();
        SDManager *sdManager;
        ~FileIterator();

    private:
        File file;
};

#endif
