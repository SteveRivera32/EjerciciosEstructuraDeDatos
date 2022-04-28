#include "APIFile.h"
#include <iostream>

using std::cout;

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
    cout << "Employee { code: " << code << ", name: " << name
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

void APIFile::saveEmployee()
{
    file->open("W");

    Employee* newone = new Employee(100, "Allan Brito", 800);
    file->write(newone->toChar(), 0, newone->getSizeOf());

    newone = new Employee(101, "Raquel Lopez", 1200);
    file->write(newone->toChar(), newone->getSizeOf(), newone->getSizeOf());

    newone = new Employee(102, "Roberto Perez", 1500);
    file->write(newone->toChar(), newone->getSizeOf() * 2, newone->getSizeOf());

    file->close();
}

void APIFile::readEmployee(int _codeSearch)
{
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
        cout << "Employee not found!\n";

    file->close();
}
