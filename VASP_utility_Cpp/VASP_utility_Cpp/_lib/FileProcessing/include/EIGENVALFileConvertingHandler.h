/*
  @author Andrei-KS
  created at the 2021
*/
#ifndef __EIGENVALFILECONVERTINGHANDLER_H__
#define __EIGENVALFILECONVERTINGHANDLER_H__

#include "TextFileHandler.h"

class EIGENVALFileConvertingHandler : public TextFileHandler
{
public:
	/**
	 * 
	 */
	EIGENVALFileConvertingHandler(std::string fileName);

	/**
	 * 
	 */
	~EIGENVALFileConvertingHandler();

	/**
	 * 
	 */
	virtual void Convert(std::string destinationFileName, double FermiEnergy = 0);

	/**
	 * 
	 */
	virtual void GetFermiSurface(std::string destinationFileName, double FermiEnergy = 0, double accuracy = 0.01);
};

#endif // !__EIGENVALFILECONVERTINGHANDLER_H__