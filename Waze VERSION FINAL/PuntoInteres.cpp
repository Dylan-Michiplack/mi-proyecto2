#include "PuntoInteres.h"
#include <iostream>

using namespace std;

PuntoInteres::PuntoInteres(string n, string t, string d)
    : nombre(n), tipo(t), distancia(d), sedeAsociada(n) {}

PuntoInteres::PuntoInteres(string n, string t, string d, const Sede& sede)
    : nombre(n), tipo(t), distancia(d), sedeAsociada(sede) {}

string PuntoInteres::getNombre() const { return nombre; }
string PuntoInteres::getTipo() const { return tipo; }
string PuntoInteres::getDistancia() const { return distancia; }
const Sede& PuntoInteres::getSede() const { return sedeAsociada; }

void PuntoInteres::mostrar() const {
    cout << "  [" << tipo << "] " << nombre << " (A " << distancia << ")\n";
}
