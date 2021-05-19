#ifndef __UTESTSPLITSTRINGTOVECTOR_H__
#define __UTESTSPLITSTRINGTOVECTOR_H__

#include "myUTest.h"
#include "StringProcessingUtilits.h"

/**
* Description of class UTestSplitStringToVector
* This class check function SplitStringToVector from StringProcessingUtilits
* 
* @see SplitStringToVector, StringProcessingUtilits
* @author Andrei-KS
*/
class UTestSplitStringToVector : public myUTest
{
public:
	/**
	* Function to run all tests
	*/
	virtual void excute() override;

protected:
	/**
	* Function check correct work function with empty string
	*/
	void TestEmptyString();

	/**
	* Function check correct work function with different amount one char words
	* @param symbol - test string contain only this symbols
	* @param delimiterSymbol - this symbol delimite words at test string
	* @param amountWords - amount words at test string
	*/
	void TestOfOneLetterWords(const char symbol, const char delimiterSymbol, const size_t amountWords);

	/**
	* Function check correct work function with different amount letter in words
	* @param words - vector contain strings with different length, which will be concatenated into a test string
	* @param delimiterSymbol - this symbol delimite words at test string
	*/
	void TestWithDifferentAmountLetterInWords(std::vector<std::string> words, const char delimiterSymbol);
};

#endif // !__UTESTSPLITSTRINGTOVECTOR_H__