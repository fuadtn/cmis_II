#include "mhash.h"
#include <string.h>

byte S1[8][16] = { // S-Box from GOST R 34.11-94
	{ 4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3 },
	{ 14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9 },
	{ 5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11 },
	{ 7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3 },
	{ 6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2 },
	{ 4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14 },
	{ 13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12 },
	{ 1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12 },
};

byte S[8][16] = { // S-Box from CryptoPro
{10 ,4 ,5 ,6 ,8 ,1 ,3 ,7 ,13 ,12 ,14 ,0 ,9 ,2 ,11 ,15},
{5 ,15 ,4 ,0 ,2 ,13 ,11 ,9 ,1 ,7 ,6 ,3 ,12 ,14 ,10 ,8},
{7 ,15 ,12 ,14 ,9 ,4 ,1 ,0 ,3 ,11 ,5 ,2 ,6 ,10 ,8 ,13},
{4 ,10 ,7 ,12 ,0 ,15 ,2 ,8 ,14 ,1 ,6 ,5 ,13 ,11 ,9 ,3},
{7 ,6 ,4 ,11 ,9 ,12 ,2 ,10 ,1 ,8 ,0 ,14 ,15 ,13 ,3 ,5},
{7 ,6 ,2 ,4 ,13 ,9 ,15 ,0 ,10 ,1 ,5 ,11 ,8 ,14 ,12 ,3},
{13 ,14 ,4 ,1 ,7 ,0 ,5 ,10 ,3 ,12 ,8 ,15 ,6 ,2 ,9 ,11},
{1 ,3 ,10 ,9 ,5 ,11 ,4 ,15 ,8 ,6 ,7 ,14 ,13 ,0 ,2 ,12},
};

void A(byte Y[], byte R[])
{
	for (uint32 i = 0; i < 24; i++)
	R[i] = Y[i + 8];
	
	for (uint32 i = 0; i < 8; i++)
	R[i + 24] = Y[i] ^ Y[i + 8];
}

uint32 fi(uint32 arg)
{
	uint32 i = arg & 0x03;
	uint32 k = arg >> 2; k++;
	return ((i << 3) + k - 1);
}

void P(byte Y[], byte R[])
{
	for (uint32 i = 0; i < 32; i++) R[i] = Y[fi(i)];
}

void gost89_f(byte A[], byte K[], byte R[])
{
	uint32 c = 0;
	for (uint32 i = 0; i < 4; i++) 
	{
		c += A[i] + K[i];
		R[i] = c & 0xFF;
		c >>= 8;
	}

	for (uint32 i = 0; i < 8; i++) 
	{
		uint32 x;
	
		if (i & 1) x = R[i >> 1] & 0xF0;
		else	   x = R[i >> 1] & 0x0F;

		R[i >> 1] ^= x;

		if (i & 1) x >>= 4;

		x = S[i][x];

		if (i & 1) R[i >> 1] |= x << 4;
		else	   R[i >> 1] |= x;
	}

	uint32 tmp = R[3];
	R[3] = R[2];
	R[2] = R[1];
	R[1] = R[0];
	R[0] = tmp;

	tmp = R[0] >> 5;
	for (uint32 i = 1; i < 4; i++) 
	{
		uint32 nTmp = R[i] >> 5;
		R[i] = (R[i] << 3) | tmp;
		tmp = nTmp;
	}
	R[0] = (R[0] << 3) | tmp;
}

void gost89(byte  D[], byte K[], byte R[]) 
{ 
	byte A[4];
	byte B[4];

	for (uint32 i = 0; i < 4; i++) A[i] = D[i];
	for (uint32 i = 0; i < 4; i++) B[i] = D[i + 4];

	for (uint32 step = 0; step < 3; step++)
	for (uint32 i = 0; i < 32; i += 4)
	{
		byte tmp[4];
		gost89_f(A, K + i, tmp);
		
		for (uint32 i = 0; i < 4; i++) tmp[i] ^= B[i];
		
		memcpy(B, A, sizeof A);
		memcpy(A, tmp, sizeof tmp);
	}

	for (int i = 28; i >= 0; i -= 4)
	{
		byte tmp[4];
		gost89_f(A, K + i, tmp);
		
		for (uint32 i = 0; i < 4; i++) tmp[i] ^= B[i];
		
		memcpy(B, A, sizeof A);
		memcpy(A, tmp, sizeof tmp);
	}

	for (uint32 i = 0; i < 4; i++) R[i] = B[i]; 
	for (uint32 i = 0; i < 4; i++) R[i + 4] = A[i];
}

