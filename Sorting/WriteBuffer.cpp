#include<iostream>
#include<time.h>
#include<fstream>
#include"WriteBuffer.h"
#include"Record.h"
#include"File.h"
#include"globalValues.h"
using namespace std;

WriteBuffer::WriteBuffer(File* file) {
	this->fileToWrite = file;
	this->buffer = new Record[BUFFER_SIZE];
	this->positionInBuffer = 0;
}

void WriteBuffer::save(Record* record)
{
	if (positionInBuffer < BUFFER_SIZE )
	{
		buffer[positionInBuffer] = *record;
		positionInBuffer++;
	}
	else 
	{
		ofstream os(fileToWrite->name, ios::out | ios::app | ios::binary);
		os.write(reinterpret_cast<const char*>(buffer), sizeof(Record)*BUFFER_SIZE);
		
		os.close();
		positionInBuffer = 0;
		buffer[positionInBuffer] = *record;
		positionInBuffer++;
	}
	
}
void WriteBuffer::saveRest()
{
	if (positionInBuffer > 0)
	{
		ofstream os(fileToWrite->name, ios::out | ios::app | ios::binary);
		os.write(reinterpret_cast<const char*>(buffer), sizeof(Record) * positionInBuffer);
		
		os.close();
	}
}

bool WriteBuffer::saveRecord(Record* record)
{
	if (positionInBuffer == BUFFER_SIZE)
	{
		ofstream os(fileToWrite->name, ios::out | ios::app | ios::binary);
		numberOfWrites++;
		os.write(reinterpret_cast<const char*>(buffer), sizeof(Record) * BUFFER_SIZE);
		os.close();
		positionInBuffer = 0;
	}
	if (record == NULL)
	{
		return false;
	}
		
	buffer[positionInBuffer] = *record;
	positionInBuffer++;
	return true;
	
}
void WriteBuffer::saveRestRecords()
{
	if (positionInBuffer > 0)
	{
		ofstream os(fileToWrite->name, ios::out | ios::app | ios::binary);
		numberOfWrites++;
		os.write(reinterpret_cast<const char*>(buffer), sizeof(Record) * positionInBuffer);
		
		os.close();
	}
}

WriteBuffer::~WriteBuffer()
{
	delete[] buffer;
}
