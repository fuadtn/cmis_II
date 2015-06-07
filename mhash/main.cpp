#include "mhash.h"
#include "tests.h"
#include <getopt.h>
#include <cxxtest/ParenPrinter.h>

int main(int argc, char *argv[])
{
	ifstream ifst;
	ofstream ofst("tests/out");

	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},
		{"md5", 1, NULL, 'm'},
		{"sha1", 1, NULL, 's'},
		{"ripemd160", 1, NULL, 'r'},
		{"gost94", 1, NULL, 'g'},
		{"test", 0, NULL, 't'},
		{NULL,0,NULL,0},
	};
		
	switch (getopt_long(argc, argv, "ht", long_options, NULL))
	{
	case 'h':
	{
		cout << " -h, --help	\t\t helper" << endl;
		cout << " -t, --test \t\t\t testing of all hash programs" << endl;
		cout << " --md5 \t\t[input file] \t get MD5 hash in out file" << endl;
		cout << " --sha1 \t[input file] \t get SHA-1 hash in out file" << endl; 
		cout << " --ripemd160 \t[input file] \t get RIPEMD-160 hash in out file" << endl; 
		cout << " --mgost94 \t[input file] \t get GOST R 34.11-94 hash in out file" << endl; 
		return 0;	
	}  
	case 't':
	{
		CxxTest::ParenPrinter testRunner;
		testRunner.run();
		return 0;
	}         
	case 'm':
	{
		ifst.open(optarg);
		if (mhash::md5(ifst, ofst) == NULL)
		cout << "error: can't open file" << endl;
		return 0;
	}
	case 's':
	{
		ifst.open(optarg);
		if (mhash::sha1(ifst, ofst) == NULL)
		cout << "error: can't open file" << endl;
		return 0;
	}
	case 'r':
	{
		ifst.open(optarg);
		if (mhash::ripemd160(ifst, ofst) == NULL)
		cout << "error: can't open file" << endl;
		return 0;
	}
	case 'g':
	{
		ifst.open(optarg);
		if (mhash::gost94(ifst, ofst) == NULL)
		cout << "error: can't open file" << endl;
		return 0;
	}
	default:
		cout << "error: to few arguments" << endl;
		return 0;
	}
	return 0;
}
