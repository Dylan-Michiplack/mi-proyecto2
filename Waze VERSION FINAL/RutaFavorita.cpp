#include "RutaFavorita.h"

using namespace std;

RutaFavorita::RutaFavorita(string u, string nombreRuta)
    : usuarioRef(nullptr), usuarioTexto(u), ruta(nombreRuta) {}

RutaFavorita::RutaFavorita(const Usuario& u, const Ruta& r)
    : usuarioRef(&u), usuarioTexto(u.getUsuario()), ruta(r) {}

string RutaFavorita::getUsuario() const {
    return usuarioRef != nullptr ? usuarioRef->getUsuario() : usuarioTexto;
}
string RutaFavorita::getNombreRuta() const { return ruta.getNombre(); }
const Usuario* RutaFavorita::getUsuarioEntidad() const { return usuarioRef; }
const Ruta& RutaFavorita::getRutaEntidad() const { return ruta; }
