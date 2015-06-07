#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

typedef unsigned int		uint32;
typedef unsigned long long	uint64;
typedef unsigned char		byte;

class mhash
{
public:
	static byte* sha1(ifstream &ifst, ofstream &ofst);
	static byte* md5(ifstream &ifst, ofstream &ofst);
	static byte* ripemd160(ifstream &ifst, ofstream &ofst);
	static byte* gost94(ifstream &ifst, ofstream &ofst);

	static void u32_chr(uint32 ui32, byte* (&m), int offset);
	static void u32_rchr(uint32 ui32, byte* (&m), int offset);

	static int r_fst(ifstream &ifst, byte* (&m));

	static void u32_str(uint32 i, string &os);
	static void u32_rstr(uint32 i, string &os);

	static byte chr2_chr(byte c1, byte c2);

	static uint32 ROL(uint32 a, int offset);
	static uint64 LROL(uint64 a, int offset);
};
