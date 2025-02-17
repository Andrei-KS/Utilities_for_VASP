#ifndef __STRINGPROCESSINGUTILITS_H__
#define __STRINGPROCESSINGUTILITS_H__

#include <string>
#include <vector>

/**
* @author Andrei-KS
*/
namespace StringProcessingUtilits
{
  struct FilePathInfo
  {
    std::string mName;
    std::string mPath;
  };

	/**
	* 
	*/
	std::vector<std::string> SplitStringToVector(const std::string& sourceString, const char delimiterSymbol = ' ');
  
  /**
  * 
  */
  char getPathSeparate();

  /**
  * 
  */
  FilePathInfo GetFilePathInfoFrom(const std::string& fullNameOfFile);
}

#endif // !__STRINGPROCESSINGUTILITS_H__