#include "my_test.h"
#include "mhash.h"
#include <cstdlib>

void CMyTestSuite::TestMD5()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [64];
	byte 	*mresult;

	system("rm -f tests/test_file_openssl");
	system("openssl dgst -hex -md5 tests/test >> tests/test_file_openssl");
	
	ifst.open("tests/test");
	mresult = mhash::md5(ifst, ofst);
	ifst.close();

	ifst.open("tests/test_file_openssl");
	ifst >> (char*) mdigest;
	ifst >> (char*) mdigest;
	ifst.close();

	for(int i = 0; i < 16; i++)
	TS_ASSERT_EQUALS(mresult[i], mhash::chr2_chr(mdigest[2*i], mdigest[2*i + 1]));
}

void CMyTestSuite::TestSHA1()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [64];
	byte 	*mresult;

	system("rm -f tests/test_file_openssl");
	system("openssl dgst -hex -sha1 tests/test >> tests/test_file_openssl");
	
	ifst.open("tests/test");
	mresult = mhash::sha1(ifst, ofst);
	ifst.close();

	ifst.open("tests/test_file_openssl");
	ifst >> (char*) mdigest;
	ifst >> (char*) mdigest;
	ifst.close();

	for(int i = 0; i < 20; i++)
	TS_ASSERT_EQUALS(mresult[i], mhash::chr2_chr(mdigest[2*i], mdigest[2*i + 1]));
}

void CMyTestSuite::TestRIPEMD160()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [64];
	byte 	*mresult;

	system("rm -f tests/test_file_openssl");
	system("openssl dgst -hex -ripemd160 tests/test >> tests/test_file_openssl");
	
	ifst.open("tests/test");
	mresult = mhash::ripemd160(ifst, ofst);
	ifst.close();

	ifst.open("tests/test_file_openssl");
	ifst >> (char*) mdigest;
	ifst >> (char*) mdigest;
	ifst.close();

	for(int i = 0; i < 20; i++)
	TS_ASSERT_EQUALS(mresult[i], mhash::chr2_chr(mdigest[2*i], mdigest[2*i + 1]));
}

void CMyTestSuite::TestGOST1194()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [64];
	byte 	*mresult;

	system("rm -f tests/test_file_openssl");
	system("openssl dgst -hex -md_gost94 tests/test >> tests/test_file_openssl");
	
	ifst.open("tests/test");
	mresult = mhash::gost94(ifst, ofst);
	ifst.close();

	ifst.open("tests/test_file_openssl");
	ifst >> (char*) mdigest;
	ifst >> (char*) mdigest;
	ifst.close();

	for(int i = 0; i < 32; i++)
	TS_ASSERT_EQUALS(mresult[i], mhash::chr2_chr(mdigest[2*i], mdigest[2*i + 1]));
}
