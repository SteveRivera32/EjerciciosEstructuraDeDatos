#include <conio.h>
#include <iostream>
#include "APIFile.h"
#include <string>

using namespace std;

int main() {
	char nombre[30];

	cout << "Indique el nombre del archivo (agregar .bin):\n";
	cin >> nombre;

	APIFile _api(nombre);

	int opcion, codigo;

	do {
		cout << "\n************** Menu **************\n"
			<< "1. Generar Archivo\n"
			<< "2. Busqueda Secuencial\n"
			<< "3. Busqueda Binaria\n"
			<< "4. Salir\n"
			<< "Seleccione una opcion (numero): \n";
		cin >> opcion;

		switch (opcion) {
		case 1:
			if (_api.fileExists()) {
				cout << "\nEl archivo ya existe.\n";
			}
			else
				_api.saveEmployee();
			break;
		case 2:
			if (_api.fileExists()) {
				cout << "Ingresar codigo de empleado: ";
				cin >> codigo;

				_api.readEmployee(codigo);
			}else
				cout << "\nEl archivo no existe.\n";
			break;
		case 3:
			if (_api.fileExists()) {
				cout << "Ingresar codigo de empleado: ";
				cin >> codigo;

				_api.BusquedaBinaria(codigo);
			}else
				cout << "\nEl archivo no existe.\n";
			break;
		case 4:
			break;
		default:
			cout << "\nLa opcion que selecciono no es valida.\n\n";
			break;
		}
	} while (opcion != 4);
}