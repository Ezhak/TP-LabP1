#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include "chofer.h"
#include "viaje.h"

//Realizar backup
int contarRegistrosChoferes();
int contarRegistrosViajes();
void realizarBackupChoferes();
void realizarBackupViajes();

//Restaurar backup
int contarRegistrosChoferesBackup();
int contarRegistrosViajesBackup();
void restaurarBackupChoferes();
void restaurarBackupViajes();
//Cargar datos de inicio

# endif // CONFIGURACION_H