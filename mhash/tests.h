/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#define _CXXTEST_ABORT_TEST_ON_FAIL
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_CMyTestSuite_init = false;
#include "/home/fuad/Desktop/mhash/my_test.h"

static CMyTestSuite suite_CMyTestSuite;

static CxxTest::List Tests_CMyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CMyTestSuite( "my_test.h", 4, "CMyTestSuite", suite_CMyTestSuite, Tests_CMyTestSuite );

static class TestDescription_suite_CMyTestSuite_TestMD5 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CMyTestSuite_TestMD5() : CxxTest::RealTestDescription( Tests_CMyTestSuite, suiteDescription_CMyTestSuite, 7, "TestMD5" ) {}
 void runTest() { suite_CMyTestSuite.TestMD5(); }
} testDescription_suite_CMyTestSuite_TestMD5;

static class TestDescription_suite_CMyTestSuite_TestSHA1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CMyTestSuite_TestSHA1() : CxxTest::RealTestDescription( Tests_CMyTestSuite, suiteDescription_CMyTestSuite, 8, "TestSHA1" ) {}
 void runTest() { suite_CMyTestSuite.TestSHA1(); }
} testDescription_suite_CMyTestSuite_TestSHA1;

static class TestDescription_suite_CMyTestSuite_TestRIPEMD160 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CMyTestSuite_TestRIPEMD160() : CxxTest::RealTestDescription( Tests_CMyTestSuite, suiteDescription_CMyTestSuite, 9, "TestRIPEMD160" ) {}
 void runTest() { suite_CMyTestSuite.TestRIPEMD160(); }
} testDescription_suite_CMyTestSuite_TestRIPEMD160;

static class TestDescription_suite_CMyTestSuite_TestGOST1194 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CMyTestSuite_TestGOST1194() : CxxTest::RealTestDescription( Tests_CMyTestSuite, suiteDescription_CMyTestSuite, 10, "TestGOST1194" ) {}
 void runTest() { suite_CMyTestSuite.TestGOST1194(); }
} testDescription_suite_CMyTestSuite_TestGOST1194;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
