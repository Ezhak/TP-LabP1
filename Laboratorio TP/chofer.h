#ifndef CHOFER_H
#define CHOFER_H

#include <iostream>
#include <cstring>
#include <ctime>
#include "fecha.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;
//-------- Estructuras
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

//------------ ABML ------------
//Prototipo
void escribirRegistroChofer(Chofer registro);

// Alta
bool existeDNI(FILE *fp, char* dnibusqueda) {
	Chofer registro;

	fseek(fp, 0, SEEK_SET);
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado)
			return true;
	}

	return false;
}
bool existeCUIT(FILE *fp, char* cuitbusqueda) {
	Chofer registro;

	fseek(fp, 0, SEEK_SET);  // resetear indicador de posición 0 + SEEK_SET (0)
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.cuit, cuitbusqueda) && registro.estado)
			return false;
	}

	return true;
}

Chofer cargarRegistroChofer() {
	Chofer registro;
	char* occurrence;

	cin.ignore();

	// strspn devuelve el largo de la porción inicial de str1 que sólo
	// contenga caracteres de str2 (overkill).
	//
	// strpbrk devuelve un puntero a la primera ocurrencia en str1 de
	// cualquier caracter en str2. Evita espacios o <Tab> más simple,
	// y si es una cadena vacía, registro.campo[0] valdrá '\0'.

	do {
		cout << "DNI: ";
		cin.getline(registro.dni, 10);
		occurrence = strpbrk(registro.dni, " \t");
	} while (occurrence || !registro.dni[0]);

	do {
		cout << "Apellido: ";
		cin.getline(registro.apellido, 50);
		occurrence = strpbrk(registro.apellido, " \t");
	} while (occurrence || !registro.apellido[0]);

	do {
		cout << "Nombre: ";
		cin.getline(registro.nombre, 50);
		occurrence = strpbrk(registro.nombre, " \t");
	} while (occurrence || !registro.nombre[0]);

	do {
		cout << "CUIT: ";
		cin.getline(registro.cuit, 30);
		occurrence = strpbrk(registro.cuit, " \t");
	} while (occurrence || !registro.cuit[0]);

	cout << "Telefono: " << endl;
	cin.getline(registro.telefono, 15);
	cout << "Fecha de Ingreso: " << endl;
	cout << "Dia: " << endl;
	cin >> registro.fecha_ingreso.dia;
	cout << "Mes: " << endl;
	cin >> registro.fecha_ingreso.mes;
	cout << "Anio: " << endl;
	cin >> registro.fecha_ingreso.anio;
	cout << "Fecha de vencimiento del registro: " << endl;
	cout << "Dia: " << endl;
	cin >> registro.fecha_vencimiento.dia;
	cout << "Mes: " << endl;
	cin >> registro.fecha_vencimiento.mes;
	cout << "Anio: " << endl;
	cin >> registro.fecha_vencimiento.anio;
	cout << "Tipo de registro: (1-3)" << endl;
	cin >> registro.tipoRegistro;
	registro.estado = true;

	return registro;
}
void nuevoChofer() {
	bool validarGrabado = true;
	Chofer reg;

	FILE* fp;
	fp = fopen("choferes.dat", "a+b");
	if (!fp) {
		cout << "Error. :)" << endl;
		validarGrabado = false;
		return;
	}

	reg = cargarRegistroChofer();

	tm tmFechaIng = crearTmFecha(reg.fecha_ingreso);
	tm tmFechaVenc = crearTmFecha(reg.fecha_vencimiento);

	if (existeDNI(fp, reg.dni) ||
	    existeCUIT(fp, reg.cuit) ||
	    compararFechaActual(tmFechaIng) > 0 ||
	    compararFechaActual(tmFechaVenc) < 0) {
		cout << "Ya existe ese DNI o CUIT, por favor, ingrese otro DNI o CUIT" << endl;
		cout << "O bien la Fecha de Ingreso/Vencimiento es invalida." << endl;
		anykey();
		return;
	}
	else {
		escribirRegistroChofer(reg);
		if (validarGrabado)
			cout << "Registros grabados en archivo correctamente!" << endl << endl;
		else
			cout << "No se pudo grabar. :)" << endl << endl;
	}

	fclose(fp);
}
void escribirRegistroChofer(Chofer registro) {
	FILE* fp;

	fp = fopen("choferes.dat", "ab");
	if (!fp) {
		cout << "Error. :)" << endl;
		return;
	}
	
	fwrite(&registro, sizeof registro, 1, fp);

	fclose(fp);
	return;
}
// Baja
int eliminarChofer() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	char dnibusqueda[10];
	int pos = 0;

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error. :)" << endl;
		return -1;
	}

	do {
		cin.ignore();
		cout << "Ingrese el DNI a dar de baja" << endl; 
		cin.getline(dnibusqueda, 10);
		occurrence = strpbrk(dnibusqueda, " \t");
	} while (occurrence || !dnibusqueda[0]);

	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado) { //Esta funcion esta explicada en validarDNI/CUIT()
			registro.estado = false;

			fseek(fp, pos * sizeof registro, 0); //fseek lo que hace es ubicar el cursor en el archivo, va a ir posicionandose a medida que itera
			fwrite(&registro, sizeof registro, 1, fp); //Es decir, la posicion * lo que pesa el registro.

			cout << "Chofer eliminado, registro dado de baja" << endl;

			fclose(fp);
			return pos;
		}
		pos++;
	}

	cout << "No se pudo dar de baja. :)" << endl;

	fclose(fp);
	return -1;
}
// Modificacion
int modificarChofer() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	int pos;
	char dnibusqueda[10];

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error. :)" << endl;
		return -1;
	}

	do {
		cin.ignore();
		cout << "Ingrese el DNI:" << endl;
		cin.getline(dnibusqueda, 10);
		occurrence = strpbrk(dnibusqueda, " \t");
	} while (occurrence || !dnibusqueda[0]);

	pos = 0;
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado) { //Explicado en bajaRegistro()
			cout << "Ingrese la nueva fecha de vencimiento" << endl; //Una vez que encuentra la coincidencia entre registro.dni, con busquedadni,
			cout << "Dia: " << endl;								// Te deja cargar la nueva fecha, y asi lo modificas.
			cin >> registro.fecha_vencimiento.dia;

			cout << "Mes: " << endl;
			cin >> registro.fecha_vencimiento.mes;

			cout << "Anio: " << endl;
			cin >> registro.fecha_vencimiento.anio;

			fseek(fp, pos * sizeof registro, 0); //Explicado ya en bajaRegistro()
			fwrite(&registro, sizeof registro, 1, fp);

			fclose(fp);
			return pos;
		}
		pos++;
	}

	cout << "No existe ese DNI" << endl;

	fclose(fp);
	return -1;
}
// Lista
void mostrarRegistroChofer(Chofer registro) {
	if (registro.estado) {
		cout << "DNI: " << registro.dni << endl;
		cout << "Apellido: " << registro.apellido << endl;
		cout << "Nombre: " << registro.nombre << endl;
		cout << "CUIT: " << registro.cuit << endl;
		cout << "Telefono: " << registro.telefono << endl;
		cout << "Fecha de Ingreso: " << endl;
		cout << "\tDia: " << registro.fecha_ingreso.dia << endl;
		cout << "\tMes: " << registro.fecha_ingreso.mes << endl;
		cout << "\tAnio: " << registro.fecha_ingreso.anio << endl;
		cout << "Fecha de vencimiento del registro: " << endl;
		cout << "\tDia: " << registro.fecha_vencimiento.dia << endl;
		cout << "\tMes: " << registro.fecha_vencimiento.mes << endl;
		cout << "\tAnio: " << registro.fecha_vencimiento.anio << endl;
		cout << "Tipo de registro (1-3): " << registro.tipoRegistro << endl;
		cout << "----------------------------------------" << endl;
	}
}

void listarChoferes() {
	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.dat", "rb");
	if (!fp) return;

	while (fread(&registro, sizeof registro, 1, fp)) {
		if (registro.estado)
			mostrarRegistroChofer(registro);
	}

	fclose(fp);
	anykey();
}

int listarChoferDNI() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	int pos;
	char dnibusqueda[10];

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error. :)" << endl;
		return -1;
	}

	do {
		cin.ignore();
		cout << "Ingrese el DNI:" << endl;
		cin.getline(dnibusqueda, 10);
		occurrence = strpbrk(dnibusqueda, " \t");
	} while (occurrence || !dnibusqueda[0]);

	pos = 0;
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado) {  //Cuando encuentra coincidencia entre el DNI dado con registro.dni
			cout << endl << "----------------------------------------" << endl;     //Te muestra el registro que coincida con el DNI.
			mostrarRegistroChofer(registro);

			fclose(fp);
			return pos;
		}
		pos++;
	}

	cout << "No existe ese DNI" << endl;

	fclose(fp);
	return -1;
}

#endif // CHOFER_H
