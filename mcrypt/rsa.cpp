#include "header.h"

int rsa_encryption(ifstream &ifst, ofstream &ofst, mbig p, mbig q)
{
	mbig n(0);
	mbig m(0);
	mbig d(0);
	mbig e(0);
	
	mbig b(0);
	mbig a(ifst);
	
	if( p == 0 || q == 0)
	{
		p = prime_gen(bits, 0);
		q = prime_gen(bits, p);
	}
	
	n = p * q;

	m = (p - 1) * (q - 1);

	d = prime_search(m);

	e = gcd_extended(m, d, n);
	
	b = mbig::mbpow(a, e, n);
	
	d.print(ofst); ofst << endl;	// key
	n.print(ofst); ofst << endl;	// mod
	b.print(ofst);					// mean
	
	return 0;
}

int rsa_decryption(ifstream &ifst, ofstream &ofst)
{	
	mbig d(ifst);
	mbig n(ifst);
	mbig b(ifst);
	mbig a(0);
	
	a = mbig::mbpow(b, d, n);
	
	a.print(ofst);
	return 0;
}
