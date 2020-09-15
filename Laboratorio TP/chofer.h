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
struct FechaVencimiento {
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
	Fecha fechaingreso;
	FechaVencimiento vencimientoRegistro;
	int tipoRegistro;
	bool propietarioAuto;
	bool estado;
};

//------------ ABML ------------
//Prototipo
void grabarRegistro(Chofer registro);
// Alta
int validarFechas(Chofer registro){
	time_t tiempo;
	struct tm* tmPtr;
	tiempo = time(NULL);
	tmPtr = localtime(&tiempo); //Con time.h se puede obtener la fecha actual y procedi a guardarlo en variables distintas discriminado por
	int dia = tmPtr->tm_mday; //Dia,Mes y Año, la misma metodologia que utilice al cargar el registro del struct.
	int mes = tmPtr->tm_mon + 1;
	int anio = 1900 + tmPtr->tm_year;
	//Lo que hago aca es basicamente comparar las dos fechas con un condicional superrebuscado, los return '1111' y '2222' son solo codigos
	//Puestos por mi, a modo de "bandera" para luego en altaRegistro() validarlos, si los return dan esos numeros, pues, no te deja cargar.
	if ((registro.fechaingreso.dia > dia) && (registro.fechaingreso.mes > mes) && (registro.fechaingreso.anio > anio)) {
		return 1111;
	}
	if ((registro.vencimientoRegistro.dia <= dia) && (registro.vencimientoRegistro.mes <= mes) && (registro.vencimientoRegistro.anio <= anio)) {
		return 2222;
	}
	return 0;
}
int validarDNI(char* dnibusqueda) {
	FILE* p;
	Chofer registro;
	int posicion = 0;
	p = fopen("registros.dat", "rb");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return -1;
	}
	//El while itera hasta que no encuentre nada para leer
	//strcmp compara los dos char, entre registro.dni, y dnibusqueda, si da cero, significa que son IGUALES, por ende
	//va a retornar '1315' que es un codigo que uso para validar a modo de bandera.
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if ((strcmp(registro.dni, dnibusqueda) == 0) && registro.estado == true) {
			fclose(p);
			posicion = 1315;
			return posicion;
		}
		posicion++;
	}
	fclose(p);
	return -1;
}
int validarCUIT(char* cuitbusqueda) {
	FILE* p;
	Chofer registro;
	int posicion = 0;
	p = fopen("registros.dat", "rb");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return -1;
	}
	//El while itera hasta que no encuentre nada para leer
	//strcmp compara los dos char, entre registro.cuit, y cuitbusqueda, si da cero, significa que son IGUALES, por ende
	//va a retornar '1315' que es un codigo que uso para validar a modo de bandera.
	while (fread(&registro, sizeof registro, 1, p) == 1) {
		if ((strcmp(registro.cuit, cuitbusqueda) == 0) && registro.estado == true) {
			posicion = 1315;
			fclose(p);
			return posicion;
		}
		posicion++;
	}
	fclose(p);
	return -1;
}

