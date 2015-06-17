#include "mbig.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>
#include <ctime>

using namespace std;

const int bits = 255;

int miller_rabin(mbig m);
int is_prime(mbig n);

mbig prime_gen(int bits, mbig p);
mbig gcd_extended(mbig a, mbig b, mbig n);
mbig gcd(mbig a, mbig b);
mbig prime_search(mbig m);
mbig primitive_root(mbig p);

void TestRSA(char *optarg, mbig p, mbig q);
void TestEl(char *optarg, mbig p);
void TestFFSP(mbig p, mbig q);

int rsa_encryption(ifstream &ifst, ofstream &ofst, mbig p, mbig q);
int rsa_decryption(ifstream &ifst, ofstream &ofst);

int el_encryption(ifstream &ifst, ofstream &ofst, mbig p);
int el_decryption(ifstream &ifst, ofstream &ofst);

int ffsp(mbig p, mbig q);
