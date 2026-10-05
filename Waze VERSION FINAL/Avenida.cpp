#include "Avenida.h"

using namespace std;

Avenida::Avenida(string n, string d)
    : nombre(n), distrito(d) {}

string Avenida::getNombre() const { return nombre; }
string Avenida::getDistrito() const { return distrito; }
