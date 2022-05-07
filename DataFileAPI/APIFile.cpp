#include "APIFile.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

APIFile::Employee::Employee() : code(0), salary(0), status(0)
{
    memcpy(name, "NotDefined", strlen("NotDefined") + 1);
}

APIFile::Employee::Employee(int _code, const char _name[], float _salary)
    : code(_code), salary(_salary), status(1)
{
    memcpy(name, _name, strlen(_name) + 1);
}

void APIFile::Employee::printEmployee()
{
    cout << "\nEmployee { code: " << code << ", name: " << name
        << ", salary: " << salary << ", status: " << status << " }\n";
}

int APIFile::Employee::getCode()
{
    return code;
}

char* APIFile::Employee::toChar()
{
    char* charResult = new char[sizeof(Employee)];

    memcpy(&charResult[0], &code, sizeof(code));
    memcpy(&charResult[sizeof(code)], name, sizeof(name)); //no se pone & porque copiaria solo la primera letra del name
    memcpy(&charResult[sizeof(code) + sizeof(name)], &salary, sizeof(salary));
    memcpy(&charResult[sizeof(code) + sizeof(name) + sizeof(salary)], &status, sizeof(status));

    return charResult;
}

void APIFile::Employee::fromChar(char* _charReaded)
{
    memcpy(&code, &_charReaded[0], sizeof(code));
    memcpy(name, &_charReaded[sizeof(code)], sizeof(name));
    memcpy(&salary, &_charReaded[sizeof(code) + sizeof(name)], sizeof(salary));
    memcpy(&status, &_charReaded[sizeof(code) + sizeof(name) + sizeof(salary)], sizeof(status));
}

int APIFile::Employee::getSizeOf()
{
    return sizeof(Employee);
}

APIFile::APIFile()
{
    file = new DataFile("testEmployee.bin");
}

APIFile::APIFile(const char* _filename)
{
    file = new DataFile(_filename);
}

void APIFile::saveEmployee()
{
    file->open("W");

    /*Employee* newone = new Employee(100, "Allan Brito", 800);
    file->write(newone->toChar(), 0, newone->getSizeOf());
    
    newone = new Employee(101, "Raquel Lopez", 1200);
    file->write(newone->toChar(), newone->getSizeOf(), newone->getSizeOf());

    newone = new Employee(102, "Roberto Perez", 1500);
    file->write(newone->toChar(), newone->getSizeOf() * 2, newone->getSizeOf());*/

    Employee* newone;

    for (int i = 1; i <= 100000; i++) {
        //concatenar con string
        std::string nombreString = "empleado_" + std::to_string(i);

        //cambiar string a char array
        char nombreChar[20];
        strcpy_s(nombreChar, nombreString.c_str());

        newone = new Employee(i, nombreChar, 800 + rand() % 1401);
        file->write(newone->toChar(), newone->getSizeOf() * (i-1), newone->getSizeOf());
    }
    cout << "\nArchivo generado!\n";

    file->close();
}

void APIFile::readEmployee(int _codeSearch)
{
    if (_codeSearch > 100000 || _codeSearch < 1) {
        cout << "\nEmpleado no encontrado.\n";
        return;
    }

    unsigned t0, t1;
    t0 = clock();

    int currentPosition = 0;
    file->open("R");
    
    Employee* toFind = new Employee();

    toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
    currentPosition += toFind->getSizeOf();

    bool found = false;

    while (!file->isEof()) {

        if (toFind->getCode() == _codeSearch) {
            toFind->printEmployee();
            found = true;
            break;
        }

        toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));
        currentPosition += toFind->getSizeOf();
    }

    if (!found)
        cout << "\nEmpleado no encontrado.\n";
  
    file->close();

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    double timems = time * 1000;
    cout << "Tiempo que se tardo: " << timems << " milisegundos" << endl;
}

void APIFile::BusquedaBinaria(int _codigo)
{
    if (_codigo > 100000 || _codigo < 1) {
        cout << "\nEmpleado no encontrado.\n";
        return;
    }

    unsigned t0, t1;
    t0 = clock();

    file->open("R");
    Employee* toFind = new Employee();

    int primero, ultimo, medio, cantidad;
    cantidad = 100000;
    primero = 0;
    ultimo = cantidad - 1;
    medio = (primero + ultimo) / 2;

    int currentPosition = toFind->getSizeOf() * medio;
    bool found = 0;

    while (true) {
        if (toFind->getCode() == _codigo)
        {
            toFind->printEmployee();
            found = true;
            break;
        }

        toFind->fromChar(file->read(currentPosition, toFind->getSizeOf()));

        if (toFind->getCode() < _codigo)
        {
            primero = medio + 1;

        }
        else if (toFind->getCode() > _codigo)
        {
            ultimo = medio - 1;
        }
        medio = (primero + ultimo) / 2;

        currentPosition = toFind->getSizeOf() * medio;
    }

    file->close();

    t1 = clock();
    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    double timems = time * 1000;
    cout << "Tiempo que se tardo: " << timems << " milisegundos" << endl;

}

bool APIFile::fileExists()
{
    return file->exists();
}

