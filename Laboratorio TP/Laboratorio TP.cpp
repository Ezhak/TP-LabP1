#include <iostream>
#include "rlutil.h"
#include "configuracion.h"
#include "chofer.h"
#include "viajes.h"

using namespace rlutil;
using namespace std;

int main(){
	int opcionPrincipal;
	int opcionChoferes;
	int opcionViajes;
	int opcionReportes;
	int opcionConfiguracion;

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
				cout << "0) SALIR DEL PROGRAMA" << endl << endl;

				cin >> opcionChoferes;

				switch (opcionChoferes) {
				case 1:
					cls();
					nuevoChofer();
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
					break;
				case 5:
					cls();
					eliminarChofer();
					anykey();
					break;
				case 0:
					break;
				default:
					cls();
					cout << "Opción inválida." << endl;
					anykey();
					break;
				}
			} while (opcionChoferes);
			break;
		case 2:
			do {
				cls();

				cout << "MENÚ VIAJES" << endl;
				cout << "--------------" << endl;
				cout << "1) NUEVO VIAJE" << endl;
				cout << "2) LISTAR VIAJE POR IDVIAJE" << endl;
				cout << "3) LISTAR TODOS LOS VIAJES" << endl;
				cout << "4) Eliminar viaje" << endl;
				cout << "--------------" << endl;
				cout << "0) SALIR DEL PROGRAMA" << endl << endl;

				cin >> opcionViajes;

				switch (opcionViajes) {
				case 1:
					cls();
					nuevoViaje();
					break;
				case 2:
					cls();
					anykey();
					break;
				case 3:
					cls();
					anykey();
					break;
				case 4:
					cls();
					break;
				case 0:
					break;
				default:
					cls();
					cout << "Opción inválida." << endl;
					anykey();
					break;
				}
			} while (opcionViajes);

			cls();
			anykey();
			break;
		case 3:
			do {
				cls();

				cout << "MENÚ REPORTES" << endl;
				cout << "-------------" << endl;
				cout << "1) REPORTE 1" << endl;
				cout << "2) REPORTE 2" << endl;
				cout << "3) REPORTE 3" << endl;
				cout << "-------------" << endl;
				cout << "0) SALIR DEL PROGRAMA" << endl << endl;

				cin >> opcionReportes;

				switch (opcionReportes) {
				case 1:
					cls();
					anykey();
					break;
				case 2:
					cls();
					anykey();
					break;
				case 3:
					cls();
					anykey();
					break;
				case 0:
					break;
				default:
					cls();
					cout << "Opción inválida." << endl;
					anykey();
					break;
				}
			} while (opcionReportes);

			cls();
			anykey();
			break;
		case 4:
			do {
				cls();

				cout << "MENÚ CONFIGURACIÓN" << endl;
				cout << "------------------" << endl;
				cout << "1) REALIZAR BACKUP" << endl;
				cout << "2) RESTAURAR BACKUP" << endl;
				cout << "3) CARGAR DATOS DE INICIO" << endl;
				cout << "------------------" << endl;
				cout << "0) SALIR DEL PROGRAMA" << endl << endl;

				cin >> opcionConfiguracion;

				switch (opcionConfiguracion) {
				case 1:
					cls();
					realizarBackupChoferes();
					anykey();
					break;
				case 2:
					cls();
					anykey();
					break;
				case 3:
					cls();
					anykey();
					break;
				case 0:
					break;
				default:
					cls();
					cout << "Opción inválida." << endl;
					anykey();
					break;
				}
			} while (opcionConfiguracion);
			break;
		case 0:
			cls();
			cout << "Adiós." << endl;
			resetColor();
			break;
		default:
			cls();
			cout << "Opción inválida." << endl;
			break;
		}
	} while (opcionPrincipal);
	
	return 0;
}
