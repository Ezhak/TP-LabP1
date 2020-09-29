// ABML Chofer
#include "chofer.h"

using namespace std;

// Alta
void nuevoChofer() {
	Chofer reg;

	FILE* fp;
	fp = fopen("choferes.dat", "a+b");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	reg = cargarRegistroChofer();

	if (existeDNI(fp, reg.dni)) {
		cout << "DNI ya registrado." << endl;
		return;
	}

	if (existeCUIT(fp, reg.cuit)) {
		cout << "CUIT ya registrado." << endl;
		return;
	}

	if (compararFechaActual(reg.fecha_ingreso) < 0) {
		cout << "Fecha de ingreso inválida." << endl;
		return;
	}

	if (compararFechaActual(reg.fecha_vencimiento) > 0) {
		cout << "Fecha de vencimiento inválida." << endl;
		return;
	}

	if (!escribirRegistroChofer(reg))
		return;
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

	cout << "Telefono: ";
	cin.getline(registro.telefono, 15);

	cout << "Fecha de Ingreso: " << endl;
	cout << "Dia: ";
	cin >> registro.fecha_ingreso.dia;
	cout << "Mes: ";
	cin >> registro.fecha_ingreso.mes;
	cout << "Anio: ";
	cin >> registro.fecha_ingreso.anio;

	cout << "Fecha de vencimiento del registro: " << endl;
	cout << "Dia: ";
	cin >> registro.fecha_vencimiento.dia;
	cout << "Mes: ";
	cin >> registro.fecha_vencimiento.mes;
	cout << "Anio: ";
	cin >> registro.fecha_vencimiento.anio;

	cout << "Tipo de registro (1-3): ";
	cin >> registro.tipoRegistro;

	cout << "Propietario del auto: ";
	cin >> registro.propietarioAuto;

	registro.estado = true;
	return registro;
}

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
			return true;
	}

	return false;
}

bool escribirRegistroChofer(Chofer registro) {
	FILE* fp;

	fp = fopen("choferes.dat", "ab");
	if (!fp) {
		cout << "Error al abrir el archivo!" << endl;
		return false;
	}
	
	fwrite(&registro, sizeof registro, 1, fp);
	if (ferror(fp)) {
		cout << "Error al escribir el archivo!" << endl;
		fclose(fp);
		return false;
	}

	fclose(fp);
	return true;
}

// Baja
void eliminarChofer() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	char dnibusqueda[10];
	int pos = 0;

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	do {
		cin.ignore();
		cout << "Ingrese el DNI a dar de baja: ";
		cin.getline(dnibusqueda, 10);
		occurrence = strpbrk(dnibusqueda, " \t");
	} while (occurrence || !dnibusqueda[0]);

	while (fread(&registro, sizeof registro, 1, fp)) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado) {
			registro.estado = false;

			// fseek pone la posición del archivo sobre el
			// registro encontrado.
			//
			// Desde el inicio:
			//
			//     pos * sizeof registro + SEEK_SET
			//                             (siempre 0)
			//
			// Desde el actual (fread() asigna y avanza, por lo
			// que hay que restar un registro):
			//
			//     -pos * sizeof registro + SEEK_CUR
			//                              (actual)
			//
			// Es útil dependiendo el tamaño del archivo, no
			// queremos reposicionar empezando del comienzo si
			// llegamos casi al final, y viceversa.
			fseek(fp, pos * sizeof registro, 0);
			fwrite(&registro, sizeof registro, 1, fp);

			cout << "Chofer eliminado. Registro dado de baja." << endl;
			fclose(fp);
			return;
		}
		pos++;
	}

	cout << "No se pudo dar de baja. :)" << endl;

	fclose(fp);
	return;
}

// Modificación
void modificarChofer() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	int pos;
	char dnibusqueda[10];

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error al escribir archivo!" << endl;
		return;
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
			return;
		}
		pos++;
	}

	cout << "No existe ese DNI" << endl;

	fclose(fp);
	return;
}

// Lista
void mostrarRegistroChofer(Chofer registro) {
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
	cout << "Propietario: " << registro.propietarioAuto << endl;
	cout << "----------------------------------------" << endl;
}

void listarChoferDNI() {
	FILE* fp;
	Chofer registro;
	char* occurrence;
	char dnibusqueda[10];

	fp = fopen("choferes.dat", "rb+");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	do {
		cin.ignore();
		cout << "Ingrese el DNI:" << endl;
		cin.getline(dnibusqueda, 10);
		occurrence = strpbrk(dnibusqueda, " \t");
	} while (occurrence || !dnibusqueda[0]);

	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		if (!strcmp(registro.dni, dnibusqueda) && registro.estado) {  //Cuando encuentra coincidencia entre el DNI dado con registro.dni
			cout << endl << "----------------------------------------" << endl;     //Te muestra el registro que coincida con el DNI.
			mostrarRegistroChofer(registro);
			fclose(fp);
			return;
		}
	}

	cout << "No existe ese DNI" << endl;

	fclose(fp);
	return;
}

void listarChoferes() {
	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.dat", "rb");
	if (!fp) {
		cout << "Error al abrir archivo!" << endl;
		return;
	}

	cin.ignore();
	while (fread(&registro, sizeof registro, 1, fp)) {
		if (registro.estado)
			mostrarRegistroChofer(registro);
	}

	fclose(fp);
}

