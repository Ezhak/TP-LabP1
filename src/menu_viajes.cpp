#include "menu_viajes.h"

void menuViajes() {
	using namespace rlutil;
	using namespace std;

	int opcionViajes;

	do {
		cls();

		cout << "MENÚ VIAJES" << endl;
		cout << "--------------" << endl;
		cout << "1) NUEVO VIAJE" << endl;
		cout << "2) LISTAR VIAJE POR IDVIAJE" << endl;
		cout << "3) LISTAR TODOS LOS VIAJES" << endl;
		cout << "4) ELIMINAR VIAJE" << endl;
		cout << "--------------" << endl;
		cout << "0) VOLVER AL MENÚ PRINCIPAL" << endl << endl;

		cin >> opcionViajes;

		switch (opcionViajes) {
		case 1:
			cls();
			nuevoViaje();
			break;
		case 2:
			cls();
			listarViajeID();
			break;
		case 3:
			cls();
			listarViajes();
			break;
		case 4:
			cls();
			// eliminarViaje();
			break;
		case 0:
			break;
		default:
			cin.ignore();
			cout << "Opción inválida." << endl;
			anykey();
			break;
		}
	} while (opcionViajes);
}
