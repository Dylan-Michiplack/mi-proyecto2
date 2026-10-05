#include "Archivos.h"
#include "Configuracion.h"
#include "Utilidades.h"
#include "HistorialTrafico.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

namespace {
int convertirAAnioNacimiento(const string& texto) {
    if (texto.empty()) return 0;

    string candidato = texto;
    size_t ultimaBarra = candidato.find_last_of('/');
    if (ultimaBarra != string::npos)
        candidato = candidato.substr(ultimaBarra + 1);

    try {
        int anio = stoi(candidato);
        if (anio >= 1900 && anio <= 2026) return anio;
    }
    catch (...) {
    }
    return 0;
}
}

void guardarUsuarios(const ListaSimple<Usuario>& usuarios) {
    ofstream archivo(ARCHIVO_USUARIOS);
    if (!archivo.is_open()) return;


    // Mathias Raul Grovas Ormachea
    usuarios.recorrerConLambda([&archivo](const Usuario& u) {
        archivo << u.getCorreo() << '|'
                << u.getUsuario() << '|'
                << u.getAnioNacimiento() << '|'
                << u.getContrasena() << '|'
                << u.getTelefono() << '\n';
    });
    archivo.close();
}

void cargarUsuarios(ListaSimple<Usuario>& usuarios) {
    ifstream archivo(ARCHIVO_USUARIOS);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        string correo, usuario, anioTexto, pass, telefono;
        stringstream ss(linea);
        getline(ss, correo, '|');
        getline(ss, usuario, '|');
        getline(ss, anioTexto, '|');
        getline(ss, pass, '|');
        getline(ss, telefono, '|');

        if (!usuario.empty()) {
            int anio = convertirAAnioNacimiento(anioTexto);
            usuarios.insertarFinal(Usuario(correo, usuario, anio, pass, telefono));
        }
    }
    archivo.close();
}

void guardarAdministradores(const ListaSimple<Administrador>& administradores) {
    ofstream archivo(ARCHIVO_ADMINISTRADORES);
    if (!archivo.is_open()) return;

    // Edgar Kevin Serna Poma
    administradores.recorrerConLambda([&archivo](const Administrador& a) {
        archivo << a.getCorreo() << '|'
                << a.getUsuario() << '|'
                << a.getContrasena() << '|'
                << a.getTelefono() << '\n';
    });
    archivo.close();
}

void cargarAdministradores(ListaSimple<Administrador>& administradores) {
    ifstream archivo(ARCHIVO_ADMINISTRADORES);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        string correo, usuario, pass, telefono;
        stringstream ss(linea);
        getline(ss, correo, '|');
        getline(ss, usuario, '|');
        getline(ss, pass, '|');
        getline(ss, telefono, '|');

        if (!usuario.empty())
            administradores.insertarFinal(Administrador(correo, usuario, pass, telefono));
    }
    archivo.close();
}

void guardarRutas(const ListaSimple<Ruta>& rutas) {
    ofstream archivo(ARCHIVO_RUTAS);
    if (!archivo.is_open()) return;


    // Dylan Jean Pierre Ybanez Mejia
    rutas.recorrerConLambda([&archivo](const Ruta& r) {
        archivo << r.getNombre() << '|'
                << r.getOrigen() << '|'
                << r.getDestino() << '|'
                << r.getDistanciaKm() << '|'
                << r.getTiempoMin() << '|';
        const auto& puntos = r.getPuntosPaso();
        for (size_t i = 0; i < puntos.size(); ++i) {
            if (i > 0) archivo << ';';
            archivo << puntos[i];
        }
        archivo << '\n';
    });
    archivo.close();
}

void cargarRutas(ListaSimple<Ruta>& rutas) {
    ifstream archivo(ARCHIVO_RUTAS);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        string nombre, origen, destino, distanciaTexto, tiempoTexto, puntosTexto;
        stringstream ss(linea);
        getline(ss, nombre, '|');
        getline(ss, origen, '|');
        getline(ss, destino, '|');
        getline(ss, distanciaTexto, '|');
        getline(ss, tiempoTexto, '|');
        getline(ss, puntosTexto);

        if (!nombre.empty() && !distanciaTexto.empty() && !tiempoTexto.empty()) {
            double distancia = atof(distanciaTexto.c_str());
            int tiempo = atoi(tiempoTexto.c_str());
            vector<string> puntos;
            string punto;
            stringstream listaPuntos(puntosTexto);
            while (getline(listaPuntos, punto, ';'))
                if (!punto.empty()) puntos.push_back(punto);
            rutas.insertarFinal(Ruta(nombre, origen, destino, distancia, tiempo, puntos));
        }
    }
    archivo.close();
}

