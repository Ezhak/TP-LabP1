#ifndef FECHA_H
#define FECHA_H

#include <ctime>

struct Fecha {
	int dia;
	int mes;
	int anio;
};

tm crearTmFecha(Fecha fecha);
int compararFechaActual(Fecha fecha);

#endif // FECHA_H
