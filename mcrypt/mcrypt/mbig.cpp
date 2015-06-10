#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

const int MaxLength = 4096;

class mbig
{
public:
	int a[MaxLength];
	int n;

	mbig msqrt();
	static mbig mpow(mbig a, mbig e, mbig n);

	mbig(int p = 0);
	mbig(char *s);
	mbig(char *s, int offset);

	void print();
	void print(ofstream &ofst);

	int max(int a, int b);
	int cmp(mbig p);

	mbig operator ^ (mbig p);
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

void mbig::print(ofstream &ofst)
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




//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

typedef unsigned long long uint64;


int miller_rabin(mbig m)
{
	if (m == 2 || m == 3) return 1;
	if (m == 0)			  return 0;

	mbig t = m - 1;
	mbig s(0);
	mbig i(0);
	mbig a(0);
	mbig x(0);

	while (t % 2 == 0)
	{
		t = t / 2;
		s = s + 1;
	}

	for (i = 0; i < 10; i = i + 1)
	{
		a = (m > i * 13 - 2) ? (m - i * 13 - 2) : m - i;

		x = mbig::mpow(a, t, m);

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

mbig prime_gen(uint64 bits, mbig p)
{
	mbig b(2);
	b = b ^ bits;

	while (b != 0)
	{
		b = b - 1;

		if (miller_rabin(b) == 1 && b != p) return b;
	}
	return 0;
}

mbig gcd_extended(mbig a, mbig b)
{
//	a * x + b * y = 1
//	m * x + d * e = 1

	mbig mod(0);

	mbig x(0);
	mbig y(0);
	mbig d(1);

	mbig q(0);
	mbig r(0);
	mbig x1(0), x2(0);
	mbig y1(0), y2(0);

	mod = a;

	if (b == 0)
	{
		d = a;
		x = 1;
		y = 0;
		return y;
	}

	x2 = 1;	x1 = 0;
	y2 = 0;	y1 = 1;

	while (b > 0)
	{
		q = a / b;
		r = a - q * b;
		q = mod - q;

		x = x2 + q * x1;
		y = y2 + q * y1;

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
	mbig i(0);

	i = 2;

	while (i != m)
	{
		i = i + 1;
		if (gcd(m, i) == 1) return i;
	}
	return 1;
}

int main()
{
	uint64 bits = 7;

	mbig p(0);
	mbig q(0);

	mbig n(0);
	mbig m(0);
	mbig d(0);
	mbig e(0);


	p = prime_gen(bits, 0);
	q = prime_gen(bits, p);

	n = p * q;

	m = (p - 1) * (q - 1);

	d = prime_search(m);

	e = gcd_extended(m, d);

	p.print(); cout << endl;
	q.print(); cout << endl;
	n.print(); cout << endl;
	m.print(); cout << endl;
	d.print(); cout << endl;
	e.print(); cout << endl;

	//---------------------
	char	*s;
	int		rl;
	int		nl = 0;

	ifstream ifst("in");
	ofstream ofst("out");


	ifst.seekg(0, ios::end);
	rl = ifst.tellg();
	ifst.seekg(0, ios::beg);

	s = new char[rl];
	ifst.getline(s, rl + 1);


	while (rl > 0)
	{
		mbig a(s + nl, 1);
		mbig b(0);

		b = mbig::mpow(a, e, n);
		b.print(ofst);

		ofst << '\0';

		--rl;
		++nl;
	}

	ifst.close();
	ofst.close();

	
	ifst.open("out");
	ofst.open("in2");


	char *s2 = new char[n.n];
	char ch;

	while (1)
	{
		ifst >> s2;
		ifst >> ch;

		if (ifst.eof()) break;

		mbig b(s2, n.n);
		mbig a(0);

		a = mbig::mpow(b, d, n);
		a.print(ofst);
	}
	return 0;
}
