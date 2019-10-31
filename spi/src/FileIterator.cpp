#include "FileIterator.h"

FileIterator::FileIterator(const char *path, SDManager *sdManager)
{
   this->sdManager = sdManager;
   if (!this->sdManager->isValidSD())
    {
        return;
    }
   this->file = SD.open(path);
}

std::string FileIterator::nextLine()
{
  std::string line = "EOF";
  if (!this->sdManager->isValidSD())
    {
        return line;
    }
  if(this->file.available()){
    line = this->file.readStringUntil('\n').c_str();
  }
  return line;
}

bool FileIterator::hasNext()
{
  return this->file.available();
}

FileIterator::~FileIterator()
{
  this->file.close();
}
