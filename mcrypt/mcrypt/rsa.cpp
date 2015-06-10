#include <iostream>
#include "mbig.h"

using namespace std;
typedef unsigned long long uint64;


mbig prime_gen(uint64 bits)
{
	mbig b(2);
	mbig r(0);
		
	b = b ^ bits;

	while (b.cmp(0) == 1)
	{
		b.print();
		cout << endl;			
		b = b - 1;
	}
	return b;
}


mbig miller_robin(mbig m)
{
	if (m.cmp(1) == 0) return 0;
	if (m.cmp(3) == 0) return 1;	
	if ((m % 2 ) == 0) return 0;
	
	mbig t(0);
	mbig s(0);		
	
	t = m - 1;
	
	while ((t != 0) && ((t % 2) == 0))
	{
		s = s + 1;
		t = t / 2;
	}

	mbig x(0);
	mbig a(0);
	
	mbig r1(2);
	mbig r2(0);
		
	r2 = m - 2;

	for(uint64 i = 0; i < 1000; i++) 
	
	{
		a = r1 + rand() % (r2 - r1);

		x = powm(a, t, m);

		if( (x == 1) || (x == (m - 1)))
		{
			continue;
		}

		mbig j(0);
		while (j != (s - 2))
		{
			j = j + 1;
			
			mbig k(2);
			x = powm(x, k, m);
			
			if(x == 1) return 0;
			if(x == (m - 1)) break;
		}

		if(x == (m - 1)) continue;

		return 0;
       }
       
    return 1;
}



int main()
{
	mbig x(5);
	mbig y(7);


	// 512-bits key;

//	x = prime_gen(9);
	
//	x = miller_robin(38);
	
	
	x.print();


//	if ( x + 2 == y) cout << "sd" << endl;
	return 0;
}
