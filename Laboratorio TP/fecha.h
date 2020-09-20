#ifndef FECHA_H
#define FECHA_H

#include <ctime>

struct Fecha {
	int dia;
	int mes;
	int anio;
};

tm crearTmFecha(Fecha fecha) {
	struct tm tmFecha = {0};
	tmFecha.tm_mday = fecha.dia;
	tmFecha.tm_mon = fecha.mes - 1;
	tmFecha.tm_year = fecha.anio - 1900;

	return tmFecha;
}

int compararFechaActual(Fecha fecha){
	// localtime() devuelve un puntero a la estructura estática interna
	// std::tm.
	// Recordar que el operador 'struct->object' es idéntico a '(*struct).object'
	time_t timer = time(0);
	struct tm fechaActual = *localtime(&timer);
	struct tm tmFecha = crearTmFecha(fecha);

	time_t t1 = mktime(&fechaActual);
	time_t t2 = mktime(&tmFecha);

	return difftime(t1, t2);
}
#endif // FECHA_H
