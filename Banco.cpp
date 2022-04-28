#include "Banco.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Banco::agregarEmpleado(int _codigo, const char* _nombre)
{
	ofstream archivoEmpleado("empleados.bin", ios::out | ios::app | ios::binary);

	if (!archivoEmpleado)
	{
		cout << "Error al intentar abrir el archivo empleados.bin\n";
		return;
	}

	Empleado nuevo;
	nuevo.codigo = _codigo;
	strcpy_s(nuevo.nombre, strlen(_nombre) + 1, _nombre);
	nuevo.saldo = 0;

	if (!empleadoExiste(nuevo.codigo)) {
		archivoEmpleado.write(reinterpret_cast<const char*>(&nuevo), sizeof(Empleado));

		cout << "\nRegistro almacenado!\n";
		archivoEmpleado.close();
	}else
		cout << "\nNo se pudo agregar, el codigo ya está en uso.\n";
}

bool Banco::empleadoExiste(int _codigo)
{
	fstream archivoEmpleado("empleados.bin", ios::in | ios::out | ios::binary);

	if (!archivoEmpleado)
	{
		cout << "Error al intentar abrir el archivo empleados.bin\n";
		return NULL;
	}

	archivoEmpleado.seekg(0, ios::beg);
	long posicionArchivo = 0;

	Empleado actual;
	archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));

	while (!archivoEmpleado.eof()) {
		if (actual.codigo == _codigo)
			return true;

		archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));
	}

	archivoEmpleado.close();
	return false;
}

void Banco::transaccion(int _codigo, short _tipoMovimiento, float _monto)
{
	ofstream archivoTransaccion("transacciones.bin", ios::out | ios::app | ios::binary);

	if (!archivoTransaccion)
	{
		cout << "Error al intentar abrir el archivo transacciones.bin\n";
		return;
	}

	Transaccion nuevo;
	nuevo.codigo = _codigo;
	nuevo.tipoMovimiento = _tipoMovimiento;
	nuevo.monto = _monto;

	if (_tipoMovimiento == 1) {
		if (empleadoExiste(_codigo)) {
			if (cambiarSaldo(_codigo, _tipoMovimiento, _monto)) {
				archivoTransaccion.write(reinterpret_cast<const char*>(&nuevo), sizeof(Transaccion));

				cout << "\nDeposito almacenado!\n";
				archivoTransaccion.close();
			}
			else
				cout << "\nEl deposito no se pudo realizar.\n";

		}
		else
			cout << "\nEl deposito se pudo realizar, el empleado no existe.\n";
	}
	else if (_tipoMovimiento == 0) {
		if (empleadoExiste(_codigo)) {
			if (cambiarSaldo(_codigo, _tipoMovimiento, _monto)) {
				archivoTransaccion.write(reinterpret_cast<const char*>(&nuevo), sizeof(Transaccion));

				cout << "\nRetiro almacenado!\n";
				archivoTransaccion.close();
			}
			else
				cout << "\nEl retiro no se pudo realizar.\n";

		}
		else
			cout << "\nEl retiro se pudo realizar, el empleado no existe.\n";
	}
}

bool Banco::cambiarSaldo(int _codigo, short _tipoMovimiento, float _monto)
{
	fstream archivoEmpleado("empleados.bin", ios::in | ios::out | ios::binary);

	if (!archivoEmpleado)
	{
		cout << "Error al intentar abrir el archivo empleados.bin\n";
		return false;
	}

	archivoEmpleado.seekg(0, ios::beg);
	long posicionArchivo = 0;

	Empleado actual;
	archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));

	while (!archivoEmpleado.eof()) {
		if (actual.codigo == _codigo) {
			if (_tipoMovimiento == 0) {
				if (_monto <= actual.saldo) {
					actual.saldo -= _monto;
				}
				else
					return false;
			}
			else if (_tipoMovimiento == 1) {
				actual.saldo += _monto;
			}

			archivoEmpleado.seekp(posicionArchivo, ios::beg);
			archivoEmpleado.write(reinterpret_cast<const char*>(&actual), sizeof(Empleado));
			archivoEmpleado.close();

			return true;
		}
		posicionArchivo = archivoEmpleado.tellg();
		archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));
	}

	archivoEmpleado.close();
	return false;
}

void Banco::imprimirEmpleados()
{
	fstream archivoEmpleado("empleados.bin", ios::in | ios::out | ios::binary);

	if (!archivoEmpleado)
	{
		cout << "Error al intentar abrir el archivo empleados.bin\n";
		return;
	}

	archivoEmpleado.seekg(0, ios::beg);

	Empleado actual;
	archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));

	int i = 1;

	cout << "\n--- Empleados ---\n";
	while (!archivoEmpleado.eof()) {

		cout << "Empleado " << i << " { codigo: " << actual.codigo << ", nombre: " << actual.nombre
			<< ", saldo: " << actual.saldo << " }\n";

		i += 1;
		archivoEmpleado.read(reinterpret_cast<char*>(&actual), sizeof(Empleado));
	}

	cout << "-----------------\n";
	archivoEmpleado.close();
}

void Banco::imprimirTransacciones()
{
	fstream archivoTransaccion("transacciones.bin", ios::in | ios::out | ios::binary);

	if (!archivoTransaccion)
	{
		cout << "Error al intentar abrir el archivo transacciones.bin\n";
		return;
	}

	archivoTransaccion.seekg(0, ios::beg);

	Transaccion actual;
	archivoTransaccion.read(reinterpret_cast<char*>(&actual), sizeof(Transaccion));

	cout << "\n--- Transacciones ---\n";
	while (!archivoTransaccion.eof()) {

		cout << actual.codigo << " " << actual.tipoMovimiento << " " << actual.monto
			<< " ---> ";
		if (actual.tipoMovimiento == 0) 
			cout << "retiro de L" << actual.monto << "\n";
		else if (actual.tipoMovimiento == 1) 
			cout << "deposito de L" << actual.monto << "\n";

		archivoTransaccion.read(reinterpret_cast<char*>(&actual), sizeof(Transaccion));
	}

	cout << "---------------------\n";
	archivoTransaccion.close();
}
