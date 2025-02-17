/*
  @author Andrei-KS
  created at the 2021
*/
#ifndef __TEXTFILEHANDLER_H__
#define __TEXTFILEHANDLER_H__

#include "FileHandler.h"

/**
* The class is responsible for opening and closing a file as text
* @author Andrei-KS
*/
class TextFileHandler : public FileHandler
{
public:
	/**
	* Associates a file with this class when constructing it
	* @param fileName - The name of the file that will be associated with this object
	*/
	TextFileHandler(std::string fileName);

	/**
	* When a class is destroyed, it closes the file associated with this class
	*/
	virtual ~TextFileHandler();

	/**
	* Displays the contents of a text file to iostream
	*/
	virtual void ShowContent();
};

#endif // !__TEXTFILEHANDLER_H__