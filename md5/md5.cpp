#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int T[64];
int X[16];

int FunctionF(int x, int y, int z)
{
	return ((x & y) | (~x &z));
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
	return (b + ((a + FunctionF(b,c,d) + X[k] + T[i]) << s));
}
int Round2(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + ((a + FunctionG(b,c,d) + X[k] + T[i]) << s));
}
int Round3(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + ((a + FunctionH(b,c,d) + X[k] + T[i]) << s));
}
int Round4(int a, int b, int c, int d, int k, int s, int i)
{
	return (b + ((a + FunctionI(b,c,d) + X[k] + T[i]) << s));
}

int main(int argc, char *argv[])
{		
	char *M;	
	int AA, BB, CC, DD;
	unsigned long int L, LTMP;

// step 3
	int A = 0x67452301;
	int B = 0xefcdab89;
	int C = 0x98badcfe;
	int D = 0x10325476;
	
// open in file
	FILE *File;
	File = fopen(argv[1], "rb");
	if (File == NULL)
	{
		cout << "error: can't open in file" << endl;
		return 0;
	}
	
	fseek(File, 0, SEEK_END);
	L = ftell(File);
	fseek(File, 0, SEEK_SET);
	M = new char [L + 64];
	for (int i = 0; i < L; i++)
	fread(&M[i], sizeof(char), 1, File);
	fclose(File);

// step 1	
	M[L] = 0x80;
	L++;
	while (L%64 != 56)
	L++;
		
// step 2
	for (int i = strlen(M) + 1; i < L; i++)
	M[i] = 0;
	
	LTMP = L;
	M[L] = LTMP;
	for (int i = L + 1; i < L + 8; i++)
	M[i] = LTMP >> 8;
	
// step 4	
	for (int i = 0; i < 64; i++)
	T[i] = 4294967296 * abs(sin(i));
	
	for (int i = 330; i < L/16; i++)
	{
		for( int j = 0; j < 16; j++)
		X[j] = M[i*16 + j];
		
		AA = A;
		BB = B;
		CC = C;
		DD = D;
				
		A = Round1(A,B,C,D,0,7,1);
		D = Round1(D,A,B,C,1,12,2);
		C = Round1(C,D,A,B,2,17,3);
		B = Round1(B,C,D,A,3,22,4);
		A = Round1(A,B,C,D,4,7,5);
		D = Round1(D,A,B,C,5,12,6);
		C = Round1(C,D,A,B,6,17,7);
		B = Round1(B,C,D,A,7,22,8);
		A = Round1(A,B,C,D,8,7,9);
		D = Round1(D,A,B,C,9,12,10);
		C = Round1(C,D,A,B,10,17,11);
		B = Round1(B,C,D,A,11,22,12);
		A = Round1(A,B,C,D,12,7,13);
		D = Round1(D,A,B,C,13,12,14);	
		C = Round1(C,D,A,B,14,17,15);
		B = Round1(B,C,D,A,15,22,16);

		A = Round2(A,B,C,D,1,5,17);
		D = Round2(D,A,B,C,6,9,18);
		C = Round2(C,D,A,B,11,14,19);
		B = Round2(B,C,D,A,0,20,20);
		A = Round2(A,B,C,D,5,5,21);
		D = Round2(D,A,B,C,10,9,22);
		C = Round2(C,D,A,B,15,14,23);
		B = Round2(B,C,D,A,4,20,24);
		A = Round2(A,B,C,D,9,5,25);
		D = Round2(D,A,B,C,14,9,26);
		C = Round2(C,D,A,B,3,14,27);
		B = Round2(B,C,D,A,8,20,28);
		A = Round2(A,B,C,D,13,5,29);
		D = Round2(D,A,B,C,2,9,30);	
		C = Round2(C,D,A,B,7,14,31);
		B = Round2(B,C,D,A,12,20,32);		

		A = Round3(A,B,C,D,5,4,33);
		D = Round3(D,A,B,C,8,11,34);
		C = Round3(C,D,A,B,11,16,35);
		B = Round3(B,C,D,A,14,23,36);
		A = Round3(A,B,C,D,1,4,37);
		D = Round3(D,A,B,C,4,11,38);
		C = Round3(C,D,A,B,7,16,39);
		B = Round3(B,C,D,A,10,23,40);
		A = Round3(A,B,C,D,13,4,41);
		D = Round3(D,A,B,C,0,11,42);
		C = Round3(C,D,A,B,3,16,43);
		B = Round3(B,C,D,A,6,23,44);
		A = Round3(A,B,C,D,9,4,45);
		D = Round3(D,A,B,C,12,11,46);	
		C = Round3(C,D,A,B,15,16,47);
		B = Round3(B,C,D,A,2,23,48);
		
		A = Round4(A,B,C,D,0,6,49);
		D = Round4(D,A,B,C,7,10,50);
		C = Round4(C,D,A,B,14,15,51);
		B = Round4(B,C,D,A,5,21,52);
		A = Round4(A,B,C,D,12,6,53);
		D = Round4(D,A,B,C,3,10,54);
		C = Round4(C,D,A,B,10,15,55);
		B = Round4(B,C,D,A,1,21,56);
		A = Round4(A,B,C,D,8,6,57);
		D = Round4(D,A,B,C,15,10,58);
		C = Round4(C,D,A,B,6,15,59);
		B = Round4(B,C,D,A,13,21,60);
		A = Round4(A,B,C,D,4,6,61);
		D = Round4(D,A,B,C,11,10,62);	
		C = Round4(C,D,A,B,2,15,63);
		B = Round4(B,C,D,A,9,21,64);
		
		A += AA;
		B += BB;
		C += CC;
		D += DD;
	}

// open out file	
	File = fopen(argv[2], "w");
	if (File == NULL)
	{
		cout << "error: can't open out file" << endl;
		return 0;
	}	
	
	fwrite(&A, sizeof(int), 1, File);
	fwrite(&B, sizeof(int), 1, File);
	fwrite(&C, sizeof(int), 1, File);
	fwrite(&D, sizeof(int), 1, File);
	fclose(File);	
	
	cout << "hash.md5 = " << hex << D << C << B << A << endl;
	return 0;
}
