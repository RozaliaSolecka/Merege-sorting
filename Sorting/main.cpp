#include<iostream>
#include<time.h>
#include<fstream>
#include"Record.h"
#include"File.h"
#include"WriteBuffer.h"
#include"ReadBuffer.h"
#include"globalValues.h"
using namespace std;


void randomRecordGeneration(const char* fileName)
{
	srand(time(NULL));

	File* file = new File(fileName);
	WriteBuffer* writeBuffer = new WriteBuffer(file);
	Record* record = NULL;
	int numberOfRecords;
	int a0, a1, a2, a3, a4, x;

	cout << "Enter the number of records:" << endl;
	cin >> numberOfRecords;

	for (int i = 0; i < numberOfRecords; i++)
	{
		a0 = rand() % MODULO;
		a1 = rand() % MODULO;
		a2 = rand() % MODULO;
		a3 = rand() % MODULO;
		a4 = rand() % MODULO;
		x = rand() % MODULO;
		record = new Record(a0, a1, a2, a3, a4, x);
		writeBuffer->save(record);
		delete record;
	}
	writeBuffer->saveRest();
	delete writeBuffer;
	delete file;

}
void enterRecordsFromKeyboard(const char* fileName)
{
	File* file = new File(fileName);
	WriteBuffer* writeBuffer = new WriteBuffer(file);
	Record* record = NULL;
	int numberOfRecords;
	int a0, a1, a2, a3, a4, x;

	cout << "Enter the number of records:" << endl;
	cin >> numberOfRecords;

	cout << "Enter records (a0 a1 a2 a3 a4 x)" << endl;

	for (int i = 0; i < numberOfRecords; i++)
	{
		cin >> a0;
		cin >> a1;
		cin >> a2;
		cin >> a3;
		cin >> a4;
		cin >> x;
		record = new Record(a0, a1, a2, a3, a4, x);
		writeBuffer->save(record);
		delete record;
	}
	writeBuffer->saveRest();
	delete writeBuffer;
	delete file;
}
void loadRecordsFromBinFile(char* inputFileName)
{
		char name[20];
		cout << "Enter the name of file" << endl;
		cin >> name;
		int size = sizeof(inputFileName) > sizeof(name) ? sizeof(inputFileName) : sizeof(name);
		for (int i = 0; i < size; i++)
		{
			inputFileName[i] = name[i];
		}
}
void loadRecordsFromTxtFile(char* inputFileName)
{
	File* file = new File(inputFileName);
	WriteBuffer* writeBuffer = new WriteBuffer(file);
	Record* record = NULL;
	int a0, a1, a2, a3, a4, x;

	char name[20];
	cout << "Enter the name of file" << endl;
	cin >> name;

	ifstream source(name, ios::in);

	while (source.eof() != true)
	{
		source >> a0;
		source >> a1;
		source >> a2;
		source >> a3;
		source >> a4;
		source >> x;

		record = new Record(a0, a1, a2, a3, a4, x);
		writeBuffer->save(record);
		delete record;
	}
	writeBuffer->saveRest();
	delete writeBuffer;
	delete file;
}

void showFileContent(const char* inputFileName)
{
	File* file = new File(inputFileName);
	ReadBuffer* readBuffer = new ReadBuffer(file);

	while (readBuffer->getRecord());
	delete file;
	delete readBuffer;
}

void distribution1(const char* inputFileName, const char* name1, const char* name2)
{
	File* input = new File(inputFileName);
	File* file1 = new File(name1);
	File* file2 = new File(name2);

	ReadBuffer* readTape = new ReadBuffer(input);  // taœma do odczytu
	WriteBuffer* writeTape1 = new WriteBuffer(file1);    //taœma1 do zapisu
	WriteBuffer* writeTape2 = new WriteBuffer(file2);   //taœma2 do zapisu
	WriteBuffer* writeTape = writeTape1;                    //taœma
	Record* record = NULL;
	unsigned long long previous = 0;

	while (true)
	{
		record = readTape->giveRecord();
		if (record == NULL)
		{
			break;
		}
		if (previous > record->value())
		{
			writeTape == writeTape1 ? writeTape = writeTape2 : writeTape = writeTape1;
			
		}
		writeTape->saveRecord(record);
		previous = record->value();
	}
	writeTape1->saveRestRecords();
	writeTape2->saveRestRecords();
	delete input;
	delete file1;
	delete file2;
	delete readTape;
	delete writeTape1;
	delete writeTape2;
}

