#pragma once
#include "chofer.h"

using namespace std;
using namespace rlutil;

//-------- Estructuras
struct Viaje {
	int idViaje;
	int idCliente;
	int horaSalida;
	int calificacion;
	float kms;
	float importe;
	char dniChofer[10];
	char patente[10];
	Fecha fechaViaje;
	bool estado;
};
//------------ ABL ------------
// Alta
Viaje cargarViaje() {
	Viaje registro;

	return registro;
}
void grabarViaje() {

}

// Baja

// Lista

// Funciones Complementarias
int cantidadArticulos() { // en el apartado de Alta, especificamente en cargarViaje(); se debera cargar el ID de manera
	int cantidad;         // reg.idViaje = cantidadArticulos()+1; Asi, es un articulo autonumerico. 
	FILE* fp;
	fp = fopen("viajes.dat", "rb");

	if (!fp) {
		cout << "Error. :)" << endl;
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	cantidad = ftell(fp) / sizeof(Viaje);

	fclose(fp);

	return cantidad;
}