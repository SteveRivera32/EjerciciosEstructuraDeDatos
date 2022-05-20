#include "File.h"
#include <iostream>
#include <fstream>

using namespace std;

File_Entry File::find_entry(char* root_directory, char* filename)
{
	//identificar si el directorio existe
	fstream file;

	file.open(root_directory, ios_base::in | std::ios::binary);

	if (!file) {
		cout << "\nEl directorio no existe.\n";
		return;
	}

	file.close();

	//buscar la entrada de directorio
	file.open(root_directory, ios_base::in | ios_base::out | std::ios::binary);

	File_Entry actual;
	char* dataReaded = new char[30];
	int position = 0;

	while (!file.eof()) {

		file.seekg(position, std::ios::beg);
		file.read(dataReaded, 30);

		if (dataReaded == filename) {
			//guardar entrada de directorio si coincide el nombre
			file.seekg(position, std::ios::beg);
			file.read(reinterpret_cast<char*>(&actual), sizeof(File_Entry));
			return actual;
		}

		//seguir la lectura
		file.seekg(position, std::ios::beg);
		file.read(reinterpret_cast<char*>(&actual), sizeof(File_Entry));
		position += sizeof(File_Entry);

	}
}
