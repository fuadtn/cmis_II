#include "header.h"

int ffsp(mbig p, mbig q)
{
	int t = 2;
	int e = 0;

	mbig n(0);
	mbig s(0);
	mbig v(0);
	mbig r(0);
	mbig x(0);
	mbig y(0);

	// Center T
	if (p == 0 || q == 0)
	{
		p = prime_gen(bits, 0);
		q = prime_gen(bits, p);
	}
	
	n = p * q;
	s = prime_search(n);
	v = mbig::mbpow(s, 2, n);

	
	// Center A
	r.random(bits);
	r = ((r % n) > 1) ? (r % n) : 1;
	x = mbig::mbpow(r, 2, n);

	//e = 0
	y = r;

	if (((y * y) % n) != (x % n))
	{
		return -1;
	}

	// e = 1
	++e;
	y = r * s;

	if (((y * y) % n) != ((x * v) % n))
	{
		return -1;
	}
	return 0;
}
