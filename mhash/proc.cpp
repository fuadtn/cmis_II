#include "mhash.h"

unsigned int mhash::ROL(unsigned int a, int offset)
{
	return a << offset | a >> (32 - offset);
}

unsigned long long mhash::LROL(unsigned long long a, int offset)
{
	return a << offset | a >> (64 - offset);
}

void mhash::u32_str(unsigned int i, string &os)
{
	string ts = "0123456789abcdef";

	for (int k = 7; k >= 0; --k)
	{
		os = os + ts[(i >> (4 * k)) & 0xf];
	}
}

void mhash::u32_rstr(unsigned int i, string &os)
{
	string ts = "0123456789abcdef";

	for (int k = 0; k < 4; ++k)
	{
		os = os + ts[(i >> (8 * k + 4)) & 0xf];
		os = os + ts[(i >> (8 * k)) & 0xf];
	}
}

void mhash::u32_chr(unsigned int ui32, byte* (&m), int offset)
{
	m[offset] 	  = ui32 >> 24;
	m[offset + 1] = ui32 >> 16;
	m[offset + 2] = ui32 >> 8;
	m[offset + 3] = ui32;
	m[offset + 4] = 0;
}

void mhash::u32_rchr(unsigned int ui32, byte* (&m), int offset)
{
	m[offset] 	  = ui32;
	m[offset + 1] = ui32 >> 8;
	m[offset + 2] = ui32 >> 16;
	m[offset + 3] = ui32 >> 24;
	m[offset + 4] = 0;
}

int mhash::r_fst(ifstream &ifst, byte* (&m))
{
	uint64 mlength = -1;
	if(!ifst.is_open()) return mlength;

	ifst.seekg(0, ios::end);
	mlength = ifst.tellg();
	ifst.seekg(0, ios::beg);
	
	m = new byte [mlength + 1];
	ifst.getline((char *) m, mlength + 1);
	return (mlength == 0) ? 0 : mlength - 1;
}

byte mhash::chr2_chr(byte c1, byte c2)
{
	byte alpha[] = "0123456789abcdef";
	byte result = 0;

	for (int i = 0; i < 16; i++)
	if (alpha[i] == c1)
	{
		result = i;
		result = result << 4;
		break;	
	}
	for (int i = 0; i < 16; i++)
	if (alpha[i] == c2)
	{
		result = result | i;
		break;
	}
	return result;
}
