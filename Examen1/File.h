#pragma once

#ifndef FILE_H
#define FILE_H

struct File_Entry {
	char name[30];
	int size;
	char type;
	int padre;
	int primerHijo;
	int hermanoDerec;
	int primerBloq;
	bool libre;
};

class File
{
public:
	File_Entry find_entry(char* root_directory, char* filename);
};

#endif // FILE.H

