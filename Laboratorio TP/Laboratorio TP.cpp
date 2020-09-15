#include <iostream>
#include "rlutil.h"
#include "chofer.h"

using namespace rlutil;
using namespace std;

int main(){
    int opcionPrincipal; int opcionChoferes;
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
            cls();
            anykey();
            break;
        case 3:
            cls();
            anykey();
            break;
        case 4:
            cls();
            anykey();
            break;
        case 0:
            cls();
            cout << "Adios" << endl;
            anykey();
            break;
        default:
            cls();
            cout << "Codigo erroneo" << endl;
            break;
        }
    } while (opcionPrincipal != 0);

    return 0;
}
