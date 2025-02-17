

#include "FileHandler.h"
#include <stdexcept>

namespace FileProcessing
{
  FileHandler::FileHandler(std::string fileName)
  {
    mFile.open(fileName, std::fstream::in);
    if (mFile.is_open() == false)
    {
      throw std::logic_error("Error: FileHandler::FileHandler(std::string fileName): File was not open");
    }
    mName = fileName;
  }

  FileHandler::~FileHandler()
  {
    if (mFile.is_open())
    {
      mFile.close();
    }
  }

  std::fstream& FileHandler::getFile()
  {
    return mFile;
  }
}