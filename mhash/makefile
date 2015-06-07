all: main.cpp proc.cpp md5.cpp sha1.cpp ripemd160.cpp gost94.cpp tests.cpp my_test.h

	cxxtestgen -o tests.h --have-eh --have-std --abort-on-fail my_test.h
	g++ -o mhash -I$CXXTEST main.cpp proc.cpp md5.cpp sha1.cpp ripemd160.cpp gost94.cpp tests.cpp -lcrypto

mhash: main.cpp proc.cpp md5.cpp sha1.cpp ripemd160.cpp gost94.cpp tests.cpp

	g++ -o mhash -I$CXXTEST main.cpp proc.cpp md5.cpp sha1.cpp ripemd160.cpp gost94.cpp tests.cpp -lcrypto

testgen: my_test.h

	cxxtestgen -o tests.h --have-eh --have-std --abort-on-fail my_test.h

clean:
	rm -f mhash
	rm -f tests.h