void guardarPOI(const ListaDoble<PuntoInteres>& listaPOI) {
    ofstream archivo(ARCHIVO_POI);
    if (!archivo.is_open()) return;

   
    // Mathias Raul Grovas Ormachea
    listaPOI.recorrerAdelante([&archivo](const PuntoInteres& p) {
        archivo << p.getNombre() << '|' << p.getTipo() << '|' << p.getDistancia() << '\n';
    });
    archivo.close();
}

void cargarPOI(ListaDoble<PuntoInteres>& listaPOI) {
    ifstream archivo(ARCHIVO_POI);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        string nombre, tipo, distancia;
        stringstream ss(linea);
        getline(ss, nombre, '|');
        getline(ss, tipo, '|');
        getline(ss, distancia, '|');

        if (!nombre.empty()) listaPOI.insertarFinal(PuntoInteres(nombre, tipo, distancia));
    }
    archivo.close();
}

void guardarReportesPendientes(const Cola<ReporteTrafico>& colaReportes) {
    ofstream archivo(ARCHIVO_REPORTES);
    if (!archivo.is_open()) return;


    // Edgar Kevin Serna Poma
    colaReportes.recorrerConLambda([&archivo](const ReporteTrafico& r) {
        archivo << r.getTipo() << '|'
                << r.getUbicacion() << '|'
                << r.getGravedad() << '\n';
    });
    archivo.close();
}

void cargarReportesPendientes(Cola<ReporteTrafico>& colaReportes) {
    ifstream archivo(ARCHIVO_REPORTES);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        string tipo, ubicacion, gravedadTexto;
        stringstream ss(linea);
        getline(ss, tipo, '|');
        getline(ss, ubicacion, '|');
        getline(ss, gravedadTexto, '|');

        if (!tipo.empty() && !gravedadTexto.empty()) {
            colaReportes.enqueue(ReporteTrafico(tipo, ubicacion, atoi(gravedadTexto.c_str())));
        }
    }
    archivo.close();
}

void registrarEnHistorial(const ReporteTrafico& reporte, const string& estado) {
    ofstream archivo(ARCHIVO_HISTORIAL, ios::app);
    if (!archivo.is_open()) return;

    HistorialTrafico registro(fechaHoraActual(), estado, reporte);
    archivo << registro.getFechaHora() << '|'
            << registro.getEstado() << '|'
            << registro.getTipoReporte() << '|'
            << registro.getUbicacion() << '|'
            << registro.getGravedad() << '\n';
    archivo.close();
}

void mostrarHistorialTrafico() {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("          HISTORIAL DE TRAFICO               \n");
    cout << "=============================================\n\n";

    ifstream archivo(ARCHIVO_HISTORIAL);
    if (!archivo.is_open()) {
        cout << "[!] Aun no existe historial de trafico.\n";
        pausar();
        return;
    }

    string linea;
    int contador = 0;
    while (getline(archivo, linea)) {
        string fecha, estado, tipo, ubicacion, gravedad;
        stringstream ss(linea);
        getline(ss, fecha, '|');
        getline(ss, estado, '|');
        getline(ss, tipo, '|');
        getline(ss, ubicacion, '|');
        getline(ss, gravedad, '|');

        if (!tipo.empty()) {
            HistorialTrafico registro(fecha, estado, tipo, ubicacion, atoi(gravedad.c_str()));
            contador++;
            cout << contador << ". " << registro.getFechaHora() << " | " << registro.getEstado() << "\n";
            cout << "   [" << registro.getTipoReporte() << "] " << registro.getUbicacion()
                 << " | Congestion: " << registro.getGravedad() << "/5\n\n";
        }
    }
    archivo.close();

    if (contador == 0) cout << "[!] El historial se encuentra vacio.\n";
    pausar();
}
