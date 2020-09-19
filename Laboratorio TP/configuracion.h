#pragma once
#include "chofer.h"
#include "viajes.h"

using namespace std;
using namespace rlutil;

//Realizar backup
void realizarBackup() {
	FILE* p;
	Chofer registro;

	//Backup de choferes
	p = fopen("choferes.dat", "rb");
	if (p == NULL) return;
	


	fclose(p);

	//Backup de viajes

	p = fopen("viajes.dat", "rb");
	if (p == NULL) return;

	fclose(p);

	anykey();
}
//Restaurar backup

//Cargar datos de inicio