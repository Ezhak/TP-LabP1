#include "viaje.h"

// Alta
void nuevoViaje() {
	Viaje reg;
	FILE* fp;

	fp = fopen("choferes.dat", "rb");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	reg = cargarRegistroViaje();

	// El DNI debe existir en el archivo de choferes.
	if (!existeDNI(fp, reg.dniChofer)) {
		cout << "DNI inválido." << endl;
		fclose(fp);
		return;
	}
	fclose(fp);

	// La fecha del viaje debe ser una fecha anterior o igual a la fecha
	// del sistema.
	if (compararFechaActual(reg.fechaViaje) < 0) {
		cout << "Fecha de viaje inválida." << endl;
		return;
	}

	// La hora de salida debe ser un número entre 0 y 23.
	if (reg.horaSalida < 0 || reg.horaSalida > 23) {
		cout << "Hora de salida inválida." << endl;
		return;
	}

	// El kilometraje debe ser un número mayor a 0.
	if (reg.kilometraje < 0) {
		cout << "Kilometraje inválido." << endl;
		return;
	}

	// El importe debe ser un número mayor a 0.
	if (reg.importe < 0) {
		cout << "Importe inválido." << endl;
		return;
	}

	// La patente no puede contener una cadena vacía.
	if (strpbrk(reg.patente, " \t") || !reg.patente[0]) {
		cout << "Patente inválida." << endl;
		return;
	}

	// La calificación del viaje debe ser un número entero entre 0 y 5.
	if (reg.calificacion < 0 || reg.calificacion > 5) {
		cout << "Calificación inválida." << endl;
		return;
	}

	if (!escribirRegistroViaje(reg))
		return;
}

Viaje cargarRegistroViaje() {
	Viaje reg;

	// Autonumérico.
	reg.idViaje = viajesTotales() + 1;
	if (!reg.idViaje)
		return reg;

	cin.ignore();

	cout << "DNI Chofer: ";
	cin.getline(reg.dniChofer, 10);

	cout << "ID Cliente: ";
	cin >> reg.idCliente ;

	cout << "Fecha del viaje" << endl;
	cout << "Dia: ";
	cin >> reg.fechaViaje.dia;
	cout << "Mes: ";
	cin >> reg.fechaViaje.mes;
	cout << "Anio: ";
	cin >> reg.fechaViaje.anio;

	cout << "Hora de salida: ";
	cin >> reg.horaSalida;

	cout << "Kilometraje: ";
	cin >> reg.kilometraje;

	cout << "Importe: ";
	cin >> reg.importe;

	cin.ignore();

	cout << "Patente: ";
	cin.getline(reg.patente, 10);

	cout << "Calificación: ";
	cin >> reg.calificacion;

	reg.estado = true;
	return reg;
}

bool escribirRegistroViaje(Viaje reg) {
	FILE* fp;

	fp = fopen("viajes.dat", "ab");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return false;
	}
	
	fwrite(&reg, sizeof reg, 1, fp);
	if (ferror(fp)) {
		cout << "Error al escribir archivo!" << endl;
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}

// Baja

// Lista
void listarViajeID() {
	FILE* fp;
	Viaje reg;
	int id;

	fp = fopen("viajes.dat", "rb");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	cout << "Ingrese el ID del viaje: ";
	cin >> id;

	cin.ignore();

	while (fread(&reg, sizeof reg, 1, fp)) {
		if ((reg.idViaje == id) && reg.estado) {
			mostrarRegistroViaje(reg);
			fclose(fp);
			return;
		}
	}

	cout << "Viaje inexistente." << endl;
	fclose(fp);
}

void listarViajes() {
	FILE* fp;
	Viaje reg;

	fp = fopen("viajes.dat", "rb");
	if (!fp) {
		cout << "Error al escribir archivo!" << endl;
		return;
	}

	cin.ignore();

	while (fread(&reg, sizeof reg, 1, fp)) {
		if (reg.estado)
			mostrarRegistroViaje(reg);
	}

	fclose(fp);
}

void mostrarRegistroViaje(Viaje reg) {
	cout << "----------------------------------" << endl;
	cout << "ID viaje: " << reg.idViaje<< endl;
	cout << "DNI chofer: " << reg.dniChofer << endl;
	cout << "ID cliente: " << reg.idCliente << endl;
	cout << "Fecha del viaje: " << endl;
	cout << "\tDia: " << reg.fechaViaje.dia << endl;
	cout << "\tMes: " << reg.fechaViaje.mes << endl;
	cout << "\tAnio: " << reg.fechaViaje.anio << endl;
	cout << "Hora de salida: " << reg.horaSalida << endl;
	cout << "Kilometraje: " << reg.kilometraje << endl;
	cout << "Importe: " << reg.importe << endl;
	cout << "Patente: " << reg.patente << endl;
	cout << "Calificación: " << reg.calificacion << endl;
	cout << "----------------------------------" << endl;
}

// Funciones Complementarias
int viajesTotales() {
	int total;
	FILE* fp;

	fp = fopen("viajes.dat", "a+b");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	total = ftell(fp) / sizeof(Viaje);

	fclose(fp);
	return total;
}

