#pragma once
#include <iostream>
#include <cstring>
#include <ctime>
#include "rlutil.h"
using namespace std;
using namespace rlutil;
//-------- Estructuras
struct Fecha {
	int dia;
	int mes;
	int anio;
};
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
void grabarRegistro(Chofer registro);
// Alta
bool validarFechaIngreso(tm fecha_actual, Fecha fecha_ing){
	struct tm t_ing = {0};
	t_ing.tm_mday = fecha_ing.dia;
	t_ing.tm_mon = fecha_ing.mes - 1;
	t_ing.tm_year = fecha_ing.anio - 1900;

	time_t t1 = mktime(&fecha_actual);
	time_t t2 = mktime(&t_ing);

	return (difftime(t1, t2) > 0);
}

bool validarFechaVencimiento(tm fecha_actual, Fecha fecha_venc){
	struct tm t_venc = {0};
	t_venc.tm_mday = fecha_venc.dia;
	t_venc.tm_mon = fecha_venc.mes - 1;
	t_venc.tm_year = fecha_venc.anio - 1900;

	time_t t1 = mktime(&fecha_actual);
	time_t t2 = mktime(&t_venc);

	return (difftime(t1, t2) < 0);
}

bool validarDNI(FILE *fp, char* dnibusqueda) {
	Chofer registro;

	fseek(fp, 0, SEEK_SET);
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.dni, dnibusqueda) && (registro.estado == true))
			return false;
	}

	return true;
}
bool validarCUIT(FILE *fp, char* cuitbusqueda) {
	Chofer registro;

	fseek(fp, 0, SEEK_SET);  // resetear indicador de posición 0 + SEEK_SET (0)
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.cuit, cuitbusqueda) && (registro.estado == true))
			return false;
	}

	return true;
}

Chofer cargarRegistro() {
	Chofer registro;
	char *occurrence;

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
void altaRegistro() {
	time_t timer = time(0);
	// localtime() devuelve un puntero a la estructura estática interna
	// std::tm.
	// Recordar que el operador 'struct->object' es idéntico a '(*struct).object'
	struct tm* tmPtr = localtime(&timer);

	bool validarGrabado = true;
	Chofer reg;

	reg = cargarRegistro();

	FILE* fp;
	fp = fopen("choferes.dat", "a+b");
	if (!fp) {
		cout << "Error. :)" << endl;
		validarGrabado = false;
		return;
	}

	if (!validarDNI(fp, reg.dni) ||
	    !validarCUIT(fp, reg.cuit) ||
	    !validarFechaIngreso(*tmPtr, reg.fecha_ingreso) ||
	    !validarFechaVencimiento(*tmPtr, reg.fecha_vencimiento)) {
		cout << "Ya existe ese DNI o CUIT, por favor, ingrese otro DNI o CUIT" << endl;
		cout << "O bien la Fecha de Ingreso/Vencimiento es invalida." << endl;
		anykey();
		return;
	}
	else {
		grabarRegistro(reg);
		if (validarGrabado)
			cout << "Registros grabados en archivo correctamente!" << endl << endl;
		else
			cout << "No se pudo grabar. :)" << endl << endl;
	}
	fclose(fp);
}
void grabarRegistro(Chofer registro) {
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
int bajaRegistro() {
	FILE* p;
	Chofer registro;
	int pos;
	char dnibusqueda[10];
	p = fopen("choferes.dat", "rb+");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return -1;
	}
	do {
		cin.ignore();
		cout << "Ingrese el DNI a dar de baja" << endl; 
		cin.getline(dnibusqueda, 10);
		pos = strspn(dnibusqueda, " \t"); //Esta parte la explique en cargarRegistro();
	} while (dnibusqueda[pos] == 0);
	pos = 0;
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if ((strcmp(registro.dni, dnibusqueda) == 0) && registro.estado == true) { //Esta funcion esta explicada en validarDNI/CUIT()
			registro.estado = false;
			fseek(p, pos * sizeof registro, 0); //fseek lo que hace es ubicar el cursor en el archivo, va a ir posicionandose a medida que itera
			fwrite(&registro, sizeof registro, 1, p); //Es decir, la posicion * lo que pesa el registro.
			cout << "Chofer eliminado, registro dado de baja" << endl;
			fclose(p);
			return pos;
		}
		pos++;
	}
	cout << "No se pudo dar de baja. :)" << endl;
	fclose(p);
	return -1;
}
// Modificacion
int modificarRegistro() {
	FILE* p;
	Chofer registro;
	int pos;
	char dnibusqueda[10];
	p = fopen("choferes.dat", "rb+");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return -1;
	}
	do {
		cin.ignore();
		cout << "Ingrese el DNI:" << endl;
		cin.getline(dnibusqueda, 10);
		pos = strspn(dnibusqueda, " \t"); //Explicado en cargarRegistro()
	} while (dnibusqueda[pos] == 0); 
	pos = 0;
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if ((strcmp(registro.dni, dnibusqueda) == 0) && registro.estado == true) { //Explicado en bajaRegistro()
			cout << "Ingrese la nueva fecha de vencimiento" << endl; //Una vez que encuentra la coincidencia entre registro.dni, con busquedadni,
			cout << "Dia: " << endl;								// Te deja cargar la nueva fecha, y asi lo modificas.
			cin >> registro.fecha_vencimiento.dia;
			cout << "Mes: " << endl;
			cin >> registro.fecha_vencimiento.mes;
			cout << "Anio: " << endl;
			cin >> registro.fecha_vencimiento.anio;
			fseek(p, pos * sizeof registro, 0); //Explicado ya en bajaRegistro()
			fwrite(&registro, sizeof registro, 1, p);
			fclose(p);
			return pos;
		}
		pos++;
	}
	cout << "No existe ese DNI" << endl;
	fclose(p);
	return -1;
}
// Lista
void mostrarRegistro(Chofer registro) {
	if (registro.estado == true) {
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
void listaRegistro() {
	FILE* p;
	Chofer registro;
	p = fopen("choferes.dat", "rb");
	if (p == NULL) return;
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if (registro.estado == true) {
			mostrarRegistro(registro);
		}
	}
	fclose(p);
	anykey();
}
int listaporDNI() {
	FILE* p;
	Chofer registro;
	int pos;
	char dnibusqueda[10];
	p = fopen("choferes.dat", "rb+");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return -1;
	}
	do {
		cin.ignore();
		cout << "Ingrese el DNI:" << endl;
		cin.getline(dnibusqueda, 10);
		pos = strspn(dnibusqueda, " \t");
	} while (dnibusqueda[pos] == 0);
	pos = 0;
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if ((strcmp(registro.dni, dnibusqueda) == 0) && registro.estado == true) {  //Cuando encuentra coincidencia entre el DNI dado con registro.dni
			cout << endl << "----------------------------------------" << endl;     //Te muestra el registro que coincida con el DNI.
			mostrarRegistro(registro);
			fclose(p);
			return pos;
		}
		pos++;
	}
	cout << "No existe ese DNI" << endl;
	fclose(p);
	return -1;
}
