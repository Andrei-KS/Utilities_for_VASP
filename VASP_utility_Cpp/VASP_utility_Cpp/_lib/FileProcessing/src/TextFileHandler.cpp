

#include "TextFileHandler.h"
#include <iostream>

namespace FileProcessing
{
  TextFileHandler::TextFileHandler(std::string fileName)
    : FileHandler(fileName)
  {
  }

  TextFileHandler::~TextFileHandler()
  {
  }

  void TextFileHandler::ShowContent()
  {
    std::fstream& fs = getFile();
    if (fs.is_open())
    {
      std::string currentLineRead;
      while (getline(fs, currentLineRead))
      {
        std::cout << currentLineRead << std::endl;
      }

      // reset the end-of-file flag and return the carriage
      // to the beginning of the stream so that we can read it again 
      fs.clear();
      fs.seekg(0);
    }
  }
}