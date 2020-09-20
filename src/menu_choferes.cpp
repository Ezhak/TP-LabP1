#include "menu_choferes.h"

void menuChoferes() {
	using namespace rlutil;
	using namespace std;

	int opcionChoferes;

	do {
		cls();

		cout << "MENÚ CHOFERES" << endl;
		cout << "-------------" << endl;
		cout << "1) NUEVO CHOFER" << endl;
		cout << "2) MODIFICAR CHOFER" << endl;
		cout << "3) LISTAR CHOFER POR DNI" << endl;
		cout << "4) LISTAR TODOS LOS CHOFERES" << endl;
		cout << "5) ELIMINAR CHOFER" << endl;
		cout << "-------------" << endl;
		cout << "0) VOLVER AL MENÚ PRINCIPAL" << endl << endl;

		cin >> opcionChoferes;

		switch (opcionChoferes) {
		case 1:
			cls();
			nuevoChofer();
			anykey();
			break;
		case 2:
			cls();
			modificarChofer();
			anykey();
			break;
		case 3:
			cls();
			listarChoferDNI();
			anykey();
			break;
		case 4:
			cls();
			listarChoferes();
			anykey();
			break;
		case 5:
			cls();
			eliminarChofer();
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
	} while (opcionChoferes);
}

