#include<iostream>
#include<fstream>
#include"File.h"
#include<time.h>
using namespace std;

File::File(const char* name) {
	this->name = name;
	this->position = 0;
	this->size = getSize();
}

int File::getSize()
{
	ifstream is(name, ios::beg | ios::binary);
	is.seekg(0, ios::end);
	return is.tellg();
}