void psi(byte arr[]) 
{
	byte y16[] = { 0, 0 };
	y16[0] ^= arr[0]; y16[1] ^= arr[1];
	y16[0] ^= arr[2]; y16[1] ^= arr[3];
	y16[0] ^= arr[4]; y16[1] ^= arr[5];
	y16[0] ^= arr[6]; y16[1] ^= arr[7];
	y16[0] ^= arr[24]; y16[1] ^= arr[25];
	y16[0] ^= arr[30]; y16[1] ^= arr[31];

	for (uint32 i = 0; i < 30; i++) 
	arr[i] = arr[i + 2];
	arr[30] = y16[0];
	arr[31] = y16[1];
}

void psi(byte arr[], uint32 p)
{
	while (p--) psi(arr);
}

void f(byte H[], byte M[], byte newH[])
{
	byte C[4][32];
	memset(C, 0, sizeof C);

	C[2][0] = 0x00;
	C[2][1] = 0xFF;
	C[2][2] = 0x00;
	C[2][3] = 0xFF;
	C[2][4] = 0x00;
	C[2][5] = 0xFF;
	C[2][6] = 0x00;
	C[2][7] = 0xFF;
	C[2][8] = 0xFF;
	C[2][9] = 0x00;
	C[2][10] = 0xFF;
	C[2][11] = 0x00;
	C[2][12] = 0xFF;
	C[2][13] = 0x00;
	C[2][14] = 0xFF;
	C[2][15] = 0x00;
	C[2][16] = 0x00;
	C[2][17] = 0xFF;
	C[2][18] = 0xFF;
	C[2][19] = 0x00;
	C[2][20] = 0xFF;
	C[2][21] = 0x00;
	C[2][22] = 0x00;
	C[2][23] = 0xFF;
	C[2][24] = 0xFF;
	C[2][25] = 0x00;
	C[2][26] = 0x00;
	C[2][27] = 0x00;
	C[2][28] = 0xFF;
	C[2][29] = 0xFF;
	C[2][30] = 0x00;
	C[2][31] = 0xFF;

	byte U[32];
	byte V[32];
	byte W[32];
	byte K[4][32];
	byte tmp[32];

	memcpy(U, H, sizeof U);
	memcpy(V, M, sizeof V);

	for (uint32 i = 0; i < 32; i++)
	W[i] = U[i] ^ V[i];

	P(W, K[0]);

	for (uint32 step = 1; step < 4; step++)
	{
		A(U, tmp); 
		for (uint32 i = 0; i < 32; i++)
		U[i] = tmp[i] ^ C[step][i];
		
		A(V, tmp);
		A(tmp, V);
		for (uint32 i = 0; i < 32; i++)
		W[i] = U[i] ^ V[i];
		P(W, K[step]);
	}

	byte S[32];
	for (uint32 i = 0; i < 32; i += 8)
	gost89(H + i, K[i >> 3], S + i);

	psi(S, 12);
	for (uint32 i = 0; i < 32; i++) S[i] ^= M[i];
	
	psi(S, 1);
	for (uint32 i = 0; i < 32; i++) S[i] ^= H[i];
	
	psi(S, 61);
	memcpy(newH, S, sizeof S);
}


byte* mhash::gost94(ifstream &ifst, ofstream &ofst) 
{
	if (!ifst.is_open())
	{
		return NULL;
	}

	byte *M;
	byte *rM;
	byte block[32];
	byte CHS[32];
	byte L[32];
	byte H[32];
	byte newH[32];

	uint32 RL = 0;
	uint32 pos = 0;
	uint32 posIB = 0;


	ifst.seekg(0, ios::end);
	RL = ifst.tellg();
	ifst.seekg(0, ios::beg);

	M = new byte [RL + 1];
	rM = new byte[32];
	
	memset(M, 0, sizeof (byte) * (RL + 1));
	memset(rM, 0, sizeof (byte) * 32);
	memset(block, 0, sizeof (byte) * 32);

	ifst >> (char *) M;
	RL = strlen((char *) M);

	memset(CHS, 0, sizeof CHS);
	memset(H, 0, sizeof H);

	while ((posIB < RL) || pos) 
	{
		if (posIB < RL)
		{
			block[pos++] = M[posIB++];
		}
		else block[pos++] = 0;
		
		if (pos == 32) 
		{
			pos = 0;
			uint32 c = 0;

			for (uint32 i = 0; i < 32; i++) 
			{
				c += block[i] + CHS[i];
				CHS[i] = c & 0xFF;
				c >>= 8;
			}

			f(H, block, newH); 
			memcpy(H, newH, sizeof newH);
		}
	}

	memset(L, 0, sizeof L);
	uint32 c = RL << 3;
	for (uint32 i = 0; i < 32; i++)
	{
		L[i] = c & 0xFF;
		c >>= 8;
	}

	f(H, L, newH); 
	memcpy(H, newH, sizeof newH);

	f(H, CHS, newH);
	memcpy(rM, newH, sizeof newH);

	if (ofst.is_open())
	{
		for (int i = 0; i < 32; i++)
		ofst << hex << rM[i];
	}	

	return rM;
}
