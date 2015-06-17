#include "header.h"

int miller_rabin(mbig m)
{
	if (m == 2 || m == 3) return 1;
	if (m == 0)			  return 0;

	mbig t = m - 1;
	mbig s(0);
	mbig i;
	mbig a;
	mbig x;

	while (t.a[0] % 2 == 0)
	{
		t = t / 2;
		s = s + 1;
	}

	for (i = 0; i < 10; i = i + 1)
	{
		a = (m > i * 13 - 2) ? (m - i * 13 - 2) : m - i;

		x = mbig::mbpow(a, t, m);

		if (x == 1) return 1;

		i = 0;
		while (i < s - 1)
		{
			i = i + 1;
			x = (x * x) % m;
			if (x == m - 1) return 1;
		}
		return 0;
	}
}

int is_prime(mbig n)
{
	mbig i(0);
	mbig s(0);

	s = n.msqrt();
	for (i = 2; i < s + 1; i = i + 1)
	{
		if (n % i == 0) return 0;
	}
	return 1;
}

mbig prime_gen(int bits, mbig p)
{
	mbig b(2);
	b = b ^ bits;
	
	if (p != 0) b = p - 1;

	while (b != 0)
	{
		b = b - 1;
		if (miller_rabin(b) == 1 && b != p) return b;
	}
	return 0;
}

mbig gcd_extended(mbig a, mbig b, mbig m)
{
	//	a * x + b * y = 1
	//	m * x + d * e = 1

	a = a;
	b = b;
	m = a;

	mbig x(0);
	mbig y(0);
	mbig d(1);

	mbig q(0);
	mbig r(0);
	mbig x1(0), x2(0);
	mbig y1(0), y2(0);

	if (b == 0)
	{
		y = 0;
		return y;
	}

	x2 = 1;	x1 = 0;
	y2 = 0;	y1 = 1;

	while (b > 0)
	{
		q = a / b;
		r = a - q * b;
		q = m - q;

		x = (x2 + q * x1);
		y = (y2 + q * y1);

		a = b;
		b = r;

		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}

	d = a;
	x = x2;
	y = y2;

	return y;
}

mbig gcd(mbig a, mbig b)
{
	if (a < b)	return gcd(b, a);
	if (b == 0) return a;
	
	mbig r(1);

	while (r != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

mbig prime_search(mbig m)
{
	mbig i(2);
	
	while (i != m)
	{
		i = i + 1;
		if (gcd(m, i) == 1) return i;
	}
	return 1;
}

mbig primitive_root(mbig p)
{
	mbig a(2);
	mbig x(0);

	while (x < p)
	{
		x = mbig::mbpow(a, p - 1, p);
		if (x == 1) return a;
		a = a + 1;
	}
}
