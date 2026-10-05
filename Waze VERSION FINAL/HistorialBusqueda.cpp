#include "HistorialBusqueda.h"

using namespace std;

HistorialBusqueda::HistorialBusqueda(string u, string o, string d, string fecha)
    : busqueda(u, o, d, ""), fechaHora(fecha) {}

HistorialBusqueda::HistorialBusqueda(const BusquedaRuta& b, string fecha)
    : busqueda(b), fechaHora(fecha) {}

string HistorialBusqueda::getUsuario() const { return busqueda.getUsuario(); }
string HistorialBusqueda::getOrigen() const { return busqueda.getOrigen(); }
string HistorialBusqueda::getDestino() const { return busqueda.getDestino(); }
string HistorialBusqueda::getFechaHora() const { return fechaHora; }
const BusquedaRuta& HistorialBusqueda::getBusqueda() const { return busqueda; }
