#include <iostream>
#include "rlutil.h"
#include "chofer.h"
#include "configuracion.h"

using namespace rlutil;
using namespace std;

int main(){
    int opcionPrincipal; int opcionChoferes; int opcionViajes; int opcionReportes; int opcionConfiguracion;
    cls(); setColor(LIGHTCYAN);
    do {
        cls();
        cout << "Menu Principal" << endl;
        cout << "--------------" << endl;
        cout << "1) Choferes" << endl;
        cout << "2) Viajes" << endl;
        cout << "3) Reportes" << endl;
        cout << "4) Configuracion" << endl;
        cout << "--------------" << endl;
        cout << "0) Salir del programa" << endl << endl;
        cin >> opcionPrincipal;
        switch (opcionPrincipal) {
        case 1:
            do {
                cls();
                cout << "Menu Choferes" << endl;
                cout << "--------------" << endl;
                cout << "1) Nuevo Chofer" << endl;
                cout << "2) Modificar Chofer" << endl;
                cout << "3) Listar Chofer por DNI" << endl;
                cout << "4) Listar todos los choferes" << endl;
                cout << "5) Eliminar Chofer" << endl;
                cout << "--------------" << endl;
                cout << "0) Salir del programa" << endl << endl;
                cin >> opcionChoferes;
                switch (opcionChoferes) {
                case 1:
                    cls();
                    altaRegistro();
                    break;
                case 2:
                    cls();
                    modificarRegistro();
                    anykey();
                    break;
                case 3:
                    cls();
                    listaporDNI();
                    anykey();
                    break;
                case 4:
                    cls();
                    listaRegistro();
                    break;
                case 5:
                    cls();
                    bajaRegistro();
                    anykey();
                    break;
                case 0:
                    break;
                default:
                    cls();
                    cout << "Codigo erroneo" << endl;
                    anykey();
                    break;
                }
            }while(opcionChoferes!=0);
            break;
        case 2:
            do {
                cls();
                cout << "Menu Viajes" << endl;
                cout << "--------------" << endl;
                cout << "1) Nuevo Viaje" << endl;
                cout << "2) Listar Viaje por IDViaje" << endl;
                cout << "3) Listar todos los viajes" << endl;
                cout << "4) Eliminar viaje" << endl;
                cout << "--------------" << endl;
                cout << "0) Salir del programa" << endl << endl;
                cin >> opcionViajes;
                switch (opcionViajes) {
                case 1:
                    cls();
                    
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
                    cout << "Codigo erroneo" << endl;
                    anykey();
                    break;
                }
            } while (opcionViajes != 0);
            cls();
            anykey();
            break;
        case 3:
            do {
                cls();
                cout << "Menu Reportes" << endl;
                cout << "--------------" << endl;
                cout << "1) Reporte 1" << endl;
                cout << "2) Reporte 2" << endl;
                cout << "3) Reporte 3" << endl;
                cout << "--------------" << endl;
                cout << "0) Salir del programa" << endl << endl;
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
                    cout << "Codigo erroneo" << endl;
                    anykey();
                    break;
                }
            } while (opcionReportes != 0);
            cls();
            anykey();
            break;
        case 4:
            do {
                cls();
                cout << "Menu Configuracion" << endl;
                cout << "--------------" << endl;
                cout << "1) Realizar Backup" << endl;
                cout << "2) Restaurar Backup" << endl;
                cout << "3) Cargar datos de Inicio" << endl;
                cout << "--------------" << endl;
                cout << "0) Salir del programa" << endl << endl;
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
                    cout << "Codigo erroneo" << endl;
                    anykey();
                    break;
                }
            } while (opcionConfiguracion != 0);
            break;
        case 0:
            cls();
            cout << "Adios" << endl;
            break;
        default:
            cls();
            cout << "Codigo erroneo" << endl;
            break;
        }
    } while (opcionPrincipal != 0);

    return 0;
}
