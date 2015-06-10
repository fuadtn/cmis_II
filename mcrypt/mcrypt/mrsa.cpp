#include "mbig.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>

using namespace std;

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

mbig prime_gen(int bits, mbig p)
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


int encryption(ifstream &ifst, ofstream &ofst)
{
	int bits = 7;

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

	ofstream kfst("rsa_kfile");
	ofstream nfst("rsa_mfile");
	
	d.print(kfst);
	n.print(nfst);
	
	kfst.close();
	nfst.close();
	
	//---------------------
	char *s;
	int	 rl, nl = 0;

	ifst.seekg(0, ios::end);
	rl = ifst.tellg();
	ifst.seekg(0, ios::beg);

	s = new char[rl];
	ifst.getline(s, rl + 1);

	while (rl > 1)
	{
		mbig a(s + nl, 1);
		mbig b(0);

		b = mbig::mpow(a, e, n);
		b.print(ofst);

		ofst << ' ';

		--rl;
		++nl;
	}
	return 0;
}


int decryption(ifstream &ifst, ofstream &ofst)
{
	ifstream kfst("rsa_kfile");
	ifstream nfst("rsa_mfile");

	if(!ifst.is_open() || !ofst.is_open())
	{
		cout << "error: can't read input file" << endl;
		return 0;
	}

	if(!kfst.is_open() || !nfst.is_open())
	{
		cout << "error: can't read file" << endl;
		return 0;
	}

	char z[MaxLength];
	kfst >> z; mbig d(z);
	nfst >> z; mbig n(z);

	kfst.close();
	nfst.close();

	char *s2 = new char[n.n];
	char ch;
	
	d.print(); cout << endl;
	n.print(); cout << endl;
	cout << " " << n.n << endl;		

	while (1)
	{		
		ifst.getline(s2, 1024, ' ');
		if (ifst.eof()) break;

		mbig b(s2, n.n);
		mbig a(0);

		a = mbig::mpow(b, d, n);
		a.print(ofst);
	}
	return 0;
}


int main(int argc, char *argv[])
{
	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},
		{"rsa", 0, NULL, 'r'},
		{"test", 1, NULL, 't'},
		{NULL,0,NULL,0},
	};
		
	switch (getopt_long(argc, argv, "ht", long_options, NULL))
	{
	case 'h':
	{
		cout << " -h, --help	\t\t helper" << endl;
		cout << " -t, --test \t\t\t testing of all hash programs" << endl;
		cout << " --rsa [key] \t[input file] \t RSA" << endl; 
		return 0;	
	}
	case 'r':
	{
		switch (getopt(argc, argv, "e:d:"))
		{
		case 'e':
		{
			ifstream ifst(optarg);
			ofstream ofst("rsa_eofile");
	
			encryption(ifst, ofst);
			
			ifst.close();
			ofst.close();	
			break;
		}
		case 'd':
		{
			ifstream ifst("rsa_eofile");
			ofstream ofst("rsa_dofile");

			decryption(ifst, ofst);
			
			ifst.close();
			ofst.close();
			break;	
		}
		default:		{
			cout << "error: too few arguments" << endl; 
			return 0;
		}
		}
		return 0;
	}

	case 't':
	{
		return 0;
	}         
	default:
	{
		cout << "error: too few arguments" << endl; 
		return 0;
	}
	}
	return 0;
}
