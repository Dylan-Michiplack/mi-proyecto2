#pragma once
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "Ruta.h"
#include "PuntoInteres.h"
#include "ReporteTrafico.h"

void cargarRutasIniciales(ListaSimple<Ruta>& rutas);
void cargarPOIIniciales(ListaDoble<PuntoInteres>& listaPOI);
void cargarReportesIniciales(Cola<ReporteTrafico>& colaReportes);
