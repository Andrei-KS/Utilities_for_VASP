

#include "EIGENVALFileConvertingHandler.h"
#include "StringProcessingUtilits.h"

namespace FileProcessing
{
  EIGENVALFileConvertingHandler::EIGENVALFileConvertingHandler(std::string fileName)
    : TextFileHandler(fileName)
  {

  }

  EIGENVALFileConvertingHandler::~EIGENVALFileConvertingHandler()
  {

  }

  void EIGENVALFileConvertingHandler::Convert(double FermiEnergy /*= 0*/)
  {
    std::fstream& fs = getFile();
    StringProcessingUtilits::FilePathInfo filePathInfo = StringProcessingUtilits::GetFilePathInfoFrom(getFullFileName());
    std::string destinationFileName = filePathInfo.mPath + "_OUTPUT_EIGENVAL";
    std::fstream dfs(destinationFileName, std::ios::out | std::ios::trunc);

    if (!fs.is_open())
    {
      throw std::logic_error("Error: EIGENVALFileConvertingHandler::Convert(double FermiEnergy): Source File  was not open");
    }

    if (!dfs.is_open())
    {
      throw std::logic_error("Error: EIGENVALFileConvertingHandler::Convert(double FermiEnergy): Destination file was not open");
    }

    std::string currentLineRead;
    size_t currentLine = 0;
    size_t numberOfBands = 0;

    // reading head of file
    while (getline(fs, currentLineRead))
    {
      std::vector<std::string> splitedString = StringProcessingUtilits::SplitStringToVector(currentLineRead);
      currentLine++;
      if (currentLine == 6 && splitedString.size() == 3)
      {
        numberOfBands = std::stoul(splitedString[2]);
      }
      else if (currentLine > 6)
      {
        break;
      }
    }

    // reading data from file
    const size_t sizeBlockData = numberOfBands + 2;
    currentLine = 0;
    while (getline(fs, currentLineRead))
    {
      std::vector<std::string> splitedString = StringProcessingUtilits::SplitStringToVector(currentLineRead);
      currentLine++;
      if (currentLine == 1)
      { // write coordinate points
        if (splitedString.size() == 4)
        {
          for (size_t i = 0; i < 3; i++)
          {
            splitedString[i] += "\t";
            dfs.write(splitedString[i].c_str(), splitedString[i].size());
          }
        }
      }
      else if (currentLine == sizeBlockData)
      {
        dfs.write("\n", 1);
        currentLine = 0;
      }
      else
      {
        double value = std::stod(splitedString[1]) - FermiEnergy;
        splitedString[1] = std::to_string(value);
        splitedString[1] += "\t";
        if (splitedString.size() == 5)
        {
          value = std::stod(splitedString[2]) - FermiEnergy;
          splitedString[1] = std::to_string(value);
          splitedString[1] += "\t";
        }
        dfs.write(splitedString[1].c_str(), splitedString[1].size());
      }
    }

    // reset the end-of-file flag and return the carriage
    // to the beginning of the stream so that we can read it again 
    fs.clear();
    fs.seekg(0);

    dfs.close();

  }

  void EIGENVALFileConvertingHandler::GetFermiSurface(std::string destinationFileName, double FermiEnergy /*= 0*/, double accuracy /*= 0.01*/)
  {
    std::fstream& fs = getFile();
    std::fstream dfs(destinationFileName, std::ios::out | std::ios::trunc);

    if (fs.is_open() && dfs.is_open())
    {
      std::string currentLineRead;
      size_t currentLine = 0;
      size_t numberOfBands = 0;

      // reading head of file
      while (getline(fs, currentLineRead))
      {
        std::vector<std::string> splitedString = StringProcessingUtilits::SplitStringToVector(currentLineRead);
        currentLine++;
        if (currentLine == 6 && splitedString.size() == 3)
        {
          numberOfBands = std::stoul(splitedString[2]);
        }
        else if (currentLine > 6)
        {
          break;
        }
      }

      // reading data from file
      const size_t sizeBlockData = numberOfBands + 2;
      currentLine = 0;
      bool bIsWrite = false;
      std::vector<std::string> coordintes;
      while (getline(fs, currentLineRead))
      {
        std::vector<std::string> splitedString = StringProcessingUtilits::SplitStringToVector(currentLineRead);
        currentLine++;
        if (currentLine == 1)
        {
          coordintes = splitedString;
          coordintes.pop_back();
        }
        else if (currentLine == sizeBlockData)
        {
          if (bIsWrite)
          {
            for (std::string& coordinte : coordintes)
            {
              coordinte += "\t";
              dfs.write(coordinte.c_str(), coordinte.size());
            }
            dfs.write("\n", 1);
          }
          bIsWrite = false;
          currentLine = 0;
        }
        else
        {
          double value = std::stod(splitedString[1]) - FermiEnergy;
          if (value <= accuracy && value >= -accuracy)
          {
            bIsWrite = true;
          }
        }
      }

      // reset the end-of-file flag and return the carriage
      // to the beginning of the stream so that we can read it again 
      fs.clear();
      fs.seekg(0);

      dfs.close();
    }
  }
}