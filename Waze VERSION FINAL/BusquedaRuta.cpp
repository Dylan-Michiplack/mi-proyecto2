#include "BusquedaRuta.h"

using namespace std;

BusquedaRuta::BusquedaRuta(string u, string o, string d, string ruta)
    : usuarioRef(nullptr), usuarioTexto(u), origen(o), destino(d),
      rutaSeleccionada(ruta, o, d, 0.0, 0), tieneRuta(!ruta.empty()) {}

BusquedaRuta::BusquedaRuta(const Usuario& u, const Sede& o, const Sede& d)
    : usuarioRef(&u), usuarioTexto(u.getUsuario()), origen(o), destino(d),
      rutaSeleccionada(), tieneRuta(false) {}

BusquedaRuta::BusquedaRuta(const Usuario& u, const Sede& o, const Sede& d, const Ruta& ruta)
    : usuarioRef(&u), usuarioTexto(u.getUsuario()), origen(o), destino(d),
      rutaSeleccionada(ruta), tieneRuta(true) {}

string BusquedaRuta::getUsuario() const {
    return usuarioRef != nullptr ? usuarioRef->getUsuario() : usuarioTexto;
}
string BusquedaRuta::getOrigen() const { return origen.getNombre(); }
string BusquedaRuta::getDestino() const { return destino.getNombre(); }
string BusquedaRuta::getRutaSeleccionada() const { return tieneRuta ? rutaSeleccionada.getNombre() : ""; }
const Usuario* BusquedaRuta::getUsuarioEntidad() const { return usuarioRef; }
const Sede& BusquedaRuta::getSedeOrigen() const { return origen; }
const Sede& BusquedaRuta::getSedeDestino() const { return destino; }
const Ruta* BusquedaRuta::getRutaSeleccionadaEntidad() const { return tieneRuta ? &rutaSeleccionada : nullptr; }
