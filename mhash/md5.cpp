#include "mhash.h"

uint32 X[16];

int FunctionF(int x, int y, int z)
{
	return ((x & y) | (~x & z));
}
int FunctionG(int x, int y, int z)
{
	return ((x & z) | (y & ~z));
}
int FunctionH(int x, int y, int z)
{
	return (x ^ y ^ z);
}
int FunctionI(int x, int y, int z)
{
	return (y ^ (x | ~z));
}

int Round1(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + mhash::ROL((a + FunctionF(b, c, d) + X[k] + i), s));
}
int Round2(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + mhash::ROL((a + FunctionG(b, c, d) + X[k] + i), s));
}
int Round3(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + mhash::ROL((a + FunctionH(b, c, d) + X[k] + i), s));
}
int Round4(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + mhash::ROL((a + FunctionI(b, c, d) + X[k] + i), s));
}

byte* mhash::md5(ifstream &ifst, ofstream &ofst)
{
	if (!ifst.is_open())
	{
		return NULL;
	}

	byte	*M;

	uint32	AA;
	uint32	BB;
	uint32	CC;
	uint32	DD;

	uint64	TEMPL;
	uint32	RL = 0;
	uint32	NL = 0;

	uint32	A = 0x67452301;
	uint32	B = 0xefcdab89;
	uint32	C = 0x98badcfe;
	uint32	D = 0x10325476;
	

	ifst.seekg(0, ios::end);
	RL = ifst.tellg();
	NL = RL;
	ifst.seekg(0, ios::beg);

	if (NL == 56)			NL++;
	while (NL % 64 != 56)	NL++;

	M = new byte[NL + 8];
	memset(M, 0, sizeof (byte) * (NL + 8));
	ifst >> (char *) M;

	RL = strlen((char *) M);

	M[RL] = 0x80;	
	for (uint32 i = RL + 1; i < NL; i++)
	M[i] = 0;

	TEMPL = RL * 8;
	for (int i = NL; i < NL + 8; i++)
	{
		M[i] = TEMPL;
		TEMPL = TEMPL >> 8;
	}

	if (NL % 64 == 0)	NL = NL / 64;
	else				NL = NL / 64 + 1;

	for (uint32 k = 0; k < NL; k++)
	{
		for (int i = 0; i < 16; i++)
		for (int j = 3; j >= 0; j--)
		{
			X[i] = (X[i] << 8);
			X[i] += M[64 * k + 4 * i + j];
		}

		AA = A;
		BB = B;
		CC = C;
		DD = D;

		A = Round1(A, B, C, D, 0, 7, 0xD76AA478);
		D = Round1(D, A, B, C, 1, 12, 0xE8C7B756);
		C = Round1(C, D, A, B, 2, 17, 0x242070DB);
		B = Round1(B, C, D, A, 3, 22, 0xC1BDCEEE);
		A = Round1(A, B, C, D, 4, 7, 0xF57C0FAF);
		D = Round1(D, A, B, C, 5, 12, 0x4787C62A);
		C = Round1(C, D, A, B, 6, 17, 0xA8304613);
		B = Round1(B, C, D, A, 7, 22, 0xFD469501);
		A = Round1(A, B, C, D, 8, 7, 0x698098D8);
		D = Round1(D, A, B, C, 9, 12, 0x8B44F7AF);
		C = Round1(C, D, A, B, 10, 17, 0xFFFF5BB1);
		B = Round1(B, C, D, A, 11, 22, 0x895CD7BE);
		A = Round1(A, B, C, D, 12, 7, 0x6B901122);
		D = Round1(D, A, B, C, 13, 12, 0xFD987193);
		C = Round1(C, D, A, B, 14, 17, 0xA679438E);
		B = Round1(B, C, D, A, 15, 22, 0x49B40821);

		A = Round2(A, B, C, D, 1, 5, 0xF61E2562);
		D = Round2(D, A, B, C, 6, 9, 0xC040B340);
		C = Round2(C, D, A, B, 11, 14, 0x265E5A51);
		B = Round2(B, C, D, A, 0, 20, 0xE9B6C7AA);
		A = Round2(A, B, C, D, 5, 5, 0xD62F105D);
		D = Round2(D, A, B, C, 10, 9, 0x02441453);
		C = Round2(C, D, A, B, 15, 14, 0xD8A1E681);
		B = Round2(B, C, D, A, 4, 20, 0xE7D3FBC8);
		A = Round2(A, B, C, D, 9, 5, 0x21E1CDE6);
		D = Round2(D, A, B, C, 14, 9, 0xC33707D6);
		C = Round2(C, D, A, B, 3, 14, 0xF4D50D87);
		B = Round2(B, C, D, A, 8, 20, 0x455A14ED);
		A = Round2(A, B, C, D, 13, 5, 0xA9E3E905);
		D = Round2(D, A, B, C, 2, 9, 0xFCEFA3F8);
		C = Round2(C, D, A, B, 7, 14, 0x676F02D9);
		B = Round2(B, C, D, A, 12, 20, 0x8D2A4C8A);

		A = Round3(A, B, C, D, 5, 4, 0xFFFA3942);
		D = Round3(D, A, B, C, 8, 11, 0x8771F681);
		C = Round3(C, D, A, B, 11, 16, 0x6D9D6122);
		B = Round3(B, C, D, A, 14, 23, 0xFDE5380C);
		A = Round3(A, B, C, D, 1, 4, 0xA4BEEA44);
		D = Round3(D, A, B, C, 4, 11, 0x4BDECFA9);
		C = Round3(C, D, A, B, 7, 16, 0xF6BB4B60);
		B = Round3(B, C, D, A, 10, 23, 0xBEBFBC70);
		A = Round3(A, B, C, D, 13, 4, 0x289B7EC6);
		D = Round3(D, A, B, C, 0, 11, 0xEAA127FA);
		C = Round3(C, D, A, B, 3, 16, 0xD4EF3085);
		B = Round3(B, C, D, A, 6, 23, 0x04881D05);
		A = Round3(A, B, C, D, 9, 4, 0xD9D4D039);
		D = Round3(D, A, B, C, 12, 11, 0xE6DB99E5);
		C = Round3(C, D, A, B, 15, 16, 0x1FA27CF8);
		B = Round3(B, C, D, A, 2, 23, 0xC4AC5665);

		A = Round4(A, B, C, D, 0, 6, 0xF4292244);
		D = Round4(D, A, B, C, 7, 10, 0x432AFF97);
		C = Round4(C, D, A, B, 14, 15, 0xAB9423A7);
		B = Round4(B, C, D, A, 5, 21, 0xFC93A039);
		A = Round4(A, B, C, D, 12, 6, 0x655B59C3);
		D = Round4(D, A, B, C, 3, 10, 0x8F0CCC92);
		C = Round4(C, D, A, B, 10, 15, 0xFFEFF47D);
		B = Round4(B, C, D, A, 1, 21, 0x85845DD1);
		A = Round4(A, B, C, D, 8, 6, 0x6FA87E4F);
		D = Round4(D, A, B, C, 15, 10, 0xFE2CE6E0);
		C = Round4(C, D, A, B, 6, 15, 0xA3014314);
		B = Round4(B, C, D, A, 13, 21, 0x4E0811A1);
		A = Round4(A, B, C, D, 4, 6, 0xF7537E82);
		D = Round4(D, A, B, C, 11, 10, 0xBD3AF235);
		C = Round4(C, D, A, B, 2, 15, 0x2AD7D2BB);
		B = Round4(B, C, D, A, 9, 21, 0xEB86D391);

		A += AA;
		B += BB;
		C += CC;
		D += DD;
	}
	
	byte *m = new byte[17];

	u32_rchr(A, m, 0);
	u32_rchr(B, m, 4);
	u32_rchr(C, m, 8);
	u32_rchr(D, m, 12);

	if (ofst.is_open())
	{
		ofst.fill('0');

		for (int i = 0; i < 4; i++)
		{
			ofst << hex << setw(2) << (A & 0xff); A >>= 8;
		}
		for (int i = 0; i < 4; i++)
		{
			ofst << hex << setw(2) << (B & 0xff); B >>= 8;
		}
		for (int i = 0; i < 4; i++)
		{
			ofst << hex << setw(2) << (C & 0xff); C >>= 8;
		}
		for (int i = 0; i < 4; i++)
		{
			ofst << hex << setw(2) << (D & 0xff); D >>= 8;
		}
	}

	return m;
}
