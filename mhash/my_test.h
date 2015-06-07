#pragma once
#include <cxxtest/TestSuite.h>

class CMyTestSuite : public CxxTest::TestSuite
{
public:
	void TestMD5();
	void TestSHA1();
	void TestRIPEMD160();
	void TestGOST1194();
};
