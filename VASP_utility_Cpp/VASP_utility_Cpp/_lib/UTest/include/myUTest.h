#ifndef __MYUTEST_H__
#define __MYUTEST_H__

/**
* @author Andrei-KS
*/
class myUTest
{
public:
  virtual ~myUTest() = 0;
	virtual void excute() = 0;
	static myUTest* Utest;
};

#endif // !__MYUTEST_H__