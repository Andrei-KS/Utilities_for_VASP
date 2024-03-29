#ifndef __FILEHANDLER_H__
#define __FILEHANDLER_H__

#include <fstream>
#include <string>

/**
* The class is responsible for opening and closing a file
* @see fstream
* @author Andrei-KS
*/
class FileHandler
{
public:
	/**
	* Associates a file with this class when constructing it
	* @param fileName - The name of the file that will be associated with this object 
	*/
	FileHandler(std::string fileName);

	/**
	* When a class is destroyed, it closes the file associated with this class 
	*/
	virtual ~FileHandler();

protected:
	/**
	* Getting a link to the fstream of the file associated with this object 
	* @return link to the fstream associated with this object
	*/
	std::fstream& getFile();

private:
	/** contains descriptor opened file */
	std::fstream itsFile;
};

#endif // !__FILEHANDLER_H__