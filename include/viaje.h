#ifndef VIAJE_H
#define VIAJE_H

#include <iostream>
#include "chofer.h"
#include "fecha.h"

using namespace std;

struct Viaje {
	int idViaje;
	char dniChofer[10];
	int idCliente;
	Fecha fechaViaje;
	int horaSalida;
	float kilometraje;
	float importe;
	char patente[10];
	int calificacion;
	bool estado;
};

bool escribirRegistroViaje(Viaje reg);
int viajesTotales();

// Alta
Viaje cargarRegistroViaje();
void nuevoViaje();
bool escribirRegistroViaje(Viaje reg);

// Baja

// Lista
void mostrarRegistroViaje(Viaje reg);
void listarViajeID();
void listarViajes();

// Funciones Complementarias
int viajesTotales();

#endif // VIAJE_H