Chofer cargarRegistro() {
	Chofer registro;
	int pos;
	cin.ignore();
	//Lo que se hace con la funcion strspn es comparar los caracteres del parametro 1 y 2, si los dos coinciden, retorna 0
	//Al retornar 0, lo pongo en un while, mientras que registro.dni[0] por ejemplo, porque POS siempre sera 0 si hay espacio en blanco
	//Significa que mientras este en 0, va a pedir que se ingrese algo. 
	do {
		cout << "DNI: ";
		cin.getline(registro.dni, 10);
		pos = strspn(registro.dni, " \t");
	} while (registro.dni[pos] == 0);
	do {
		cout << "Apellido: ";
		cin.getline(registro.apellido, 50);
		pos = strspn(registro.apellido, " \t");
	} while (registro.apellido[pos] == 0);
	do {
		cout << "Nombre: ";
		cin.getline(registro.nombre, 50);
		pos = strspn(registro.nombre, " \t");
	} while (registro.nombre[pos] == 0);
	do {
		cout << "CUIT: ";
		cin.getline(registro.cuit, 30);
		pos = strspn(registro.cuit, " \t");
	} while (registro.cuit[pos] == 0);
	cout << "Telefono: " << endl;
	cin.getline(registro.telefono, 15);
	cout << "Fecha de Ingreso: " << endl;
	cout << "Dia: " << endl;
	cin >> registro.fechaingreso.dia;
	cout << "Mes: " << endl;
	cin >> registro.fechaingreso.mes;
	cout << "Anio: " << endl;
	cin >> registro.fechaingreso.anio;
	cout << "Fecha de vencimiento del registro: " << endl;
	cout << "Dia: " << endl;
	cin >> registro.vencimientoRegistro.dia;
	cout << "Mes: " << endl;
	cin >> registro.vencimientoRegistro.mes;
	cout << "Anio: " << endl;
	cin >> registro.vencimientoRegistro.anio;
	cout << "Tipo de registro: (1-3)" << endl;
	cin >> registro.tipoRegistro;
	registro.estado = true;
	return registro;
}
void altaRegistro() {
	bool validarGrabado = true; bool espaciosVacios = false; int posicionDNI; int posicionCUIT; int posicionFechaIngreso; int posicionFechaVencimiento;
	Chofer reg;
	//Cargo el registro en la memoria
	reg = cargarRegistro();
	//Creo archivo
	FILE* p;
	p = fopen("registros.dat", "ab");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		validarGrabado = false;
		return;
	}
	//-------Grabo el registro de memoria al archivo
	//Primero tenemos que validar si es la segunda vuelta, la primera no se valida, solo los espacios vacios.
	//Valido que no haya un DNI o CUIT igual o que no haya un espacio vacio
	posicionDNI = validarDNI(reg.dni); posicionCUIT = validarCUIT(reg.cuit);
	posicionFechaIngreso = validarFechas(reg); posicionFechaVencimiento = validarFechas(reg);
	//Las variables de tipo posicionALGO, sirven para usarlos a modo de bandera, que segun cada funcion, yo le di un codigo particular
	//Asi, verifico si se cumple tal o cual condicion para validar, DNI no repetido, CUIT no repetido, y las Fechas, etc.
	if (posicionCUIT == 1315 || posicionDNI == 1315 || posicionFechaIngreso == 1111 || posicionFechaVencimiento == 2222) {
		cout << "Ya existe ese DNI o CUIT, por favor, ingrese otro DNI o CUIT" << endl;
		cout << "O bien la Fecha de Ingreso/Vencimiento es invalida." << endl;
		anykey();
		return;
	}
	else {
		grabarRegistro(reg);
		if (validarGrabado == true) {
			cout << "Registros grabados en archivo correctamente!" << endl << endl;
		}
		else {
			cout << "No se pudo grabar. :)" << endl << endl;
		}
	}	
	fclose(p);
}
void grabarRegistro(Chofer registro) {
	FILE* p;
	p = fopen("registros.dat", "ab");
	if (p == NULL) {
		cout << "Error. :)" << endl;
		return;
	}
	fwrite(&registro, sizeof registro, 1, p);
	fclose(p);
	return;
}
// Baja
int bajaRegistro() {
	FILE* p;
	Chofer registro;
	int pos;
	char dnibusqueda[10];
	p = fopen("registros.dat", "rb+");
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
	p = fopen("registros.dat", "rb+");
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
			cin >> registro.vencimientoRegistro.dia;
			cout << "Mes: " << endl;
			cin >> registro.vencimientoRegistro.mes;
			cout << "Anio: " << endl;
			cin >> registro.vencimientoRegistro.anio;
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
		cout << "\tDia: " << registro.fechaingreso.dia << endl;
		cout << "\tMes: " << registro.fechaingreso.mes << endl;
		cout << "\tAnio: " << registro.fechaingreso.anio << endl;
		cout << "Fecha de vencimiento del registro: " << endl;
		cout << "\tDia: " << registro.vencimientoRegistro.dia << endl;
		cout << "\tMes: " << registro.vencimientoRegistro.mes << endl;
		cout << "\tAnio: " << registro.vencimientoRegistro.anio << endl;
		cout << "Tipo de registro (1-3): " << registro.tipoRegistro << endl;
		cout << "----------------------------------------" << endl;
	}
}
void listaRegistro() {
	FILE* p;
	Chofer registro;
	p = fopen("registros.dat", "rb");
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
	p = fopen("registros.dat", "rb+");
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