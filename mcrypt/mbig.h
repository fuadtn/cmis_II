#include <cstdio>
#include <fstream>
#include <ctime>
#include <string.h>
#include <stdlib.h>

const int MaxLength = 3000;

class mbig
{
public:
	int a[MaxLength];
	int n;

	void random(int bits);

	mbig msqrt();
	static mbig mpow(mbig a, mbig e, mbig n);
	static mbig mbpow(mbig a, mbig e, mbig m);

	mbig(int p = 0);
	mbig(std::ifstream &ifst);
	mbig(char *s);
	mbig(char *s, int offset);

	void print();
	void print(std::ofstream &ofst);

	int max(int a, int b);
	int cmp(mbig p);

	mbig operator ^ (mbig n);
	mbig operator + (mbig p);
	mbig operator - (mbig p);
	mbig operator * (mbig p);
	mbig operator / (mbig p);
	mbig operator % (mbig p);
	int operator == (mbig p);
	int operator != (mbig p);
	int operator >  (mbig p);
	int operator <  (mbig p);
	mbig operator << (int k);
	mbig operator >> (int k);
	mbig last(int k);

	mbig karatsuba_mul(mbig p);

	int cmp(int a[], int na, int b[], int nb);
	void add(int a[], int b[], int c[], int &n);
	void sub(int a[], int b[], int c[], int &n);
	void sub2(int a[], int b[], int &n);
	void mul(int a[], int na, int b[], int nb, int c[], int &nc);
	void divmod(int a[], int na, int b[], int nb, int d[], int &nd, int r[], int &nr);
};

