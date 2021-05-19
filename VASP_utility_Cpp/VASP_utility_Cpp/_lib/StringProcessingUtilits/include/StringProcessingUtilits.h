#ifndef __STRINGPROCESSINGUTILITS_H__
#define __STRINGPROCESSINGUTILITS_H__

#include <string>
#include <vector>

/**
* @author Andrei-KS
*/
namespace StringProcessingUtilits
{
	/**
	* 
	*/
	std::vector<std::string> SplitStringToVector(const std::string& sourceString, const char delimiterSymbol = ' ');
}

#endif // !__STRINGPROCESSINGUTILITS_H__