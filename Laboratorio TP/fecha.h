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

int compararFechaActual(tm fecha){
	time_t timer = time(0);
	// localtime() devuelve un puntero a la estructura estática interna
	// std::tm.
	// Recordar que el operador 'struct->object' es idéntico a '(*struct).object'
	struct tm* fechaActual = localtime(&timer);

	time_t t1 = mktime(fechaActual);
	time_t t2 = mktime(&fecha);

	return difftime(t1, t2);
}
#endif // FECHA_H
