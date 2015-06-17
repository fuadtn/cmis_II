#include "header.h"

void TestRSA(char *optarg, mbig p, mbig q)
{
	clock_t t0 = clock();	
	
	ifstream ifst(optarg);
	ofstream ofst("rsa_encrypt");
	if (!ifst.is_open()) 
	{
		cout << "Test 1 | error: cannot open input file" << endl; 
		return;
	}
	rsa_encryption(ifst, ofst, p, q);	
	ifst.close();
	ofst.close();
	
	ifst.open("rsa_encrypt");
	ofst.open("rsa_decrypt");
	
	rsa_decryption(ifst, ofst);
	
	ifst.close();
	ofst.close();		
	
	char s1[2*MaxLength];
	char s2[2*MaxLength];
	
	ifst.open(optarg);
	ifst >> s1;
	ifst.close();
	
	ifst.open("rsa_decrypt");
	ifst >> s2;
	ifst.close();
	
	clock_t t1 = clock();
	
	if (strcmp(s1, s2) == 0)
	cout << "Test 1...OK!";
	else cout << "Test 1...ERROR!";
	cout << "\tTime: " << (double) (t1 - t0) / CLOCKS_PER_SEC << endl;
}

void TestEl(char *optarg, mbig p)
{
	clock_t t0 = clock();	

	ifstream ifst(optarg);
	ofstream ofst("el_encrypt");

	if (!ifst.is_open()) 
	{
		cout << "Test 2 | error: cannot open input file" << endl; 
		return;		
	}
	el_encryption(ifst, ofst, p);

	ifst.close();
	ofst.close();

	ifst.open("el_encrypt");
	ofst.open("el_decrypt");

	el_decryption(ifst, ofst);
			
	ifst.close();
	ofst.close();
				
	char s1[2*MaxLength];
	char s2[2*MaxLength];
	
	ifst.open(optarg);
	ifst >> s1;
	ifst.close();
	
	ifst.open("el_decrypt");
	ifst >> s2;
	ifst.close();
	
	clock_t t1 = clock();
		
	if (strcmp(s1, s2) == 0)
	cout << "Test 2...OK!";
	else cout << "Test 2...ERROR!";
	cout << "\tTime: " << (double) (t1 - t0) / CLOCKS_PER_SEC << endl;
}

void TestFFSP(mbig p, mbig q)
{
	clock_t t0 = clock();
	int result = ffsp(p, q);
	clock_t t1 = clock();
	
	if (result == 0) cout << "Test 3...OK!";
	else cout << "Test 3...ERROR!";

	cout << "\tTime: " << (double) (t1 - t0) / CLOCKS_PER_SEC << endl;	
}
