#include "mbig.h"

#define delete_zero(a, na) while (na > 1 && a[na - 1] == 0) -- na;

int mbig::cmp(int a[], int na, int b[], int nb)
{
	if (na > nb) return 1;
	if (nb > na) return -1;
	for (int i = na - 1; i >= 0; --i)
	{
		if (a[i] > b[i]) return 1;
		if (a[i] < b[i]) return -1;
	}
	return 0;
}

void mbig::add(int a[], int b[], int c[], int &n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		c[i] += a[i] + b[i];
		c[i + 1] = c[i] / 10;
		c[i] %= 10;
	}
	delete_zero(c, n);
}

void mbig::sub(int a[], int b[], int c[], int &n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		c[i] += a[i] - b[i];
		if (c[i] < 0)
		{
			--c[i + 1];
			c[i] += 10;
		}
	}
	delete_zero(c, n);
}
void mbig::sub2(int a[], int b[], int &n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		a[i] -= b[i];
		if (a[i] < 0)
		{
			--a[i + 1];
			a[i] += 10;
		}
	}
	delete_zero(a, n);
}
void mbig::mul(int a[], int na, int b[], int nb, int c[], int &nc)
{
	int i, j;
	nc = na + nb;
	for (i = 0; i < na; ++i)
	for (j = 0; j < nb; ++j)
		c[i + j] += a[i] * b[j];
	for (i = 0; i < nc; ++i)
	if (c[i] >= 10)
	{
		c[i + 1] += c[i] / 10;
		c[i] %= 10;
	}
	delete_zero(c, nc);
}
void mbig::divmod(int a[], int na, int b[], int nb, int d[], int &nd, int r[], int &nr)
{
	int i, j;
	nd = na;
	nr = 1;
	for (i = na - 1; i >= 0; --i)
	{
		if (nr != 1 || r[0] != 0)
		{
			for (j = nr; j > 0; --j)
				r[j] = r[j - 1];
			++nr;
		}
		r[0] = a[i];

		while (cmp(r, nr, b, nb) >= 0)
		{
			++d[i];
			sub2(r, b, nr);
		}
	}
	delete_zero(d, nd);
	delete_zero(r, nr);
}

// class functions
mbig::mbig(int p)
{
	for (int i = 0; i < MaxLength; ++i)
		a[i] = 0;

	n = 0;
	do
	{
		a[n++] = p % 10;
		p /= 10;
	} while (p);
}
mbig::mbig(char *s)
{
	int i;
	for (i = 0; i < MaxLength; ++i)
		a[i] = 0;
	for (n = 0; s[n] != 0; ++n);
	for (i = 0; i < n; ++i)
		a[i] = s[n - i - 1] - '0';
}
mbig::mbig(char *s, int offset)
{
	int i;
	for (i = 0; i < MaxLength; ++i)
		a[i] = 0;

	for (n = 0; n < offset && s[n] != 0; ++n);
	for (i = 0; i < n; ++i)
		a[i] = s[n - i - 1] - '0';
}

void mbig::print()
{
	for (int i = n - 1; i >= 0; --i)
	printf("%d", a[i]);
}

void mbig::print(std::ofstream &ofst)
{
	int i = n;
	while (i != 0)
	{
		i--;
		ofst << (int) a[i];
	}
}

int mbig::cmp(mbig p)
{
	return cmp(a, n, p.a, p.n);
}
int mbig::max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

mbig mbig::mpow(mbig a, mbig e, mbig n)
{
	mbig r(1);
	while (e.cmp(0) == 1)
	{
		e = e - 1;
		r = r * a;
		r = r % n;
	}
	return r;
}

mbig mbig::msqrt()
{
	mbig l(0);
	mbig r(0);
	mbig res(0);
	mbig m(0);
	mbig t(0);

	r = *this;
	t = *this;

	while (l < r + 1)
	{
		m = (l + r) / 2;
		
		if (m*m < t + 1)
		{
			res = m;
			l = m + 1;
		}
		else r = m - 1;
	}
	return res;
}

int mbig::operator == (mbig p)
{
	mbig s = *this;	
	
	if (s.cmp(p) == 0)
	return 1;
	return 0;
}

int mbig::operator != (mbig p)
{
	mbig s = *this;	
	
	if (s.cmp(p) == 0)
	return 0;
	return 1;
}

int mbig::operator > (mbig p)
{
	mbig s = *this;

	if (s.cmp(p) == 1)
	return 1;
	return 0;
}
int mbig::operator < (mbig p)
{
	mbig s = *this;

	if (s.cmp(p) == -1)
	return 1;
	return 0;
}
mbig mbig::operator ^ (mbig p)
{
	mbig r(1);

	mbig s = *this;
	mbig u = p;

	while (u.cmp(0) == 1)
	{
		u = u - 1;
		r = r * s;
	}
	return r;
}
mbig mbig::operator + (mbig p)
{
	mbig s;
	s.n = max(n, p.n) + 1;
	add(a, p.a, s.a, s.n);
	return s;
}
mbig mbig::operator - (mbig p)
{
	mbig s;
	s.n = max(n, p.n);
	if (cmp(p) >= 0)
		sub(a, p.a, s.a, s.n);
	else
		sub(p.a, a, s.a, s.n);
	return s;
}
mbig mbig::operator * (mbig p)
{
	if (n + p.n < 1000)
	{
		mbig s;
		mul(a, n, p.a, p.n, s.a, s.n);
		return s;
	}
	else
		return karatsuba_mul(p);
}
mbig mbig::operator / (mbig p)
{
	mbig s;
	mbig r;
	divmod(a, n, p.a, p.n, s.a, s.n, r.a, r.n);
	return s;
}
mbig mbig::operator % (mbig p)
{
	mbig s;
	mbig r;
	divmod(a, n, p.a, p.n, s.a, s.n, r.a, r.n);
	return r;
}
mbig mbig::operator << (int k)
{
	mbig s;
	s.n = n + k;
	for (int i = s.n - 1; i >= 0; --i)
		s.a[i] = (i >= k ? a[i - k] : 0);
	return s;
}
mbig mbig::operator >> (int k)
{
	mbig s;
	s.n = n - k;
	for (int i = k; i < n; ++i)
		s.a[i - k] = a[i];
	return s;
}
mbig mbig::last(int k)
{
	mbig s;
	s.n = k;
	for (short i = 0; i < k; ++i)
		s.a[i] = a[i];
	return s;
}
mbig mbig::karatsuba_mul(mbig p)
{
	int k = max(n, p.n) / 2;

	mbig a = (*this).last(k);
	mbig b = (*this) >> k;
	mbig c = p.last(k);
	mbig d = p >> k;

	mbig ac = a * c;
	mbig bd = b * d;
	mbig abcd = (a + b) * (c + d);

	mbig res = ((abcd - ac - bd) << k) + (bd << (k << 1)) + ac;
	return res;
}
