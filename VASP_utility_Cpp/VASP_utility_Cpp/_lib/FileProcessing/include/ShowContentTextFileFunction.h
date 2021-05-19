#ifndef __SHOWCONTENTTEXTFILEFUNCTION_H__
#define __SHOWCONTENTTEXTFILEFUNCTION_H__

#include "CalledPanelFunction.h"
#include <string>
class TextFileHandler;

/**
* @author Andrei-KS
*/
class ShowContentTextFileFunction : public CalledPanelFunction
{
public:
	/**
	* 
	*/
	ShowContentTextFileFunction(std::string fileName);
	
	/**
	* 
	*/
	~ShowContentTextFileFunction();

	/**
	* 
	*/
	virtual void execute() override;

private:
	/**  */
	TextFileHandler* itsFileHandler;
};

#endif // !__SHOWCONTENTTEXTFILEFUNCTION_H__