#include "menu_configuracion.h"

void menuConfiguracion() {
	using namespace rlutil;
	using namespace std;

	int opcionConfiguracion;

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
			realizarBackupChoferes();
			anykey();
			break;
		case 2:
			cls();
			// restaurarBackup();
			anykey();
			break;
		case 3:
			cls();
			// cargarDatosInicio();
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