bool merge(const char* name1, const char* name2, const char* name3, const char* name4)
{
	File* file1 = new File(name1);
	File* file2 = new File(name2);
	File* file3 = new File(name3);
	File* file4 = new File(name4);

	ReadBuffer* readTape1 = new ReadBuffer(file1);    //taœma1 do odczytu
	ReadBuffer* readTape2 = new ReadBuffer(file2);   //taœma2 do odczytu

	WriteBuffer* writeTape1 = new WriteBuffer(file3);    //taœma1 do zapisu
	WriteBuffer* writeTape2 = new WriteBuffer(file4);   //taœma2 do zapisu
	WriteBuffer* writeTape = writeTape1;                    //taœma do zapisu

	Record* record1;
	Record* record2;

	unsigned long long previous1 = 0;
	unsigned long long previous2 = 0;
	
	record2 = readTape2->giveRecord();

	if (record2 == NULL)
	{
		return true;
	}
	record1 = readTape1->giveRecord();

	while (true)
	{
		if (record1 != NULL && record2 != NULL)  //taœmy nie sa puste
		{
			if (record1->value() < previous1) // koniec serii w taœmie 1
			{
				while (record2 != NULL && record2->value() >= previous2)  //przepisywanie reszty seri w taœmie 2
				{
					writeTape->saveRecord(record2);
					previous2 = record2->value();
					record2 = readTape2->giveRecord();
				}
			writeTape == writeTape1 ? writeTape = writeTape2 : writeTape = writeTape1;
			previous1 = 0;
			previous2 = 0;
			}
			else if (record2->value() < previous2) // koniec serii w taœmie 2
			{
				while (record1 != NULL && record1->value() >= previous1)  //przepisywanie reszty seri w taœmie 1
				{
					writeTape->saveRecord(record1);
					previous1 = record1->value();
					record1 = readTape1->giveRecord();
				}
				writeTape == writeTape1 ? writeTape = writeTape2 : writeTape = writeTape1;
				previous1 = 0;
				previous2 = 0;
			}
			else  // seria w tasmie 1 i 2 sie nie skonczyla
			{
				if (record1->value() < record2->value())
				{
					writeTape->saveRecord(record1);
					previous1 = record1->value();
					record1 = readTape1->giveRecord();
				}
				else
				{
					writeTape->saveRecord(record2);
					previous2 = record2->value();
					record2 = readTape2->giveRecord();
				}
			}
		}
		else if (record1 == NULL && record2 != NULL) //koniec tasmy 1, ale nie koniec tasmy 2
		{
			while (record2 != NULL)
			{
				writeTape->saveRecord(record2);
				record2 = readTape2->giveRecord();
			}
			break;
		}
		else if (record1 != NULL && record2 == NULL) // koniec tasmy 2, ale nie koniec tasmy1
		{
			while (record1 != NULL && record1->value() >= previous1)
			{
				writeTape->saveRecord(record1);
				previous1 = record1->value();
				record1 = readTape1->giveRecord();
			}
			writeTape == writeTape1 ? writeTape = writeTape2 : writeTape = writeTape1;
			previous1 = 0;
			if (record1 == NULL)
			{
				break;
			}
			
		}
		
	}
	writeTape1->saveRestRecords();
	writeTape2->saveRestRecords();
	delete file1, file2, file3, file4, readTape1, readTape2, writeTape1, writeTape2;

	return false;
}
void clearFile(const char* fileName)
{
	ofstream ofs;
	ofs.open(fileName, ios::out | ios::trunc);
	ofs.close();
}
int main()
{
	int choice;
	char yesOrNo;
	bool displayAfterEachPhase = false;
	bool sorted = false;
	bool firstDistribution = true;
	bool swap = false;
	char inputFileName[20]="input.bin";
	char file1[20] = "file1.bin";
	char file2[20] = "file2.bin";
	char file3[20] = "file3.bin";
	char file4[20] = "file4.bin";
	
	cout << "Rozalia Solecka 175735 - sorting" << endl;
	cout << "Choose number and generate records" << endl;
	cout << "1. Random record generation" << endl;
	cout << "2. Enter your records form keyboard" << endl;
	cout << "3. Load records from .bin file" << endl;
	cout << "4. Load records from .txt file" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
		randomRecordGeneration(inputFileName);
		cout << "Records are saved successfully to " << inputFileName << endl;
		break;
	case 2:
		enterRecordsFromKeyboard(inputFileName);
		cout << "Records are saved successfully to " << inputFileName << endl;
		break;
	case 3:
		loadRecordsFromBinFile(inputFileName);
		cout << "Records are saved successfully to " << inputFileName << endl;
		break;
	case 4:
		loadRecordsFromTxtFile(inputFileName);
		cout << "Records are saved successfully to " << inputFileName << endl;
		break;
	}
	cout << "Type 'y' if you want to display the file after each sorting phase or 'n' if youd don't want to " << endl;
	cin >> yesOrNo;
	if (yesOrNo == 'y') { displayAfterEachPhase = true; }



	cout << "File before sorting:" << endl;
	cout << "a0 a1 a2 a3 a4 x" << endl;
	showFileContent(inputFileName);
	
	while (!sorted)
	{
		if (firstDistribution)
		{
			clearFile(file1);
			clearFile(file2);
			distribution1(inputFileName, file1, file2);
			firstDistribution = false;

			if (displayAfterEachPhase)
			{
				cout << "Files after distribution:" << endl;
				cout << "File1:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file1);
				cout << "File2:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file2);
			}
		}
		if (swap == false)
		{
			clearFile(file3);
			clearFile(file4);
			sorted = merge(file1, file2, file3, file4);
			if (sorted) { break; }
			numberOfPhases++;
			swap = true;
			if (displayAfterEachPhase)
			{
				cout << "File3:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file3);
				cout << "File4:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file4);
			}
			
		}
		else
		{
			clearFile(file1);
			clearFile(file2);
			sorted = merge(file3, file4, file1, file2);
			if (sorted) { break; }
			numberOfPhases++;
			swap = false;
			if (displayAfterEachPhase)
			{
				cout << "File3:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file1);
				cout << "File4:" << endl;
				cout << "a0 a1 a2 a3 a4 x" << endl;
				showFileContent(file2);
			}
		}	
	}
	cout << "File after sorting:" << endl;
	cout << "a0 a1 a2 a3 a4 x" << endl;
	if (swap == true)
	{
		showFileContent(file3);
		cout << "Sorted records are in " << file3 << endl;
	}
	else
	{
		showFileContent(file1);
		cout << "Sorted records are in " << file1 << endl;
		
	}
	cout << "Number of reads: "<<numberOfReads << endl;
	cout << "Number of wrides: "<<numberOfWrites << endl;
	cout << "Number of phases: "<<numberOfPhases << endl;
	
	system("pause");
	return 0;
}