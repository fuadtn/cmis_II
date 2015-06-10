lib:
	g++ -fPIC -c  -o mbig.o mbig.c
	g++ -shared -o libmbig.so mbig.o
	rm -f mbig.o
	
cpl:
	export LD_LIBRARY_PATH=$PWD
	g++ -o rsa rsa.cpp -L. -lmbig
