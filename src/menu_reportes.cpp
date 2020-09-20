#include "menu_reportes.h"

void menuReportes() {
	using namespace rlutil;
	using namespace std;

	int opcionReportes;
	do {
		cls();

		cout << "MENÚ REPORTES" << endl;
		cout << "-------------" << endl;
		cout << "1) REPORTE 1" << endl;
		cout << "2) REPORTE 2" << endl;
		cout << "3) REPORTE 3" << endl;
		cout << "-------------" << endl;
		cout << "0) VOLVER AL MENÚ PRINCIPAL" << endl << endl;

		cin >> opcionReportes;

		switch (opcionReportes) {
		case 1:
			cls();
			break;
		case 2:
			cls();
			break;
		case 3:
			cls();
			break;
		case 0:
			break;
		default:
			cin.ignore();
			cout << "Opción inválida." << endl;
			anykey();
			break;
		}
	} while (opcionReportes);
}
