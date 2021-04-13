#pragma once

class File
{
public:
	const char* name;
	int position;
	int size;

	File(const char* name);
	int getSize();
	
};