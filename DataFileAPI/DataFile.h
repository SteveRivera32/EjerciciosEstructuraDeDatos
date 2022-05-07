#pragma once

#include <fstream>
#include <iostream>

using std::fstream;
using std::ios_base;

class DataFile
{
public:
	DataFile();
	DataFile(const char*);
	~DataFile();

	void open(const char*);
	void close();
	bool exists();

	void write(char*, unsigned int, unsigned int);
	char* read(unsigned int, unsigned int);

	bool isEof();

private:
	fstream file;
	ios_base::openmode openMode; //modo de apertura
	const char* path;
};