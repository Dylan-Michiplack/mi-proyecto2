#include "Sede.h"

using namespace std;

Sede::Sede(string n, string d, string dir)
    : nombre(n), distrito(d), direccion(dir) {}

string Sede::getNombre() const { return nombre; }
string Sede::getDistrito() const { return distrito; }
string Sede::getDireccion() const { return direccion; }
