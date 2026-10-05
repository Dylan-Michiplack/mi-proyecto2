#include "TramoRuta.h"

using namespace std;

TramoRuta::TramoRuta(string ruta, string av, double distancia, int pos)
    : nombreRuta(ruta), avenida(av), interseccion(), distanciaKm(distancia), orden(pos) {}

TramoRuta::TramoRuta(string ruta, const Avenida& av, const Interseccion& inter,
                     double distancia, int pos)
    : nombreRuta(ruta), avenida(av), interseccion(inter), distanciaKm(distancia), orden(pos) {}

string TramoRuta::getNombreRuta() const { return nombreRuta; }
string TramoRuta::getAvenida() const { return avenida.getNombre(); }
double TramoRuta::getDistanciaKm() const { return distanciaKm; }
int TramoRuta::getOrden() const { return orden; }
const Avenida& TramoRuta::getAvenidaEntidad() const { return avenida; }
const Interseccion& TramoRuta::getInterseccion() const { return interseccion; }
