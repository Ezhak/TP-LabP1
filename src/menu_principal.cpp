#include "menu_principal.h"
#include "menu_choferes.h"
#include "menu_viajes.h"
#include "menu_reportes.h"
#include "menu_configuracion.h"

void menuPrincipal() {
	using namespace rlutil;
	using namespace std;

	int opcionPrincipal;

	cls();
	setColor(LIGHTCYAN);
	do {
		cls();

		cout << "MENÚ PRINCIPAL" << endl;
		cout << "--------------" << endl;
		cout << "1) CHOFERES" << endl;
		cout << "2) VIAJES" << endl;
		cout << "3) REPORTES" << endl;
		cout << "4) CONFIGURACIÓN" << endl;
		cout << "--------------" << endl;
		cout << "0) SALIR DEL PROGRAMA" << endl << endl;

		cin >> opcionPrincipal;

		switch (opcionPrincipal) {
		case 1:
			menuChoferes();
			break;
		case 2:
			menuViajes();
			break;
		case 3:
			menuReportes();
			break;
		case 4:
			menuConfiguracion();
			break;
		case 0:
			cout << "Saliendo del programa de gestión..." << endl;
			resetColor();
			break;
		default:
			cin.ignore();
			cout << "Opción inválida." << endl;
			anykey();
			break;
		}
	} while (opcionPrincipal);
}
	
