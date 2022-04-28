#include <iostream>
#include "Banco.h"

using namespace std;

int main() {
	Banco* banco = new Banco();
	int opcion, codigo;
	float monto;
	char nombre[30];

	cout << "*** B A N C O ***\n";

	do {
		cout << "\n************** Menu **************\n"
			<< "1. Agregar Cuenta\n"
			<< "2. Depositar\n"
			<< "3. Retirar\n"
			<< "4. Imprimir Cuentas\n"
			<< "5. Imprimir Transacciones\n"
			<< "6. Salir\n"
			<< "Seleccione una opcion (numero): \n";
		cin >> opcion;

		switch (opcion) {
		case 1:
			cout << "\nIndique el codigo de la cuenta:";
			cin >> codigo;

			cout << "\nIndique el nombre de la cuenta:";
			cin >> nombre;

			banco->agregarCuenta(codigo, nombre);
			break;
		case 2:
			cout << "\nIndique el codigo de la cuenta:";
			cin >> codigo;

			cout << "\nIndique el monto a depositar:";
			cin >> monto;

			banco->transaccion(codigo, 1, monto);
			break;
		case 3:
			cout << "\nIndique el codigo de la cuenta:";
			cin >> codigo;

			cout << "\nIndique el monto a retirar:";
			cin >> monto;

			banco->transaccion(codigo, 0, monto);
			break;
		case 4:
			banco->imprimirCuentas();
			break;
		case 5:
			banco->imprimirTransacciones();
			break;
		case 6:
			break;
		default:
			cout << "\nLa opcion que selecciono no es valida.\n\n";
			break;
		}

	} while (opcion != 6);
}