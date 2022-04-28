#pragma once

#ifndef BANCO_H
#define BANCO_H

struct Empleado {
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
	void agregarEmpleado(int, const char*);
	bool empleadoExiste(int);
	void transaccion(int, short, float);
	bool cambiarSaldo(int, short, float);

	void imprimirEmpleados();
	void imprimirTransacciones();
};

#endif // !BANCO_H

