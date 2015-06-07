#include "mhash.h"

byte* mhash::sha1(ifstream &ifst, ofstream &ofst)
{
	if (!ifst.is_open())
	{
		return NULL;
	}

	byte *M;

	uint32	W[80];
	uint32	h[5];
	uint32	RL = 0;
	uint32	NL = 0;
	uint64	TEMPL;

	h[0] = 0x67452301;
	h[1] = 0xEFCDAB89;
	h[2] = 0x98BADCFE;
	h[3] = 0x10325476;
	h[4] = 0xC3D2E1F0;

	ifst.seekg(0, ios::end);
	RL = (uint32) ifst.tellg();
	NL = RL;
	ifst.seekg(0, ios::beg);

	if (NL == 56)			NL++;
	while (NL % 64 != 56)	NL++;

	M = new byte[NL + 8];
	memset(M, 0, sizeof (byte) * (NL + 8));
	ifst >> (char *) M;

	RL = strlen((char *) M);

	M[RL] = 0x80;
	for (uint32 i = RL + 1; i < NL; ++i)
	M[i] = 0;

	TEMPL = RL * 8;
	for (uint32 i = NL; i < NL + 8; ++i)
	{
		TEMPL = LROL(TEMPL, 8);
		M[i] = (byte) TEMPL;
	}

	if (NL % 64 == 0)	NL = NL / 64;
	else				NL = NL / 64 + 1;

	for (uint32 k = 0; k < NL; ++k)
	{
		for (uint32 i = 0; i < 16; ++i)
		for (uint32 j = 0; j < 4; ++j)
		{
			W[i] = (W[i] << 8);
			W[i] += M[64 * k + 4 * i + j];
		}

		for (uint32 i = 16; i < 80; i++)
		{
			W[i] = ROL((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]), 1);
		}

		uint32 a = h[0];
		uint32 b = h[1];
		uint32 c = h[2];
		uint32 d = h[3];
		uint32 e = h[4];
		uint32 f;
		uint32 t;

		for (uint32 i = 0; i < 80; i++)
		{
			if (i < 20)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (i < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (i < 60)
			{
				f = (b & c) ^ (b & d) ^ (c & d);
				k = 0x8F1BBCDC;
			}
			else if (i < 80)
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			t = ROL(a, 5) + f + e + k + W[i];
			e = d;
			d = c;
			c = ROL(b, 30);
			b = a;
			a = t;
		}

		h[0] = h[0] + a;
		h[1] = h[1] + b;
		h[2] = h[2] + c;
		h[3] = h[3] + d;
		h[4] = h[4] + e;
	}


	if (ofst.is_open())
	{
		ofst.fill('0');

		ofst << hex << setw(8) << h[0] << h[1] << h[2] << h[3] << h[4];
	}

	byte *m = new byte[21];

	u32_chr(h[0], m, 0);
	u32_chr(h[1], m, 4);
	u32_chr(h[2], m, 8);
	u32_chr(h[3], m, 12);
	u32_chr(h[4], m, 16);
	
	delete[] M;
	return m;
}
