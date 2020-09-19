#pragma once
#include "chofer.h"
#include "viajes.h"

using namespace std;
using namespace rlutil;

//Realizar backup
int contarRegistrosChoferes() {
	int cantidad = 0;

	FILE* fp;
	Chofer registro;

	fp = fopen("choferes.dat", "rb");
	if (fp == NULL) return -1;

	fseek(fp, 0, 2);
	cantidad = ftell(fp) / sizeof registro;
	fclose(fp);

	return cantidad;
}
void realizarBackupChoferes() {
	FILE* fp; FILE* fp2;
	int cantidadRegistros; int it = 0;
	Chofer registro; Chofer registrobackup;
	Chofer* vectoresRegistro;

	fp = fopen("choferes.dat", "rb");
	if (fp == NULL) return;
	cantidadRegistros = contarRegistrosChoferes();
	//Necesitamos contar cuantos registros hay, para luego crear un vector dinamico y laburar ahi los registros para fianalmente crear un backup.
	//Para ello se utiliz contarRegistros();
	vectoresRegistro = new Chofer[cantidadRegistros]; //Asignacion de memoria dinamica a un vector, asi pasamos los registros del archivo a la memoria.
	if (vectoresRegistro == NULL) {
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

	fp2 = fopen("choferes.bkp", "a+b");
	if (fp2 == NULL) return;

	for (int j = 0; j < cantidadRegistros; j++){
		fwrite(&vectoresRegistro[j], sizeof registrobackup, 1, fp2);
	}
	fclose(fp2);
	cout << endl <<"Backup hecho." << endl;

	delete []vectoresRegistro;
	anykey();
}
void realizarBackupViajes() {

	anykey();
}
//Restaurar backup

//Cargar datos de inicio