#pragma once
#include"File.h"
#include"Record.h"
#include"globalValues.h"
class WriteBuffer
{
public:
	Record* buffer;
	File* fileToWrite;
	int positionInBuffer;

	WriteBuffer(File* file);
	void save(Record* rekord);  // zapis wygenerowanych lub z klawiatury
	void saveRest();
	bool saveRecord(Record* record);  //zapis podczas sortowania
	void saveRestRecords();
	~WriteBuffer();
};