#include "configuracion.h"

using namespace std;

//Realizar backup
int contarRegistrosChoferes() {
	int cantidad = 0;

	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.dat", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

int contarRegistrosViajes() {
	int cantidad = 0;

	FILE* fp;
	Viaje registro;

	fp = fopen("viajes.dat", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

int contarRegistrosChoferesInicio() {
	int cantidad = 0;

	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.ini", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

int contarRegistrosViajesInicio() {
	int cantidad = 0;

	FILE* fp;
	Viaje registro;

	fp = fopen("viajes.ini", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

void realizarBackupChoferes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; 
	int it = 0;
	Chofer registro; 
	Chofer registrobackup;
	Chofer* vectoresRegistro;

	fp = fopen("choferes.dat", "rb");
	if (!fp) return;

	cantidadRegistros = contarRegistrosChoferes();

	//Necesitamos contar cuantos registros hay, para luego crear un vector dinamico y laburar ahi los registros para finalmente crear un backup.
	//Para ello se utiliz contarRegistrosChoferes();
	vectoresRegistro = new Chofer[cantidadRegistros]; //Asignacion de memoria dinamica a un vector, asi pasamos los registros del archivo a la memoria.

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	//Una vez pasados los registros del archivo a la memoria (en un vector)
	//Procedo a grabarlo en el backup

	fp2 = fopen("choferes.bkp", "w+b");

	if (!fp2) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Backup de 'choferes.dat' hecho." << endl;

	/**  //Este bloque lo use para verificar que el backup funcione, basicamente muestro el backup.
	FILE* fp3;
	Chofer ayuda;
	fp3 = fopen("choferes.bkp", "rb");
	if (fp3 == NULL) return;
	while (fread(&ayuda, sizeof ayuda, 1, fp3) == 1) {
		mostrarRegistro(ayuda);
	}
	fclose(fp2);
	**/

	delete[]vectoresRegistro;
	return;
}

void realizarBackupViajes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; 
	int it = 0; int opcion;
	Viaje registro; 
	Viaje registrobackup;
	Viaje* vectoresRegistro;

	fp = fopen("viajes.dat", "rb");

	if (!fp) return;

	cantidadRegistros = contarRegistrosViajes();

	//Necesitamos contar cuantos registros hay, para luego crear un vector dinamico y laburar ahi los registros para finalmente crear un backup.
	//Para ello se utiliz contarRegistrosViajes();
	vectoresRegistro = new Viaje[cantidadRegistros]; //Asignacion de memoria dinamica a un vector, asi pasamos los registros del archivo a la memoria.

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	//Una vez pasados los registros del archivo a la memoria (en un vector)
	//Procedo a grabarlo en el backup

	fp2 = fopen("viajes.bkp", "w+b");

	if (!fp2) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Backup de 'viajes.dat' hecho." << endl;

	delete[]vectoresRegistro;
	return;
}
//Restaurar backup

int contarRegistrosChoferesBackup() {
	int cantidad = 0;

	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.bkp", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

int contarRegistrosViajesBackup() {
	int cantidad = 0;

	FILE* fp;
	Viaje registro;

	fp = fopen("viajes.bkp", "rb");
	if (!fp) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}

void restaurarBackupChoferes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; int it = 0;
	Chofer registro; Chofer registrobackup;
	Chofer* vectoresRegistro;

	fp = fopen("choferes.bkp", "rb");

	if (!fp) return;

	cantidadRegistros = contarRegistrosChoferesBackup();

	//Necesitamos contar cuantos registros hay, para luego crear un vector dinamico y laburar ahi los registros para finalmente crear un backup.
	//Para ello se utiliz contarRegistrosChoferesBackup();
	vectoresRegistro = new Chofer[cantidadRegistros]; //Asignacion de memoria dinamica a un vector, asi pasamos los registros del archivo a la memoria.

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	//Una vez pasados los registros del archivo a la memoria (en un vector)
	//Procedo a grabarlo en el archivo original

	fp2 = fopen("choferes.dat", "w+b");
	if (fp2 == NULL) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Backup de 'choferes.dat' restaurado." << endl;

	delete[]vectoresRegistro;
	return;
}

void restaurarBackupViajes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; 
	int it = 0; int opcion;
	Viaje registro; 
	Viaje registrobackup;
	Viaje* vectoresRegistro;

	fp = fopen("viajes.bkp", "rb");

	if (!fp) return;

	cantidadRegistros = contarRegistrosViajesBackup();

	//Necesitamos contar cuantos registros hay, para luego crear un vector dinamico y laburar ahi los registros para finalmente crear un backup.
	//Para ello se utiliz contarRegistrosViajesBackup();
	vectoresRegistro = new Viaje[cantidadRegistros]; //Asignacion de memoria dinamica a un vector, asi pasamos los registros del archivo a la memoria.

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	//Una vez pasados los registros del archivo a la memoria (en un vector)
	//Procedo a grabarlo en el archivo original

	fp2 = fopen("viajes.dat", "w+b");

	if (!fp2) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Backup de 'viajes.dat' hecho." << endl;

	delete[]vectoresRegistro;
	return;

}
//Cargar datos de inicio

void cargarDatosInicioChoferes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; int it = 0;
	Chofer registro; Chofer registrobackup;
	Chofer* vectoresRegistro;

	fp = fopen("choferes.ini", "rb");

	if (!fp) return;

	cantidadRegistros = contarRegistrosChoferesInicio();

	vectoresRegistro = new Chofer[cantidadRegistros];

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	fp2 = fopen("choferes.dat", "w+b");
	if (fp2 == NULL) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Carga de datos de inicio de 'choferes.dat' realizado." << endl;

	delete[]vectoresRegistro;
	return;
}

void cargarDatosInicioViajes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros;
	int it = 0; int opcion;
	Viaje registro;
	Viaje registrobackup;
	Viaje* vectoresRegistro;

	fp = fopen("viajes.ini", "rb");

	if (!fp) return;

	cantidadRegistros = contarRegistrosViajesInicio();

	vectoresRegistro = new Viaje[cantidadRegistros];

	if (!vectoresRegistro) {
		cout << "Error memoria :)" << endl;
		return;
	}
	while (fread(&registro, sizeof registro, 1, fp) == 1) {
		vectoresRegistro[it] = registro;
		it++;
	}
	fclose(fp);

	fp2 = fopen("viajes.dat", "w+b");

	if (!fp2) return;

	fwrite(vectoresRegistro, sizeof registrobackup, cantidadRegistros, fp2);
	fclose(fp2);

	cout << endl << "Carga de datos de inicio de 'viajes.dat' realizado." << endl;

	delete[]vectoresRegistro;
	return;
}
