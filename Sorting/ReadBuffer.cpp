#include<iostream>
#include<time.h>
#include<fstream>
#include"ReadBuffer.h"
#include"Record.h"
#include"File.h"
#include"globalValues.h"

using namespace std;

ReadBuffer::ReadBuffer(File* file) {
	this->fileToRead = file;
	this->buffer = new Record[BUFFER_SIZE];
	this->binaryBuffer = new char[BUFFER_SIZE * sizeof(Record)];
	this->sizeOfBuffer = BUFFER_SIZE;
	this->endOfFile = false;
	this->positionToReturn=0;
	this->empty=true;
}

bool ReadBuffer::getRecord() {

	ifstream is(fileToRead->name, ios::beg | ios::binary);

	is.seekg(fileToRead->position, ios::beg);

	if (fileToRead->size - fileToRead->position >= sizeOfBuffer*sizeof(Record))
	{
		is.read(reinterpret_cast<char*>(binaryBuffer), sizeof(Record) * BUFFER_SIZE);
		fileToRead->position = is.tellg();

		int j = 0;
		for (int i = 0; i < sizeOfBuffer * sizeof(Record); i += sizeof(Record))
		{
			buffer[j].a0 = binaryBuffer[i];
			buffer[j].a1 = binaryBuffer[i + 4];
			buffer[j].a2 = binaryBuffer[i + 8];
			buffer[j].a3 = binaryBuffer[i + 12];
			buffer[j].a4 = binaryBuffer[i + 16];
			buffer[j].x = binaryBuffer[i + 20];
			
			cout << buffer[j].a0 << SEPARATOR << buffer[j].a1 << SEPARATOR << buffer[j].a2 << SEPARATOR << buffer[j].a3 << SEPARATOR << buffer[j].a4 << SEPARATOR << buffer[j].x << SEPARATOR << buffer[j].value() << endl;
			j++;
		}
		is.close();
	}
	else
	{
		sizeOfBuffer = (fileToRead->size - fileToRead->position) / sizeof(Record);
		if (sizeOfBuffer == 0)
		{
			return false;
		}
		is.read(reinterpret_cast<char*>(binaryBuffer), sizeof(Record) * sizeOfBuffer);
		fileToRead->position = is.tellg();

		int j = 0;
		for (int i = 0; i < sizeOfBuffer * sizeof(Record); i += sizeof(Record))
		{
			buffer[j].a0 = binaryBuffer[i];
			buffer[j].a1 = binaryBuffer[i + 4];
			buffer[j].a2 = binaryBuffer[i + 8];
			buffer[j].a3 = binaryBuffer[i + 12];
			buffer[j].a4 = binaryBuffer[i + 16];
			buffer[j].x = binaryBuffer[i + 20];

			cout << buffer[j].a0 << SEPARATOR << buffer[j].a1 << SEPARATOR << buffer[j].a2 << SEPARATOR << buffer[j].a3 << SEPARATOR << buffer[j].a4 << SEPARATOR << buffer[j].x << SEPARATOR << buffer[j].value() << endl;
			j++;
		}
		is.close();
		return false;

	}
	return true;
}

Record* ReadBuffer::giveRecord()
{	
	Record* record;
	ifstream is(fileToRead->name, ios::beg | ios::binary);

	is.seekg(fileToRead->position, ios::beg);

	if (fileToRead->size - fileToRead->position >= sizeOfBuffer * sizeof(Record) && !endOfFile && empty)
	{
		is.read(reinterpret_cast<char*>(binaryBuffer), sizeof(Record) * BUFFER_SIZE);
		fileToRead->position = is.tellg();

		numberOfReads++;
		empty = false;
		positionToReturn = 0;

		int j = 0;
		for (int i = 0; i < sizeOfBuffer * sizeof(Record); i += sizeof(Record))
		{
			buffer[j].a0 = binaryBuffer[i];
			buffer[j].a1 = binaryBuffer[i + 4];
			buffer[j].a2 = binaryBuffer[i + 8];
			buffer[j].a3 = binaryBuffer[i + 12];
			buffer[j].a4 = binaryBuffer[i + 16];
			buffer[j].x = binaryBuffer[i + 20];
			j++;
		}
		is.close();
	}
	else if(fileToRead->size - fileToRead->position < sizeOfBuffer * sizeof(Record) && !endOfFile && empty)
	{
		sizeOfBuffer = (fileToRead->size - fileToRead->position) / sizeof(Record);

		if (sizeOfBuffer == 0)
		{
			return NULL;
		}

		is.read(reinterpret_cast<char*>(binaryBuffer), sizeof(Record) * sizeOfBuffer);
		fileToRead->position = is.tellg();

		endOfFile = true;
		numberOfReads++;
		empty = false;
		positionToReturn = 0;

		int j = 0;
		for (int i = 0; i < sizeOfBuffer * sizeof(Record); i += sizeof(Record))
		{
			buffer[j].a0 = binaryBuffer[i];
			buffer[j].a1 = binaryBuffer[i + 4];
			buffer[j].a2 = binaryBuffer[i + 8];
			buffer[j].a3 = binaryBuffer[i + 12];
			buffer[j].a4 = binaryBuffer[i + 16];
			buffer[j].x = binaryBuffer[i + 20];

			j++;
		}
		is.close();
	}
	
	if (endOfFile && empty)
	{
		return NULL;
	}
	
	if (positionToReturn == sizeOfBuffer-1)
	{
		empty = true;
	}

	record = &buffer[positionToReturn];
	positionToReturn++;
	
	return record;
	
}
ReadBuffer::~ReadBuffer()
{
	delete[] buffer;
	delete[] binaryBuffer;
}


