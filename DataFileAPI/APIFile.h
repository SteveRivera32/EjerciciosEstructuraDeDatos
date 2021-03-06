#pragma once
#include "DataFile.h"

class APIFile
{
private:
	DataFile* file;

	class Employee {
	private:
		int code;
		char name[20];
		float salary;
		bool status;

	public:
		Employee();
		Employee(int, const char[], float);

		void printEmployee();

		int getCode();

		char* toChar(); //convertir toda la clase a bytecode
		void fromChar(char*); //recibe de bytecode y lo inserta en los atributos de clase
		int getSizeOf(); //devuelve el sizeof de la clase
	};

public:
	APIFile();
	APIFile(const char*);

	void saveEmployee();
	void readEmployee(int);
	void BusquedaBinaria(int);
    bool fileExists();
	
};

