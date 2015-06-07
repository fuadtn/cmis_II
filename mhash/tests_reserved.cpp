#include "my_test.h"
#include "mhash.h"
#include <cstdlib>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/ripemd.h>

void CMyTestSuite::Test1()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [MD5_DIGEST_LENGTH];
	byte 	*mresult;
	byte 	*mbuffer;
	uint64	 mlength;

	ifst.open("tests/test");
	mlength = mhash::r_fst(ifst, mbuffer);
	MD5(mbuffer, mlength, mdigest);
	ifst.close();

	ifst.open("tests/test");
	mresult = mhash::md5(ifst, ofst);
	ifst.close();
	ofst.close();

	cout << endl;
	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	cout << hex << (int) mdigest[i];	
	cout << endl;
	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	cout << hex << (int) mresult[i];	
		

	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	TS_ASSERT_EQUALS(mresult[i], mdigest[i]);
}

void CMyTestSuite::Test2()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [SHA_DIGEST_LENGTH];
	byte 	*mresult;
	byte 	*mbuffer;
	uint64	 mlength;

	ifst.open("tests/test");
	mlength = mhash::r_fst(ifst, mbuffer);
	SHA1(mbuffer, mlength, mdigest);
	ifst.close();
	
	ifst.open("tests/test");
	mresult = mhash::sha1(ifst, ofst);
	ifst.close();

	for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
	TS_ASSERT_EQUALS(mresult[i], mdigest[i]);
}

void CMyTestSuite::Test3()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [RIPEMD160_DIGEST_LENGTH];
	byte 	*mresult;
	byte 	*mbuffer;
	uint64	 mlength;

	ifst.open("tests/test");
	mlength = mhash::r_fst(ifst, mbuffer);
	RIPEMD160(mbuffer, mlength, mdigest);
	ifst.close();
	
	ifst.open("tests/test");
	mresult = mhash::ripemd160(ifst, ofst);
	ifst.close();

	for(int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++)
	TS_ASSERT_EQUALS(mresult[i], mdigest[i]);
}

void CMyTestSuite::Test4()
{
	ifstream ifst;
	ofstream ofst;

	byte 	*mdigest = new byte [32];
	byte 	*mbuffer = new byte [64];
	byte 	*mresult;
	uint64	 mlength;

//	system("rm -f tests/test_file_gostsum");
//	system("./tests/gostsum tests/test >> tests/test_file_gostsum");
	
	system("rm -f tests/test_file_openssl");
	system("openssl dgst -hex -md_gost94 tests/test >> tests/test_file_openssl");
	
	ifst.open("tests/test");
	mresult = mhash::gost94(ifst, ofst);
	ifst.close();

	ifst.open("tests/test_file_openssl");
	ifst >> (char*) mbuffer;
	ifst >> (char*) mbuffer;
	ifst.close();

	for(int i = 0; i < 32; i++)
	TS_ASSERT_EQUALS(mresult[i], mhash::chr2_chr(mbuffer[2*i], mbuffer[2*i + 1]));
}
