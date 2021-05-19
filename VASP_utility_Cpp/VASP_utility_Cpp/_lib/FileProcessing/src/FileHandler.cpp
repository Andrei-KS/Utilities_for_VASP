

#include "FileHandler.h"

FileHandler::FileHandler(std::string fileName)
{
	itsFile.open(fileName, std::fstream::in);
	if (itsFile.is_open() == false)
	{
		throw ("Error: FileHandler::FileHandler(std::string fileName): File was not open");
	}
}

FileHandler::~FileHandler()
{
	if (itsFile.is_open())
	{
		itsFile.close();
	}
}

std::fstream& FileHandler::getFile()
{
	return itsFile;
}