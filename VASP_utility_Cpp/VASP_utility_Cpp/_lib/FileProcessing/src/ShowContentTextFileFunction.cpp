

#include "ShowContentTextFileFunction.h"
#include "TextFileHandler.h"

ShowContentTextFileFunction::ShowContentTextFileFunction(std::string fileName)
{
	itsFileHandler = new TextFileHandler(fileName);
}

ShowContentTextFileFunction::~ShowContentTextFileFunction()
{
	delete itsFileHandler;
}

void ShowContentTextFileFunction::execute()
{
	itsFileHandler->ShowContent();
}