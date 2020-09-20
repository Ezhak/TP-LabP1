#ifndef CHOFER_H
#define CHOFER_H

#include <iostream>
#include <cstring>
#include "fecha.h"

struct Chofer {
	char dni[10];
	char apellido[50];
	char nombre[50];
	char cuit[20];
	char telefono[15];
	char vacio;
	Fecha fecha_ingreso;
	Fecha fecha_vencimiento;
	int tipoRegistro;
	bool propietarioAuto;
	bool estado;
};

// Prototipos
bool escribirRegistroChofer(Chofer registro);

// Alta
bool existeDNI(FILE *fp, char* dnibusqueda);
bool existeCUIT(FILE *fp, char* cuitbusqueda);
Chofer cargarRegistroChofer();
void nuevoChofer();
bool escribirRegistroChofer(Chofer registro);

// Baja
void eliminarChofer();

// Modificacion
void modificarChofer();

// Lista
void mostrarRegistroChofer(Chofer registro);
void listarChoferDNI();
void listarChoferes();

#endif // CHOFER_H
