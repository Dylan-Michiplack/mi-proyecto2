#include "HistorialTrafico.h"

using namespace std;

HistorialTrafico::HistorialTrafico(string fecha, string e, string tipo, string u, int g)
    : fechaHora(fecha), estado(e), reporte(tipo, u, g) {}

HistorialTrafico::HistorialTrafico(string fecha, string e, const ReporteTrafico& r)
    : fechaHora(fecha), estado(e), reporte(r) {}

string HistorialTrafico::getFechaHora() const { return fechaHora; }
string HistorialTrafico::getEstado() const { return estado; }
string HistorialTrafico::getTipoReporte() const { return reporte.getTipo(); }
string HistorialTrafico::getUbicacion() const { return reporte.getUbicacion(); }
int HistorialTrafico::getGravedad() const { return reporte.getGravedad(); }
const ReporteTrafico& HistorialTrafico::getReporte() const { return reporte; }
