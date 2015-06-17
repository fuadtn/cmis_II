#include "header.h"

int el_encryption(ifstream &ifst, ofstream &ofst, mbig p)
{
	mbig g(0);
	mbig x(0);
	mbig y(0);
	mbig k(0);
	mbig a(0);
	mbig b(0);
	mbig M(ifst);

	// init
	if (p == 0)
	p = prime_gen(bits, 0);
	g = primitive_root(p);

	x.random(bits);
	x = ((x % p) > 1) ? (x % p) : 2;

	y = mbig::mbpow(g, x, p);

	// encryp
	x.random(bits);
	x = ((x % (p - 1)) > 1) ? (x % (p - 1)) : 2;

	a = mbig::mbpow(g, k, p);
	b = mbig::mbpow(y, k, p); b = b * M % p;

	p.print(ofst); ofst << endl;
	x.print(ofst); ofst << endl;
	a.print(ofst); ofst << endl;
	b.print(ofst);

	ifst.close();
	ofst.close();

	return 0;
}


int el_decryption(ifstream &ifst, ofstream &ofst)
{
	mbig D(0);

	mbig p(ifst);
	mbig x(ifst);
	mbig a(ifst);
	mbig b(ifst);
	
	D = mbig::mbpow(a, p - 1 - x, p); D = D * b % p;
	D.print(ofst);
	return 0;
}
