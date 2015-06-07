#include "mhash.h"

uint32 FUNCTION(uint32 i, uint32 x, uint32 y, uint32 z)
{
	if (i < 16) return (x ^ y ^ z);
	else if (i < 32) return ((x & y) | ((~x) & z));
	else if (i < 48) return ((x | (~y)) ^ z);
	else if (i < 64) return ((x & z) | (y & (~z)));
	else if (i < 80) return (x ^ (y | (~z)));
}

uint32 K(uint32 i)
{
	if (i < 16) return 0x00000000;
	else if (i < 32) return 0x5A827999;
	else if (i < 48) return 0x6ED9EBA1;
	else if (i < 64) return 0x8F1BBCDC;
	else if (i < 80) return 0xA953FD4E;
}

uint32 Kv(uint32 i)
{
	if (i < 16) return 0x50A28BE6;
	else if (i < 32) return 0x5C4DD124;
	else if (i < 48) return 0x6D703EF3;
	else if (i < 64) return 0x7A6D76E9;
	else if (i < 80) return 0x00000000;
}


byte* mhash::ripemd160(ifstream &ifst, ofstream &ofst)
{
	if (!ifst.is_open())
	{
		return NULL;
	}

	byte *M;

	uint64	TEMPL;
	uint32	T;
	uint32	H[5];
	uint32	X[16];
	uint32	RL = 0;
	uint32	NL = 0;

	uint32	A, Av;
	uint32	B, Bv;
	uint32	C, Cv;
	uint32	D, Dv;
	uint32	E, Ev;

	uint32	R[80] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
		3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
		1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
		4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13
	};
	uint32	Rv[80] = { 5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
		6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
		15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
		8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
		12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11
	};
	uint32 S[80] = { 11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
		7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
		11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
		11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
		9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6
	};
	uint32 Sv[80] = { 8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
		9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
		9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
		15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
		8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11
	};

	H[0] = 0x67452301;
	H[1] = 0xEFCDAB89;
	H[2] = 0x98BADCFE;
	H[3] = 0x10325476;
	H[4] = 0xC3D2E1F0;

	ifst.seekg(0, ios::end);
	RL = (uint32)ifst.tellg();
	NL = RL;
	ifst.seekg(0, ios::beg);

	if (NL == 56)			NL++;
	while (NL % 64 != 56)	NL++;

	M = new byte[NL + 8];
	memset(M, 0, sizeof (byte) * (NL + 8));
	ifst >> (char*) M;

	RL = strlen((char*) M);

	M[RL] = 0x80;
	for (uint32 i = RL + 1; i < NL; i++)
	M[i] = 0;

	TEMPL = RL * 8;
	for (uint32 i = NL; i < NL + 8; i++)
	{
		M[i] = (byte)TEMPL;
		TEMPL = TEMPL >> 8;
	}

	if (NL % 64 == 0)	NL = NL / 64;
	else				NL = NL / 64 + 1;

	for (uint32 n = 0; n < NL; ++n)
	{
		for (int i = 0; i < 16; ++i)
		for (int j = 3; j >= 0; --j)
		{
			X[i] = (X[i] << 8);
			X[i] += M[64 * n + 4 * i + j];
		}

		A = H[0];		Av = H[0];
		B = H[1];		Bv = H[1];
		C = H[2];		Cv = H[2];
		D = H[3];		Dv = H[3];
		E = H[4];		Ev = H[4];

		for (uint32 i = 0; i < 80; ++i)
		{
			T = ROL((A + FUNCTION(i, B, C, D) + X[R[i]] + K(i)), S[i]) + E;
			A = E;
			E = D;
			D = ROL(C, 10);
			C = B;
			B = T;

			T = ROL(Av + FUNCTION(79 - i, Bv, Cv, Dv) + X[Rv[i]] + Kv(i), Sv[i]) + Ev;
			Av = Ev;
			Ev = Dv;
			Dv = ROL(Cv, 10);
			Cv = Bv;
			Bv = T;
		}

		T = H[1] + C + Dv;
		H[1] = H[2] + D + Ev;
		H[2] = H[3] + E + Av;
		H[3] = H[4] + A + Bv;
		H[4] = H[0] + B + Cv;
		H[0] = T;
	}

	byte *m = new byte[21];

	u32_rchr(H[0], m, 0);
	u32_rchr(H[1], m, 4);
	u32_rchr(H[2], m, 8);
	u32_rchr(H[3], m, 12);
	u32_rchr(H[4], m, 16);
	

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
