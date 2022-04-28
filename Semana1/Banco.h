#pragma once

#ifndef BANCO_H
#define BANCO_H

struct Cuenta {
	int codigo;
	char nombre[30];
	float saldo;
};

struct Transaccion {
	int codigo;
	short tipoMovimiento;
	float monto;
};

class Banco
{
public:
	void agregarCuenta(int, const char*);
	bool cuentaExiste(int);
	void transaccion(int, short, float);
	bool cambiarSaldo(int, short, float);

	void imprimirCuentas();
	void imprimirTransacciones();
};

#endif // !BANCO_H

