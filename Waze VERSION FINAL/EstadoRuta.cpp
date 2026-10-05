#include "EstadoRuta.h"

using namespace std;

EstadoRuta::EstadoRuta(string ruta, int congestion, bool disp)
    : nombreRuta(ruta), nivelCongestion(congestion), disponible(disp) {}

string EstadoRuta::getNombreRuta() const { return nombreRuta; }
int EstadoRuta::getNivelCongestion() const { return nivelCongestion; }
bool EstadoRuta::estaDisponible() const { return disponible; }
void EstadoRuta::setNivelCongestion(int congestion) { nivelCongestion = congestion; }
void EstadoRuta::setDisponible(bool disp) { disponible = disp; }
