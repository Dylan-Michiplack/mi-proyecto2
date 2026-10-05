#include "Ruta.h"
#include <iostream>
#include <iomanip>

using namespace std;

Ruta::Ruta(string n, string o, string d, double distancia, int tiempo,
           const vector<string>& puntos, const string& intermedia)
    : nombre(n), origen(o), destino(d), estado(n, 0, true),
      tramoPrincipal(n, "", distancia, 1), distanciaKm(distancia), tiempoMin(tiempo),
      puntosPaso(puntos), sedeIntermedia(intermedia) {}

Ruta::Ruta(string n, const Sede& o, const Sede& d,
           double distancia, int tiempo, const EstadoRuta& e,
           const TramoRuta& tramo, const vector<string>& puntos, const string& intermedia)
    : nombre(n), origen(o), destino(d), estado(e), tramoPrincipal(tramo),
      distanciaKm(distancia), tiempoMin(tiempo), puntosPaso(puntos), sedeIntermedia(intermedia) {}

string Ruta::getNombre() const { return nombre; }
string Ruta::getOrigen() const { return origen.getNombre(); }
string Ruta::getDestino() const { return destino.getNombre(); }
double Ruta::getDistanciaKm() const { return distanciaKm; }
int Ruta::getTiempoMin() const { return tiempoMin; }
const vector<string>& Ruta::getPuntosPaso() const { return puntosPaso; }
string Ruta::getSedeIntermedia() const { return sedeIntermedia; }
const Sede& Ruta::getSedeOrigen() const { return origen; }
const Sede& Ruta::getSedeDestino() const { return destino; }
const EstadoRuta& Ruta::getEstado() const { return estado; }
const TramoRuta& Ruta::getTramoPrincipal() const { return tramoPrincipal; }

void Ruta::mostrarInfo() const {
    cout << "  " << nombre << "\n";
    cout << "    Origen    : " << origen.getNombre() << "\n";
    if (!sedeIntermedia.empty())
        cout << "    Intermedia: " << sedeIntermedia << "\n";
    cout << "    Destino   : " << destino.getNombre() << "\n";
    cout << "    Distancia : " << fixed << setprecision(1) << distanciaKm << " km\n";
    cout << "    Tiempo    : " << tiempoMin << " min\n";
    if (!puntosPaso.empty()) {
        cout << "    Pasa por  : ";
        for (size_t i = 0; i < puntosPaso.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << puntosPaso[i];
        }
        cout << "\n";
    }
}
