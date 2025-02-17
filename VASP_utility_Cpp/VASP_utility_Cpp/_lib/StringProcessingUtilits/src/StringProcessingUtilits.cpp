

#include "StringProcessingUtilits.h"
#include <algorithm>

namespace StringProcessingUtilits {
  std::vector<std::string> SplitStringToVector(const std::string& sourceString, const char delimiterSymbol)
  {
    std::vector<std::string> outputVector;
    size_t currentWordInVetor = 0;
    bool addNewWordFlag = true;
    size_t sizeString = sourceString.size();
    for (size_t i = 0; i < sizeString; i++)
    {
      if ((sourceString[i] == delimiterSymbol) || (sourceString[i] == '\0'))
      {
        if (!addNewWordFlag)
        {
          addNewWordFlag = true;
          currentWordInVetor++;
        }
      }
      else
      {
        if (addNewWordFlag)
        {
          outputVector.push_back(std::string({ sourceString[i] }));
          addNewWordFlag = false;
        }
        else
        {
          outputVector[currentWordInVetor].push_back(sourceString[i]);
        }
      }
    }
    return std::move(outputVector);
  }

  char getPathSeparate()
  {
#if defined(WIN32)||defined(_WIN32)
    return '\\';
#else
    return '/';
#endif
  }

  FilePathInfo GetFilePathInfoFrom(const std::string& fullNameOfFile)
  {
    FilePathInfo result{ "", fullNameOfFile };
    result.mName.reserve(25);
    char seporator = getPathSeparate();
    
    while (!result.mPath.empty() && result.mPath.back() != seporator)
    {
      result.mName.push_back(result.mPath.back());
      result.mPath.pop_back();
    }

    std::reverse(result.mName.begin(), result.mName.end());
    
    return result;
  }
}