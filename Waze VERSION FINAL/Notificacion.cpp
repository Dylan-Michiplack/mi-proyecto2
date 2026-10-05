#include "Notificacion.h"

using namespace std;

Notificacion::Notificacion(string u, string m, string ubic, bool estado)
    : destinatario(nullptr), usuarioTexto(u), mensaje(m),
      reporte("Aviso", ubic, 0), leida(estado) {}

Notificacion::Notificacion(const Usuario& u, string m, const ReporteTrafico& r, bool estado)
    : destinatario(&u), usuarioTexto(u.getUsuario()), mensaje(m), reporte(r), leida(estado) {}

string Notificacion::getUsuario() const {
    return destinatario != nullptr ? destinatario->getUsuario() : usuarioTexto;
}
string Notificacion::getMensaje() const { return mensaje; }
string Notificacion::getUbicacion() const { return reporte.getUbicacion(); }
bool Notificacion::estaLeida() const { return leida; }
const Usuario* Notificacion::getDestinatario() const { return destinatario; }
const ReporteTrafico& Notificacion::getReporte() const { return reporte; }
void Notificacion::marcarComoLeida() { leida = true; }
