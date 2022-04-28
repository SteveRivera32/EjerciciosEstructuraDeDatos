#include "DataFile.h"

DataFile::DataFile() : path(nullptr) {}

DataFile::DataFile(const char* _path) : path(_path) {}

DataFile::~DataFile()
{
	delete path;
	file.close();
}

void DataFile::open(const char* _openFormat)
{
	if (strcmp(_openFormat, "R") == 0)
		openMode = ios_base::in;
	else if (strcmp(_openFormat, "W") == 0)
		openMode = ios_base::out;
	else if (strcmp(_openFormat, "RW") == 0)
		openMode = ios_base::in | ios_base::out;

	file.open(path, openMode | std::ios::binary);

	if (!file) {
		std::cerr << "Error: file could not be opened" << std::endl;

		exit(1);
	}
}

void DataFile::close()
{
	file.close();
}

void DataFile::write(char* _data, unsigned int _position, unsigned int _length)
{
	file.seekp(_position, std::ios::beg);
	file.write(_data, _length);
}

char* DataFile::read(unsigned int _position, unsigned int _length)
{
	char* dataReaded = new char[_length];

	file.seekg(_position, std::ios::beg);
	file.read(dataReaded, _length);

	return dataReaded;
}

bool DataFile::isEof()
{
	return file.eof();
}
