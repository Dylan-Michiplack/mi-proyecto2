#pragma once
#include <string>
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Ruta.h"
#include "ReporteTrafico.h"
#include "PuntoInteres.h"

void guardarUsuarios(const ListaSimple<Usuario>& usuarios);
void cargarUsuarios(ListaSimple<Usuario>& usuarios);
void guardarAdministradores(const ListaSimple<Administrador>& administradores);
void cargarAdministradores(ListaSimple<Administrador>& administradores);
void guardarRutas(const ListaSimple<Ruta>& rutas);
void cargarRutas(ListaSimple<Ruta>& rutas);
void guardarPOI(const ListaDoble<PuntoInteres>& listaPOI);
void cargarPOI(ListaDoble<PuntoInteres>& listaPOI);
void guardarReportesPendientes(const Cola<ReporteTrafico>& colaReportes);
void cargarReportesPendientes(Cola<ReporteTrafico>& colaReportes);
void registrarEnHistorial(const ReporteTrafico& reporte, const std::string& estado);
void mostrarHistorialTrafico();
