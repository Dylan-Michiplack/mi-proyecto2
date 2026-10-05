#include "DatosIniciales.h"
#include "Archivos.h"
#include "Configuracion.h"
#include "Utilidades.h"
#include "Sede.h"
#include <fstream>

using namespace std;

void cargarRutasIniciales(ListaSimple<Ruta>& rutas) {
    if (archivoExiste(ARCHIVO_RUTAS)) return;

    // Todas las rutas utilizan solamente las cuatro sedes definidas para el avance.
    rutas.insertarFinal(Ruta("Ruta Panamericana", SEDE_VILLA, SEDE_MONTERRICO, 18.5, 29,
        {"Mall del Sur", "Tottus Atocongo", "Jockey Plaza"}));
    rutas.insertarFinal(Ruta("Ruta Evitamiento", SEDE_VILLA, SEDE_MONTERRICO, 20.1, 25,
        {"Puente Atocongo", "Metro San Borja", "Jockey Plaza"}));
    rutas.insertarFinal(Ruta("Ruta Costa Verde", SEDE_SAN_MIGUEL, SEDE_SAN_ISIDRO, 10.8, 22,
        {"Plaza San Miguel", "Parque Media Luna", "Real Plaza Salaverry"}));
    rutas.insertarFinal(Ruta("Ruta Javier Prado", SEDE_SAN_ISIDRO, SEDE_MONTERRICO, 13.4, 26,
        {"Clinica Ricardo Palma", "La Rambla San Borja", "Jockey Plaza"}));
    rutas.insertarFinal(Ruta("Ruta Circuito de Playas", SEDE_SAN_MIGUEL, SEDE_VILLA, 28.6, 42,
        {"Plaza San Miguel", "Larcomar", "Playa Agua Dulce"}));
    rutas.insertarFinal(Ruta("Ruta Via Expresa", SEDE_MONTERRICO, SEDE_SAN_ISIDRO, 12.0, 24,
        {"Jockey Plaza", "Estacion Angamos", "Centro Financiero"}));
    guardarRutas(rutas);
}

void cargarPOIIniciales(ListaDoble<PuntoInteres>& listaPOI) {
    if (archivoExiste(ARCHIVO_POI)) return;

  
    Sede villa(SEDE_VILLA, "Chorrillos", "");
    Sede monterrico(SEDE_MONTERRICO, "Santiago de Surco", "");
    Sede sanMiguel(SEDE_SAN_MIGUEL, "San Miguel", "");
    Sede sanIsidro(SEDE_SAN_ISIDRO, "San Isidro", "");

    listaPOI.insertarFinal(PuntoInteres(SEDE_VILLA, "Sede UPC", "Villa", villa));
    listaPOI.insertarFinal(PuntoInteres(SEDE_MONTERRICO, "Sede UPC", "Monterrico", monterrico));
    listaPOI.insertarFinal(PuntoInteres(SEDE_SAN_MIGUEL, "Sede UPC", "San Miguel", sanMiguel));
    listaPOI.insertarFinal(PuntoInteres(SEDE_SAN_ISIDRO, "Sede UPC", "San Isidro", sanIsidro));
    guardarPOI(listaPOI);
}

void cargarReportesIniciales(Cola<ReporteTrafico>& colaReportes) {
    if (archivoExiste(ARCHIVO_REPORTES)) return;

    Sede villa(SEDE_VILLA);
    Sede monterrico(SEDE_MONTERRICO);
    Sede sanMiguel(SEDE_SAN_MIGUEL);

    ReporteTrafico r1("Accidente", villa, 4);
    ReporteTrafico r2("Trafico Pesado", monterrico, 2);
    ReporteTrafico r3("Obras en via", sanMiguel, 5);

    colaReportes.enqueue(r1);
    colaReportes.enqueue(r2);
    colaReportes.enqueue(r3);
    guardarReportesPendientes(colaReportes);

    ifstream historial(ARCHIVO_HISTORIAL);
    bool historialExiste = historial.good();
    historial.close();
    if (!historialExiste) {
        registrarEnHistorial(r1, "REPORTE INICIAL");
        registrarEnHistorial(r2, "REPORTE INICIAL");
        registrarEnHistorial(r3, "REPORTE INICIAL");
    }
}
