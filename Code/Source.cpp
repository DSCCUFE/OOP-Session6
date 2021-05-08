#include<iostream>
#include"BigInteger.h"
using namespace std;

int main() {
	BigInteger obj("234568565454564383423912354");
	BigInteger obj2("100");

	BigInteger b = obj - obj2;
	cout <<b<< endl;
	return 0;
}