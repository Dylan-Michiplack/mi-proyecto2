#include "ReporteTrafico.h"
#include <iostream>

using namespace std;

ReporteTrafico::ReporteTrafico(string t, string u, int g)
    : tipo(t), ubicacion(u), gravedad(g) {}

ReporteTrafico::ReporteTrafico(string t, const Sede& u, int g)
    : tipo(t), ubicacion(u), gravedad(g) {}

void ReporteTrafico::mostrarInfo() const {
    cout << "  - [" << tipo << "] En: " << ubicacion.getNombre()
         << " | Congestion: " << gravedad << "/5\n";
}

string ReporteTrafico::getTipo() const { return tipo; }
string ReporteTrafico::getUbicacion() const { return ubicacion.getNombre(); }
int ReporteTrafico::getGravedad() const { return gravedad; }
const Sede& ReporteTrafico::getSede() const { return ubicacion; }
