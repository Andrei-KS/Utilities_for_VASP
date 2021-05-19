

#include "UTestSplitStringToVector.h"
#include <cassert>

myUTest* myUTest::Utest = new UTestSplitStringToVector();

void UTestSplitStringToVector::excute()
{
	TestEmptyString();
	TestOfOneLetterWords('a',' ',5);
	TestOfOneLetterWords('a','-',6);
	TestOfOneLetterWords('a','-',0);
	TestWithDifferentAmountLetterInWords({ "a" }, '-');
	TestWithDifferentAmountLetterInWords({ "a", "ad" }, ' ');
	TestWithDifferentAmountLetterInWords({ "9842h", "aadad", "a3oirhn", "asidne" }, ' ');
}

void UTestSplitStringToVector::TestEmptyString()
{
	assert(StringProcessingUtilits::SplitStringToVector(std::string()).size() == 0);
}

void UTestSplitStringToVector::TestOfOneLetterWords(const char symbol, const char delimiterSymbol, const size_t amountWords)
{
	std::string testString;
	for (size_t i = 0; i < amountWords; i++)
	{
		testString.push_back(symbol);
		testString.push_back(delimiterSymbol);
	}
	assert(StringProcessingUtilits::SplitStringToVector(testString,delimiterSymbol).size() == amountWords);
}

void UTestSplitStringToVector::TestWithDifferentAmountLetterInWords(std::vector<std::string> words, const char delimiterSymbol)
{
	std::string testString;
	for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); it++)
	{
		testString += delimiterSymbol + (*it);
	}
	assert(StringProcessingUtilits::SplitStringToVector(testString, delimiterSymbol).size() == words.size());
}
