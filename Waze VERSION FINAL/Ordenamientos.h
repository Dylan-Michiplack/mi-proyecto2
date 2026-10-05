#pragma once
#include "Ruta.h"
#include "Usuario.h"
#include "ListaSimple.h"

// Edgar Kevin Serna Poma
int particionRutas(Ruta** arreglo, int low, int high);
void quickSortRutas(Ruta** arreglo, int low, int high);
void mostrarRutasOrdenadas(ListaSimple<Ruta>& rutas);

// Mathias Raul Grovas Ormachea
void countingSortUsuariosPorAnio(Usuario** arreglo, int n);
void mostrarUsuariosOrdenadosPorAnio(ListaSimple<Usuario>& usuarios);

// Dylan Jean Pierre Ybanez Mejia
void mergeRutasPorDistancia(Ruta** arreglo, int izquierda, int medio, int derecha);
void mergeSortRutasPorDistancia(Ruta** arreglo, int izquierda, int derecha);
void mostrarRutasOrdenadasPorDistancia(ListaSimple<Ruta>& rutas);
