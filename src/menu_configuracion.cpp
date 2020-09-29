#include "menu_configuracion.h"

void menuConfiguracion() {
	using namespace rlutil;
	using namespace std;

	int opcionConfiguracion;
	int opcionBackup;
	int opcionInicio;

	do {
		cls();

		cout << "MENÚ CONFIGURACIÓN" << endl;
		cout << "------------------" << endl;
		cout << "1) REALIZAR BACKUP" << endl;
		cout << "2) RESTAURAR BACKUP" << endl;
		cout << "3) CARGAR DATOS DE INICIO" << endl;
		cout << "------------------" << endl;
		cout << "0) VOLVER AL MENÚ PRINCIPAL" << endl << endl;

		cin >> opcionConfiguracion;

		switch (opcionConfiguracion) {
		case 1:
			cls();
			cout << "Desea realizar un backup del sistema?" << endl;
			cout << "1. Si                           2. No" << endl;
			cin >> opcionBackup;
			if (opcionBackup == 2) return;
			realizarBackupChoferes();
			realizarBackupViajes();
			anykey();
			break;
		case 2:
			cls();
			opcionBackup = 0;
			cout << "Desea restaurar el backup al sistema?" << endl;
			cout << "1. Si                           2. No" << endl;
			cin >> opcionBackup;
			if (opcionBackup == 2) return;
			restaurarBackupChoferes();
			restaurarBackupViajes();
			anykey();
			break;
		case 3:
			cls();
			opcionInicio = 0;
			cout << "Desea cargar los datos de inicio al sistema?" << endl;
			cout << "1. Si                           2. No" << endl;
			cin >> opcionInicio;
			if (opcionInicio == 2) return;
			cargarDatosInicioChoferes();
			cargarDatosInicioViajes();
			anykey();
			break;
		case 0:
			break;
		default:
			cin.ignore();
			cout << "Opción inválida." << endl;
			anykey();
			break;
		}
	} while (opcionConfiguracion);
}
