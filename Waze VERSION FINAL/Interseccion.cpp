#include "Interseccion.h"

using namespace std;

Interseccion::Interseccion(string a1, string a2, string ref)
    : avenidaUno(a1), avenidaDos(a2), referencia(ref) {}

Interseccion::Interseccion(const Avenida& a1, const Avenida& a2, string ref)
    : avenidaUno(a1), avenidaDos(a2), referencia(ref) {}

string Interseccion::getAvenidaUno() const { return avenidaUno.getNombre(); }
string Interseccion::getAvenidaDos() const { return avenidaDos.getNombre(); }
string Interseccion::getReferencia() const { return referencia; }
const Avenida& Interseccion::getAvenidaUnoEntidad() const { return avenidaUno; }
const Avenida& Interseccion::getAvenidaDosEntidad() const { return avenidaDos; }
