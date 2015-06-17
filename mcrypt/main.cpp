#include "header.h"

int main(int argc, char *argv[])
{
	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},
		{"rsa", 0, NULL, 'r'},
		{"gamal", 0, NULL, 'g'},
		{"ffsp", 0, NULL, 'f'},
		{"test", 1, NULL, 't'},
		{NULL,0,NULL,0},
	};
		
	switch (getopt_long(argc, argv, "ht:", long_options, NULL))
	{
	case 'h':
	{
		cout << " -h,\t--help\t\t\t\thelper" << endl;
		cout << " -t,\t--test\t\t[input file]\ttesting of all crypto-programs" << endl;
		cout << " \t--rsa\t[key]\t[input file]\tRSA" << endl;
		cout << " \t--gamal\t[key]\t[input file]\tEl Gamal" << endl;
		cout << " \t--ffsp\t\t\t\tFeige Fiat Shamir" << endl;
		return 0;	
	}
	case 'r':
	{
		switch (getopt(argc, argv, "e:d:"))
		{
		case 'e':
		{
			ifstream ifst(optarg);
			ofstream ofst("rsa_encrypt");
	
			if (!ifst.is_open()) 
			{
				cout << "error: cannot open input file" << endl; 
				return 0;		
			}
			rsa_encryption(ifst, ofst, 0, 0);
			
			ifst.close();
			ofst.close();
			return 0;
		}
		case 'd':
		{
			ifstream ifst(optarg);
			ofstream ofst("rsa_decrypt");

			if (!ifst.is_open()) 
			{
				cout << "error: cannot open input file" << endl; 
				return 0;		
			}
			rsa_decryption(ifst, ofst);
			
			ifst.close();
			ofst.close();
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

	case 'g':
	{
		switch (getopt(argc, argv, "e:d:"))
		{
		case 'e':
		{
			ifstream ifst(optarg);
			ofstream ofst("el_encrypt");
	
			if (!ifst.is_open()) 
			{
				cout << "error: cannot open input file" << endl; 
				return 0;		
			}
			el_encryption(ifst, ofst, 0);

			ifst.close();
			ofst.close();
			return 0;
		}
		case 'd':
		{
			ifstream ifst(optarg);
			ofstream ofst("el_decrypt");

			if (!ifst.is_open()) 
			{
				cout << "error: cannot open input file" << endl; 
				return 0;		
			}
			el_decryption(ifst, ofst);
			
			ifst.close();
			ofst.close();
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

	case 'f':
	{
		if (ffsp(0, 0) == 0) cout << "result: success" << endl;
		else cout << "result: error" << endl;
		return 0;
	}
	
	case 't':
	{
		clock_t t0 = clock();
		mbig p = prime_gen(bits, 0);
		mbig q = prime_gen(bits, p);	
		clock_t t1 = clock();
		cout << "KeyGeneration\tTime: " << (double) (t1 - t0) / CLOCKS_PER_SEC << endl;
		
		TestRSA(optarg, p, q);
		TestEl(optarg, p);
		TestFFSP(p, q);
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
