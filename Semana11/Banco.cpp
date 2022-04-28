#include "Banco.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void Banco::agregarCuenta(int _codigo, const char* _nombre)
{
	ofstream archivoCuenta("cuentas.bin", ios::out | ios::app | ios::binary);

	if (!archivoCuenta)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return;
	}

	Cuenta nuevo;
	nuevo.codigo = _codigo;
	strcpy_s(nuevo.nombre, strlen(_nombre) + 1, _nombre);
	nuevo.saldo = 0;

	if (!cuentaExiste(nuevo.codigo)) {
		archivoCuenta.write(reinterpret_cast<const char*>(&nuevo), sizeof(Cuenta));

		cout << "\nRegistro almacenado!\n";
		archivoCuenta.close();
	}
	else
		cout << "\nNo se pudo agregar, el codigo ya esta en uso.\n";
}

bool Banco::cuentaExiste(int _codigo)
{
	fstream archivoCuenta("cuentas.bin", ios::in | ios::out | ios::binary);

	if (!archivoCuenta)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return NULL;
	}

	archivoCuenta.seekg(0, ios::beg);
	long posicionArchivo = 0;

	Cuenta actual;
	archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));

	while (!archivoCuenta.eof()) {
		if (actual.codigo == _codigo)
			return true;

		archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));
	}

	archivoCuenta.close();
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
		if (cuentaExiste(_codigo)) {
			if (cambiarSaldo(_codigo, _tipoMovimiento, _monto)) {
				archivoTransaccion.write(reinterpret_cast<const char*>(&nuevo), sizeof(Transaccion));

				cout << "\nDeposito almacenado!\n";
				archivoTransaccion.close();
			}
			else
				cout << "\nEl deposito no se pudo realizar.\n";

		}
		else
			cout << "\nEl deposito se pudo realizar, la cuenta no existe.\n";
	}
	else if (_tipoMovimiento == 0) {
		if (cuentaExiste(_codigo)) {
			if (cambiarSaldo(_codigo, _tipoMovimiento, _monto)) {
				archivoTransaccion.write(reinterpret_cast<const char*>(&nuevo), sizeof(Transaccion));

				cout << "\nRetiro almacenado!\n";
				archivoTransaccion.close();
			}
			else
				cout << "\nEl retiro no se pudo realizar.\n";

		}
		else
			cout << "\nEl retiro se pudo realizar, la cuenta no existe.\n";
	}
}

bool Banco::cambiarSaldo(int _codigo, short _tipoMovimiento, float _monto)
{
	fstream archivoCuenta("cuentas.bin", ios::in | ios::out | ios::binary);

	if (!archivoCuenta)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return false;
	}

	archivoCuenta.seekg(0, ios::beg);
	long posicionArchivo = 0;

	Cuenta actual;
	archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));

	while (!archivoCuenta.eof()) {
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

			archivoCuenta.seekp(posicionArchivo, ios::beg);
			archivoCuenta.write(reinterpret_cast<const char*>(&actual), sizeof(Cuenta));
			archivoCuenta.close();

			return true;
		}
		posicionArchivo = archivoCuenta.tellg();
		archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));
	}

	archivoCuenta.close();
	return false;
}

void Banco::imprimirCuentas()
{
	fstream archivoCuenta("cuentas.bin", ios::in | ios::out | ios::binary);

	if (!archivoCuenta)
	{
		cout << "Error al intentar abrir el archivo cuentas.bin\n";
		return;
	}

	archivoCuenta.seekg(0, ios::beg);

	Cuenta actual;
	archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));

	int i = 1;

	cout << "\n--- Cuentas ---\n";
	while (!archivoCuenta.eof()) {

		cout << "Cuenta " << i << " { codigo: " << actual.codigo << ", nombre: " << actual.nombre
			<< ", saldo: " << actual.saldo << " }\n";

		i += 1;
		archivoCuenta.read(reinterpret_cast<char*>(&actual), sizeof(Cuenta));
	}

	cout << "-----------------\n";
	archivoCuenta.close();
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
