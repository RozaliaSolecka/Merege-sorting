#include<iostream>
#include"Record.h"
#include<time.h>
using namespace std;

Record::Record() {}
Record::Record(int a0, int a1, int a2, int a3, int a4, int x) {
	this->a0 = a0;
	this->a1 = a1;
	this->a2 = a2;
	this->a3 = a3;
	this->a4 = a4;
	this->x = x;
}
unsigned long long Record::value()
{
	return (a0 + a1 * x + a2 * x * x + a3 * x * x * x + a4 * x * x * x * x);
}

