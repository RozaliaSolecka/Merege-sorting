#pragma once
#include"File.h"
#include"Record.h"
#include"globalValues.h"
class ReadBuffer
{
public:
	Record* buffer;
	char* binaryBuffer;
	File* fileToRead;
	int sizeOfBuffer;
	bool endOfFile;
	int positionToReturn;
	bool empty;
	
	ReadBuffer(File* file);
	bool getRecord();
	Record* giveRecord();
	~ReadBuffer();
};