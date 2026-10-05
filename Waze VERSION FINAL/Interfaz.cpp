#include "Interfaz.h"
#include "Utilidades.h"
#include "Archivos.h"
#include "Ordenamientos.h"
#include "DatosIniciales.h"
#include "Configuracion.h"
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "Cola.h"
#include "Usuario.h"
#include "Administrador.h"
#include "Ruta.h"
#include "ReporteTrafico.h"
#include "PuntoInteres.h"
#include "Sede.h"
#include "BusquedaRuta.h"
#include "HistorialBusqueda.h"
#include "Notificacion.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <queue>
#include <iomanip>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using namespace std;

namespace {

bool esNombreAdministrativo(const string& nombre);

void mostrarPantallaDeCarga() {
    const string logo[] = {
        "    ..:---===========================================---:..    ",
        "  ..-=====================================================-..  ",
        " .-=========================================================-..",
        ".-===========================================================-.",
        ":=============================================================:",
        "===========================+#@@@@@@@@@%#+======================",
        "=======================+%@@@%*=::::::=*%@@@%+==================",
        "=====================#@@%-..           ...=@@@#================",
        "===================#@@+.                     *@@#==============",
        "=================+@@#.                        .*@%+============",
        "================*@@=                            -@@*===========",
        "===============*@@:         ...           ...    =%@+==========",
        "==============+%@-         .*@#:.       .+@@-.    =@@==========",
        "==============#@#.         #@@@+.       =@@@@.    .#@*=========",
        "==============%@-.          *#+.         =**:      +@@=========",
        "=============+%@:                                  =@@=========",
        "=============+%@:           ..            ...      =@@=========",
        "=============+%@:           @@*          :%@:      *@%=========",
        "=============#@%:           :%@#-.     :*@@+.     :#@+=========",
        "=========+#%@@#:.            .=#@@%**#@@@*:.     .*@%==========",
        "=========+@@*:.                ..-====-:..      .+@%+==========",
        "==========*@%=                                 :#@%+===========",
        "===========+@@#:                              +@@#=============",
        "=============#@@%. .-%@@@@%*               .*@@%+==============",
        "===============*@@@@@@@@@@@@%           -#@@@#=================",
        "==================*@@@@@@@@@@@@@@@@@@@@@@@@@@==================",
        "==================*@@@@@@@@@@@####@@@@@@@@@@@==================",
        "===================%@@@@@@@@%=====+@@@@@@@@@+==================",
        "====================+%@@@@@+========*@@@@@#====================",
        ":=============================================================:",
        ".-===========================================================-.",
        " .-=========================================================-..",
        "  ..-=====================================================-:.  ",
        "    ..:--=============================================--:..    ",
    };
#ifdef _WIN32
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    // Si la salida es un archivo, continuamos directamente al menu.
    if (!GetConsoleScreenBufferInfo(consola, &info)) return;
    CONSOLE_CURSOR_INFO cursor;
    const bool restaurarCursor = GetConsoleCursorInfo(consola, &cursor) != 0;
    if (restaurarCursor) {
        CONSOLE_CURSOR_INFO oculto = cursor;
        oculto.bVisible = FALSE;
        SetConsoleCursorInfo(consola, &oculto);
    }
    const int ancho = (std::min)(68, int(info.srWindow.Right - info.srWindow.Left));
    const int alto = (std::min)(38, int(info.srWindow.Bottom - info.srWindow.Top));
    if (ancho >= 20 && alto >= 12) {
        limpiarPantalla();
        const int filas = sizeof(logo) / sizeof(logo[0]);
        int columnas = 0;
        for (const string& fila : logo)
            columnas = (std::max)(columnas, int(fila.size()));
        const int altoLogo = (std::min)(filas, alto - 3);
        const int anchoLogo = (std::min)(columnas, ancho);
        const int margenX = (ancho - anchoLogo) / 2;
        const int margenY = (alto - 3 - altoLogo) / 2;
        const double cx = (ancho - 1) / 2.0;
        const double cy = (alto - 4) / 2.0;

        // Dylan Jean Pierre Ybanez Mejia
        auto fotograma = [&](int etapa, double radio, bool guino, int numero) {
            for (int y = 0; y < alto; ++y) {
                string fila(ancho, ' ');
                for (int x = 0; x < ancho && y < alto - 3; ++x) {
                    double dx = (x - cx) / (anchoLogo / 2.0);
                    double dy = (y - cy) / (altoLogo / 2.0);
                    double distancia = sqrt(dx * dx + dy * dy);
                    if (etapa == 0) {
                        // La burbuja crece, revelando el logo desde su centro.
                        if (fabs(distancia - radio) < 0.05)
                            fila[x] = 'o';
                        else if (distancia < radio && x >= margenX &&
                                 x < margenX + anchoLogo && y >= margenY &&
                                 y < margenY + altoLogo) {
                            int ly = (y - margenY) * filas / altoLogo;
                            int lx = (x - margenX) * columnas / anchoLogo;
                            string detalle = logo[ly];
                            // El ojo derecho se cierra; el resto del logo se conserva.
                            if (guino && ly >= 11 && ly <= 14)
                                detalle.replace(40, 8, ly == 13 ? " .----. " : "        ");
                            if (lx < int(detalle.size())) fila[x] = detalle[lx];
                        }
                    }
                    else if (etapa == 1) {
                        // Fragmentos que se separan al explotar la burbuja.
                        for (int k = 0; k < 16; ++k) {
                            double angulo = k * 6.283185307 / 16;
                            int px = int(cx + cos(angulo) * radio * anchoLogo / 2.0);
                            int py = int(cy + sin(angulo) * radio * altoLogo / 2.0);
                            if (x == px && y == py) fila[x] = k % 2 ? 'o' : '*';
                        }
                        if (radio < 0.6 && y == int(cy) &&
                            x >= int(cx) - 2 && x < int(cx) + 2)
                            fila[x] = string("POP!")[x - (int(cx) - 2)];
                    }
                }
                if (y == alto - 2) {
                    string mensaje = "Cargando Waze" + string(1 + numero % 3, '.');
                    fila.replace((ancho - mensaje.size()) / 2, mensaje.size(), mensaje);
                }
                // Sobrescribir cada fila evita el parpadeo de ejecutar cls por cuadro.
                COORD posicion = { info.srWindow.Left,
                    static_cast<SHORT>(info.srWindow.Top + y) };
                DWORD escritos;
                WriteConsoleOutputCharacterA(consola, fila.c_str(),
                    static_cast<DWORD>(fila.size()), posicion, &escritos);
            }
            this_thread::sleep_for(chrono::milliseconds(70));
        };

        for (int i = 1; i <= 16; ++i) fotograma(0, i * 1.5 / 16, false, i);
        for (int i = 0; i < 8; ++i) fotograma(0, 1.5, false, i);
        for (int i = 0; i < 6; ++i) fotograma(0, 1.5, true, i);
        for (int i = 0; i < 5; ++i) fotograma(0, 1.5, false, i);
        for (int i = 0; i < 12; ++i) fotograma(1, 0.2 + i * 0.14, false, i);
        fotograma(2, 0, false, 0);
    }
    if (restaurarCursor) SetConsoleCursorInfo(consola, &cursor);
#else
    for (const string& fila : logo) cout << fila << '\n';
    cout << "\nCargando Waze..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
#endif
    limpiarPantalla();
}
bool menuPerfilUsuario(Usuario& usuarioActivo, ListaSimple<Usuario>& listaUsuarios) {
    int opcPerfil = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("            PERFIL DE USUARIO                \n");
        cout << "=============================================\n";
        cout << " Nombre de Usuario : " << usuarioActivo.getUsuario() << "\n";
        cout << " Correo Electronico: " << usuarioActivo.getCorreo() << "\n";
        cout << " Telefono          : " << usuarioActivo.getTelefono() << "\n";
        cout << " Anio Nacimiento   : ";
        if (usuarioActivo.getAnioNacimiento() >= 1900) cout << usuarioActivo.getAnioNacimiento() << "\n";
        else cout << "No registrado\n";
        cout << " Preferencia Ruta  : " << usuarioActivo.getPerfil().getPreferenciaRuta() << "\n";
        cout << "=============================================\n";
        cout << "1. Cambiar nombre de usuario\n";
        cout << "2. Cambiar contrasena\n";
        cout << "3. Eliminar cuenta\n";
        cout << "4. Volver al menu de navegacion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcPerfil)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcPerfil == 1) {
            string nuevoUser;
            cout << "\nIngrese el nuevo nombre de usuario: ";
            cin >> nuevoUser;
            if (esNombreAdministrativo(nuevoUser) ||
                // Mathias Raul Grovas Ormachea
                listaUsuarios.existeSi([&](const Usuario& u) {
                    return &u != &usuarioActivo && u.getUsuario() == nuevoUser;
                })) {
                cout << "[!] Nombre reservado o ya registrado.\n";
                pausar();
                continue;
            }
            usuarioActivo.setUsuario(nuevoUser);
            guardarUsuarios(listaUsuarios);
            cout << "\n[+] Nombre de usuario actualizado con exito.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (opcPerfil == 2) {
            string passActual, passNueva;
            cout << "\nIngrese su contrasena actual: ";
            cin >> passActual;
            if (passActual == usuarioActivo.getContrasena()) {
                cout << "Ingrese la nueva contrasena: ";
                cin >> passNueva;
                usuarioActivo.setContrasena(passNueva);
                guardarUsuarios(listaUsuarios);
                cout << "\n[+] Contrasena actualizada con exito.\n";
            }
            else cout << "\n[!] Contrasena incorrecta.\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
        else if (opcPerfil == 3) {
            char confirm;
            cout << "\nEsta seguro que desea eliminar su cuenta? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                string u = usuarioActivo.getUsuario();
                string p = usuarioActivo.getContrasena();

                // Identifica la cuenta que coincide con usuario y contrasena.
                // Edgar Kevin Serna Poma
                listaUsuarios.eliminar([&u, &p](const Usuario& usr) {
                    return usr.getUsuario() == u && usr.getContrasena() == p;
                });

                guardarUsuarios(listaUsuarios);
                cout << "\n[+] Cuenta eliminada correctamente. Redirigiendo...\n";
                this_thread::sleep_for(chrono::seconds(1));
                return true;
            }
        }
    } while (opcPerfil != 4);

    return false;
}

void explorarPOI(const ListaDoble<PuntoInteres>& listaPOI) {
    NodoDoble<PuntoInteres>* actual = listaPOI.getCabeza();
    char opc = 'x';

    if (actual == nullptr) {
        cout << "[!] No hay puntos de interes registrados.\n";
        pausar();
        return;
    }

    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("     PUNTOS DE INTERES CERCANOS (POI)        \n");
        cout << "=============================================\n\n";
        actual->dato.mostrar();
        cout << "\n=============================================\n";
        cout << " [A] Anterior  |  [S] Siguiente  |  [X] Salir\n";
        cout << "Opcion: ";
        cin >> opc;

        if ((opc == 's' || opc == 'S') && actual->siguiente != nullptr)
            actual = actual->siguiente;
        else if ((opc == 'a' || opc == 'A') && actual->anterior != nullptr)
            actual = actual->anterior;
    } while (opc != 'x' && opc != 'X');
}

const string CONTORNO_MAPA[] = {
"                            .===:",
"                          .:-...-+:.",
"                       .:=-..   ..:==.",
"                .:=*=......        ..:*.",
"           ...:+*.                    ..+*:.....",
"           .+:.                           ....*:..",
"           .-=.                               ..+-.",
"           ..+.                                 =-....         .:=-:..",
"            .*.                                 .:---=+=:..::..--..-=+:.",
"            .+.                                        .::::::::..  .:+-..",
"           .+-.                                                       .-+#*=:.",
"         .:+:.                                                           ....-+#.",
"      ..=#-.                                                               .==..",
"      .*-                                                                   .+-..",
"      .*.                                                                    .-*:",
"     .:*:                                                                      -+",
"     .*.                                                                       :*",
"   ..+:                                                                        .*",
".==::..                                                                      :=::",
".--                                                                         .=-.",
" .-=.                                                                      .:=.",
" .-=.                                                                     .:=:.",
".:+.                                                                     .:+:.",
"..=:                                                                    .+=.",
" .:=.                                                                 .-+:.",
"  :=.                                                               .:+-..",
"..-=.                                                              .==..",
"+-..                                                             .*+..",
"..:++:.                                                      ..:*-.",
"    .-=. ..-+=.                                           ..:++:.",
"      .==-+-:++==:                                  ...-=++-..",
"         .::.-=:+.                             ..:-==+-..",
"         .-.-:.--                          .-+==--..",
"         .... .+:                        .+=:.",
"            .=*:                       .==..",
"        .:##+:.                       .-=.",
"         .--                       .#-%*.",
"         .--.                      .#",
"          :-..                    .*:",
"         ..=:.                   .+:.",
"      .+==-..                   .=-.",
"      .+-.                      :=:",
"      ..*:.-=:.                .==.",
"       -++*:..-+*--:.          .==",
"                   .*-        .-+.",
"                    :+      .:#:",
"                    .==.   .=*.",
"                      .====+="
};

struct UbicacionMapa {
    string nombre;
    int x = 0;
    int y = 0;
    string distrito;
    string direccion;
};
ListaSimple<UbicacionMapa> ubicacionesMapa;
const int MAPA_FILAS = sizeof(CONTORNO_MAPA) / sizeof(CONTORNO_MAPA[0]);

int anchoMapa() {
    int ancho = 0;
    for (const string& fila : CONTORNO_MAPA) ancho = (std::max)(ancho, int(fila.size()));
    return ancho;
}

// Cada fila del ASCII delimita el interior entre sus bordes izquierdo y derecho.
// Los caracteres del contorno y todo el espacio exterior estan excluidos.
bool coordenadasValidas(int x, int y) {
    if (y < 0 || y >= MAPA_FILAS || x < 0 || x >= int(CONTORNO_MAPA[y].size()))
        return false;
    const string& fila = CONTORNO_MAPA[y];
    size_t izquierda = fila.find_first_not_of(' ');
    size_t derecha = fila.find_last_not_of(' ');
    return izquierda != string::npos && x > int(izquierda) && x < int(derecha) &&
           fila[x] == ' ';
}

string recortar(string texto) {
    size_t inicio = texto.find_first_not_of(" \t\r");
    if (inicio == string::npos) return "";
    return texto.substr(inicio, texto.find_last_not_of(" \t\r") - inicio + 1);
}

bool textoMapaValido(const string& texto) {
    return !texto.empty() && texto.find('|') == string::npos;
}

int inicioEtiqueta(const UbicacionMapa& u) {
    if (u.y <= 0 || !coordenadasValidas(u.x, u.y)) return -1;
    int preferido = u.x - int(u.nombre.size()) / 2;
    int mejor = -1, distancia = anchoMapa() + 1;
    for (int inicio = 0; inicio + int(u.nombre.size()) <= anchoMapa(); ++inicio) {
        bool libre = true;
        for (int i = 0; i < int(u.nombre.size()); ++i)
            if (!coordenadasValidas(inicio + i, u.y - 1)) { libre = false; break; }
        if (libre && abs(inicio - preferido) < distancia) {
            mejor = inicio; distancia = abs(inicio - preferido);
        }
    }
    return mejor;
}

void cargarUbicacionesMapa() {
    // Las cuatro sedes son puntos fijos del mapa. Las coordenadas son internas
    // y no se solicitan al usuario ni al administrador.
    ubicacionesMapa.vaciar();
    ubicacionesMapa.insertarFinal(UbicacionMapa{SEDE_MONTERRICO, 15, 5,
        "Santiago de Surco", "UPC Monterrico"});
    ubicacionesMapa.insertarFinal(UbicacionMapa{SEDE_SAN_MIGUEL, 74, 12,
        "San Miguel", "UPC San Miguel"});
    ubicacionesMapa.insertarFinal(UbicacionMapa{SEDE_VILLA, 10, 41,
        "Chorrillos", "UPC Villa"});
    ubicacionesMapa.insertarFinal(UbicacionMapa{SEDE_SAN_ISIDRO, 60, 28,
        "San Isidro", "UPC San Isidro"});
}

void mostrarMapaASCII() {
    limpiarPantalla();
    string imagen[MAPA_FILAS];
    for (int i = 0; i < MAPA_FILAS; ++i) imagen[i] = CONTORNO_MAPA[i];
    // Edgar Kevin Serna Poma
    ubicacionesMapa.recorrerConLambda([&](const UbicacionMapa& u) {
        int inicio = inicioEtiqueta(u);
        if (inicio < 0) return;
        imagen[u.y - 1].replace(inicio, u.nombre.size(), u.nombre);
        imagen[u.y][u.x] = 'O';
    });
    for (const string& fila : imagen) cout << fila << '\n';
}

void pausaFormulario() {
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

void listarUbicacionesMapa() {
    imprimirTituloAmarillo("SEDES FIJAS DEL MAPA\n\n");
    int indice = 0;
    // Mathias Raul Grovas Ormachea
    ubicacionesMapa.recorrerConLambda([&](const UbicacionMapa& u) {
        cout << ++indice << ". " << u.nombre << '\n';
    });
}

void menuMapaAdministrativo() {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("              MAPA Y SEDES FIJAS\n");
        cout << "=============================================\n";
        cout << "1. Mostrar mapa\n";
        cout << "2. Ver sedes fijas\n";
        cout << "3. Volver\nOpcion: ";
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcion = 0;
        }
        if (opcion == 1) { mostrarMapaASCII(); pausar(); }
        else if (opcion == 2) { limpiarPantalla(); listarUbicacionesMapa(); pausar(); }
        else if (opcion != 3) { cout << "[!] Opcion invalida.\n"; pausar(); }
    } while (opcion != 3);
}

bool hayUbicaciones(int minimo) {
    if (ubicacionesMapa.longitud() >= minimo) return true;
    cout << "\n[!] No se pudieron cargar las sedes fijas del mapa.\n";
    pausar();
    return false;
}

string seleccionarUbicacion(const string& titulo) {
    imprimirTituloAmarillo("\n" + titulo + "\n");
    int indice = 0;
    // Mathias Raul Grovas Ormachea
    ubicacionesMapa.recorrerConLambda([&](const UbicacionMapa& u) {
        cout << ++indice << ". " << u.nombre << "\n";
    });
    int opcion = 0;
    do {
        cout << "Seleccione una ubicacion: ";
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
        }
        if (opcion < 1 || opcion > ubicacionesMapa.longitud())
            cout << "[!] Seleccione una ubicacion de la lista.\n";
    } while (opcion < 1 || opcion > ubicacionesMapa.longitud());
    return ubicacionesMapa.obtenerPos(opcion - 1)->nombre;
}
int leerOpcion();

struct PasoMapa { int x; int y; };
struct RecorridoMapa {
    vector<Ruta> tramos;
    double distancia = 0;
    int tiempo = 0;
};

const UbicacionMapa* buscarPuntoMapa(const string& nombre) {
    // Edgar Kevin Serna Poma
    return ubicacionesMapa.buscar([&](const UbicacionMapa& u) { return textoIgual(u.nombre, nombre); });
}

// Cada ruta es una conexion dirigida. La recursion evita ciclos.
void buscarRecorridos(const string& actual, const string& destino,
                     const ListaSimple<Ruta>& rutas, vector<string>& visitadas,
                     RecorridoMapa& parcial, vector<RecorridoMapa>& resultados) {
    if (textoIgual(actual, destino)) { resultados.push_back(parcial); return; }
    // Dylan Jean Pierre Ybanez Mejia
    rutas.recorrerConLambda([&](const Ruta& r) {
        if (!textoIgual(r.getOrigen(), actual) || !buscarPuntoMapa(r.getDestino())) return;
        for (const string& nombre : visitadas)
            if (textoIgual(nombre, r.getDestino())) return;
        visitadas.push_back(r.getDestino());
        parcial.tramos.push_back(r);
        parcial.distancia += r.getDistanciaKm();
        parcial.tiempo += r.getTiempoMin();
        buscarRecorridos(r.getDestino(), destino, rutas, visitadas, parcial, resultados);
        parcial.tiempo -= r.getTiempoMin();
        parcial.distancia -= r.getDistanciaKm();
        parcial.tramos.pop_back();
        visitadas.pop_back();
    });
}

// El trazo visual respeta el contorno; km/min vienen de las rutas registradas.
vector<PasoMapa> caminoInterior(const UbicacionMapa& origen, const UbicacionMapa& destino) {
    const int ancho = anchoMapa();
    vector<int> anterior(ancho * MAPA_FILAS, -1);
    queue<int> pendientes;
    int inicio = origen.y * ancho + origen.x;
    int final = destino.y * ancho + destino.x;
    anterior[inicio] = inicio;
    pendientes.push(inicio);
    const int dx[] = {1, -1, 0, 0};
    const int dy[] = {0, 0, 1, -1};
    while (!pendientes.empty() && anterior[final] == -1) {
        int actual = pendientes.front(); pendientes.pop();
        for (int i = 0; i < 4; ++i) {
            int x = actual % ancho + dx[i], y = actual / ancho + dy[i];
            if (!coordenadasValidas(x, y)) continue;
            int siguiente = y * ancho + x;
            if (anterior[siguiente] != -1) continue;
            anterior[siguiente] = actual; pendientes.push(siguiente);
        }
    }
    vector<PasoMapa> camino;
    if (anterior[final] == -1) return camino;
    for (int actual = final;; actual = anterior[actual]) {
        camino.push_back(PasoMapa{actual % ancho, actual / ancho});
        if (actual == inicio) break;
    }
    reverse(camino.begin(), camino.end());
    return camino;
}

vector<string> dibujarRecorrido(const vector<PasoMapa>& trazo, size_t avance, bool coche) {
    vector<string> imagen(CONTORNO_MAPA, CONTORNO_MAPA + MAPA_FILAS);
    const int ancho = anchoMapa();
    for (string& fila : imagen) fila.resize(ancho, ' ');
    for (size_t i = 0; i <= avance && i < trazo.size(); ++i)
        imagen[trazo[i].y][trazo[i].x] = '*';
    // Mathias Raul Grovas Ormachea
    ubicacionesMapa.recorrerConLambda([&](const UbicacionMapa& u) {
        int inicio = inicioEtiqueta(u);
        if (inicio >= 0) imagen[u.y - 1].replace(inicio, u.nombre.size(), u.nombre);
        imagen[u.y][u.x] = 'O';
    });
    if (coche && avance < trazo.size()) {
        PasoMapa punto = trazo[avance];
        bool derecha = true;
        for (size_t i = avance; i > 0; --i)
            if (trazo[i].x != trazo[i - 1].x) {
                derecha = trazo[i].x > trazo[i - 1].x; break;
            }
        if (avance == 0)
            for (size_t i = 1; i < trazo.size(); ++i)
                if (trazo[i].x != punto.x) { derecha = trazo[i].x > punto.x; break; }
        vector<string> autoASCII = {
            R"(  ______       )",
            R"( /|_||_\ .__   )",
            R"((   _    _ _\  )",
            R"(= -(_)--(_)-'  )"
        };
        autoASCII[1][8] = char(96);
        autoASCII[3][1] = char(96);
        if (!derecha) {
            for (string& fila : autoASCII) {
                reverse(fila.begin(), fila.end());
                for (char& c : fila) {
                    if (c == '/') c = '\\'; else if (c == '\\') c = '/';
                    else if (c == '(') c = ')'; else if (c == ')') c = '(';
                }
            }
        }
        int izquierda = punto.x - int(autoASCII[0].size()) / 2;
        int arriba = punto.y - 2;
        bool cabe = true;
        for (int y = 0; y < int(autoASCII.size()); ++y)
            for (int x = 0; x < int(autoASCII[y].size()); ++x)
                if (autoASCII[y][x] != ' ' && !coordenadasValidas(izquierda + x, arriba + y))
                    cabe = false;
        if (cabe) {
            for (int y = 0; y < int(autoASCII.size()); ++y)
                for (int x = 0; x < int(autoASCII[y].size()); ++x)
                    if (autoASCII[y][x] != ' ') imagen[arriba + y][izquierda + x] = autoASCII[y][x];
        } else {
            imagen[punto.y][punto.x] = derecha ? '>' : '<';
        }
    }
    return imagen;
}

void animarRecorrido(const RecorridoMapa& recorrido) {
    vector<PasoMapa> trazo;
    for (const Ruta& tramo : recorrido.tramos) {
        const UbicacionMapa* origen = buscarPuntoMapa(tramo.getOrigen());
        const UbicacionMapa* destino = buscarPuntoMapa(tramo.getDestino());
        if (!origen || !destino) return;
        vector<PasoMapa> segmento = caminoInterior(*origen, *destino);
        if (segmento.empty()) {
            cout << "[!] No se puede dibujar este tramo dentro del contorno.\n"; return;
        }
        if (!trazo.empty()) segmento.erase(segmento.begin());
        trazo.insert(trazo.end(), segmento.begin(), segmento.end());
    }
    if (trazo.empty()) return;
    limpiarPantalla();
#ifdef _WIN32
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    bool animar = GetConsoleScreenBufferInfo(consola, &info) != 0;
    CONSOLE_CURSOR_INFO cursor;
    bool restaurar = animar && GetConsoleCursorInfo(consola, &cursor);
    if (restaurar) {
        CONSOLE_CURSOR_INFO oculto = cursor; oculto.bVisible = FALSE;
        SetConsoleCursorInfo(consola, &oculto);
    }
    if (animar) {
        COORD maximo = GetLargestConsoleWindowSize(consola);
        SHORT ancho = static_cast<SHORT>((std::max)(int(info.dwSize.X), anchoMapa() + 2));
        SHORT alto = static_cast<SHORT>((std::max)(int(info.dwSize.Y), MAPA_FILAS + 5));
        SetConsoleScreenBufferSize(consola, COORD{ancho, alto});
        SMALL_RECT ventana = {0, 0,
            static_cast<SHORT>((std::min)(int(maximo.X), anchoMapa() + 2) - 1),
            static_cast<SHORT>((std::min)(int(maximo.Y), MAPA_FILAS + 5) - 1)};
        SetConsoleWindowInfo(consola, TRUE, &ventana);
        SetConsoleCursorPosition(consola, COORD{0, 0});
    }
#else
    bool animar = false;
#endif
    if (animar) {
        const int pausa = (std::max)(20, (std::min)(70, 4000 / int(trazo.size())));
        for (size_t i = 0; i < trazo.size(); ++i) {
            vector<string> imagen = dibujarRecorrido(trazo, i, true);
#ifdef _WIN32
            for (int y = 0; y < MAPA_FILAS; ++y) {
                DWORD escritos;
                WriteConsoleOutputCharacterA(consola, imagen[y].c_str(),
                    static_cast<DWORD>(imagen[y].size()), COORD{0, static_cast<SHORT>(y)}, &escritos);
            }
#endif
            this_thread::sleep_for(chrono::milliseconds(pausa));
        }
    }
    vector<string> final = dibujarRecorrido(trazo, trazo.size() - 1, false);
#ifdef _WIN32
    if (animar) {
        for (int y = 0; y < MAPA_FILAS; ++y) {
            DWORD escritos;
            WriteConsoleOutputCharacterA(consola, final[y].c_str(),
                static_cast<DWORD>(final[y].size()), COORD{0, static_cast<SHORT>(y)}, &escritos);
        }
        SetConsoleCursorPosition(consola, COORD{0, static_cast<SHORT>(MAPA_FILAS)});
    } else
#endif
        for (const string& fila : final) cout << fila << '\n';
#ifdef _WIN32
    if (restaurar) SetConsoleCursorInfo(consola, &cursor);
#endif
    cout << "\nRecorrido completado: " << recorrido.tramos.front().getOrigen();
    for (const Ruta& tramo : recorrido.tramos) cout << " -> " << tramo.getDestino();
    cout << "\n";
}

void mantenerMapaConResultados(const string& origen, const string& destino,
                              const vector<RecorridoMapa>& resultados, size_t mejor) {
    vector<PasoMapa> trazo;
    for (const Ruta& tramo : resultados[mejor].tramos) {
        const UbicacionMapa* a = buscarPuntoMapa(tramo.getOrigen());
        const UbicacionMapa* b = buscarPuntoMapa(tramo.getDestino());
        if (!a || !b) continue;
        vector<PasoMapa> segmento = caminoInterior(*a, *b);
        if (!trazo.empty() && !segmento.empty()) segmento.erase(segmento.begin());
        trazo.insert(trazo.end(), segmento.begin(), segmento.end());
    }
    vector<string> mapa = dibujarRecorrido(trazo, trazo.empty() ? 0 : trazo.size() - 1, false);
    vector<string> resumen;
    // Ajusta el texto a la columna lateral y pagina sin mover el mapa.
    // Edgar Kevin Serna Poma
    auto agregar = [&](string linea) {
        const size_t ancho = 44;
        while (linea.size() > ancho) {
            size_t corte = linea.rfind(' ', ancho);
            if (corte == string::npos || corte == 0) corte = ancho;
            resumen.push_back(linea.substr(0, corte));
            linea = linea.substr(corte);
            if (!linea.empty() && linea[0] == ' ') linea.erase(0, 1);
        }
        resumen.push_back(linea);
    };
    agregar("Origen seleccionado: " + origen);
    agregar("Destino seleccionado: " + destino);
    agregar("Rutas registradas para este trayecto:");
    agregar("--------------------------------------------");
    for (size_t i = 0; i < resultados.size(); ++i) {
        const RecorridoMapa& r = resultados[i];
        agregar("Alternativa " + to_string(i + 1) +
            (i == mejor ? " [seleccionada]" : ""));
        if (r.tramos.size() > 1) agregar("RECORRIDO CON CONEXIONES");
        for (const Ruta& tramo : r.tramos) {
            agregar(tramo.getNombre());
            agregar("Origen: " + tramo.getOrigen());
            agregar("Destino: " + tramo.getDestino());
            ostringstream datos;
            datos << fixed << setprecision(1) << "Distancia: " << tramo.getDistanciaKm()
                  << " km | Tiempo: " << tramo.getTiempoMin() << " min";
            agregar(datos.str());
            const auto& puntos = tramo.getPuntosPaso();
            if (!puntos.empty()) {
                string detalle = "Pasa por: ";
                for (size_t p = 0; p < puntos.size(); ++p) {
                    if (p > 0) detalle += " -> ";
                    detalle += puntos[p];
                }
                agregar(detalle);
            }
        }
        ostringstream totales;
        totales << fixed << setprecision(1) << "Distancia total: " << r.distancia << " km";
        agregar(totales.str());
        agregar("Tiempo total: " + to_string(r.tiempo) + " min");
        if (i == mejor) agregar("[+] Recorrido seleccionado por el usuario.");
        agregar("--------------------------------------------");
    }
    agregar("Total de alternativas: " + to_string(resultados.size()));
    const int lineasPorPagina = MAPA_FILAS - 2;
    const int paginas = (int(resumen.size()) + lineasPorPagina - 1) / lineasPorPagina;
    int pagina = 0;
#ifdef _WIN32
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    bool esConsola = GetConsoleScreenBufferInfo(consola, &info) != 0;
    if (esConsola) {
        const int ancho = anchoMapa() + 3 + 44;
        COORD tamano = {static_cast<SHORT>((std::max)(int(info.dwSize.X), ancho + 1)),
                        static_cast<SHORT>((std::max)(int(info.dwSize.Y), MAPA_FILAS + 4))};
        SetConsoleScreenBufferSize(consola, tamano);
        COORD maximo = GetLargestConsoleWindowSize(consola);
        SMALL_RECT ventana = {0, 0,
            static_cast<SHORT>((std::min)(int(maximo.X), ancho + 1) - 1),
            static_cast<SHORT>((std::min)(int(maximo.Y), MAPA_FILAS + 4) - 1)};
        SetConsoleWindowInfo(consola, TRUE, &ventana);
    }
#else
    bool esConsola = false;
#endif
    // Dylan Jean Pierre Ybanez Mejia
    auto mostrar = [&]() {
        vector<string> pantalla = mapa;
        for (int y = 0; y < MAPA_FILAS; ++y) {
            string derecha;
            if (y == 0) derecha = "RESULTADOS | " + to_string(pagina + 1) + "/" + to_string(paginas);
            else if (y >= 2) {
                int indice = pagina * lineasPorPagina + y - 2;
                if (indice < int(resumen.size())) derecha = resumen[indice];
            }
            pantalla[y] += "   " + derecha + string(44 - derecha.size(), ' ');
        }
#ifdef _WIN32
        if (esConsola) {
            for (int y = 0; y < MAPA_FILAS; ++y) {
                DWORD escritos;
                WriteConsoleOutputCharacterA(consola, pantalla[y].c_str(),
                    static_cast<DWORD>(pantalla[y].size()), COORD{0, static_cast<SHORT>(y)}, &escritos);
            }
            SetConsoleCursorPosition(consola, COORD{0, static_cast<SHORT>(MAPA_FILAS)});
        } else
#endif
            for (const string& fila : pantalla) cout << fila << '\n';
        cout << "[ENTER] Mantener mapa | [N/P] Paginas del resumen | [V] Volver: " << flush;
    };
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    mostrar();
    string opcion;
    while (getline(cin, opcion)) {
        opcion = aMinusculas(recortar(opcion));
        if (opcion == "v") break;
        int anterior = pagina;
        if (opcion == "n" && pagina + 1 < paginas) ++pagina;
        else if (opcion == "p" && pagina > 0) --pagina;
        if (pagina != anterior) mostrar();
#ifdef _WIN32
        else if (esConsola) {
            // ENTER no vuelve al menu ni agrega lineas debajo del mapa.
            SetConsoleCursorPosition(consola, COORD{0, static_cast<SHORT>(MAPA_FILAS)});
            cout << "[ENTER] Mantener mapa | [N/P] Paginas del resumen | [V] Volver: " << flush;
        }
#endif
    }
}
void buscarRutasAlternativas(const Usuario& usuarioActivo, const ListaSimple<Ruta>& rutas) {
    if (!hayUbicaciones(2)) return;
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("       BUSQUEDA RECURSIVA DE RUTAS\n");
    cout << "=============================================\n";
    string origen = seleccionarUbicacion("ORIGEN");
    string destino;
    do {
        destino = seleccionarUbicacion("DESTINO");
        if (textoIgual(origen, destino)) cout << "[!] El destino debe ser diferente del origen.\n";
    } while (textoIgual(origen, destino));

    vector<string> visitadas{origen};
    RecorridoMapa parcial;
    vector<RecorridoMapa> resultados;
    buscarRecorridos(origen, destino, rutas, visitadas, parcial, resultados);
    if (resultados.empty()) {
        cout << "\nOrigen seleccionado : " << origen << "\nDestino seleccionado: " << destino;
        cout << "\n[!] No existen rutas registradas que conecten esas ubicaciones.\n";
        pausar(); return;
    }
    size_t recomendado = 0;
    for (size_t i = 1; i < resultados.size(); ++i)
        if (resultados[i].tiempo < resultados[recomendado].tiempo ||
            (resultados[i].tiempo == resultados[recomendado].tiempo &&
             resultados[i].distancia < resultados[recomendado].distancia)) recomendado = i;

    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("          RUTAS DISPONIBLES PARA ELEGIR\n");
    cout << "=============================================\n";
    for (size_t i = 0; i < resultados.size(); ++i) {
        cout << "\n" << i + 1 << ". ";
        for (size_t j = 0; j < resultados[i].tramos.size(); ++j) {
            if (j > 0) cout << " + ";
            cout << resultados[i].tramos[j].getNombre();
        }
        if (i == recomendado) cout << "  [RECOMENDADA]";
        cout << "\n   Distancia total: " << fixed << setprecision(1)
             << resultados[i].distancia << " km";
        cout << "\n   Tiempo total   : " << resultados[i].tiempo << " min\n";
        for (const Ruta& tramo : resultados[i].tramos) {
            const auto& puntos = tramo.getPuntosPaso();
            if (!puntos.empty()) {
                cout << "   " << tramo.getNombre() << " pasa por: ";
                for (size_t p = 0; p < puntos.size(); ++p) {
                    if (p > 0) cout << " -> ";
                    cout << puntos[p];
                }
                cout << "\n";
            }
        }
    }
    cout << "\n0. Volver\nSeleccione la ruta que desea visualizar: ";
    int seleccion = leerOpcion();
    if (seleccion == 0) return;
    if (seleccion < 1 || seleccion > static_cast<int>(resultados.size())) {
        cout << "[!] Opcion invalida.\n";
        pausar();
        return;
    }
    size_t elegida = static_cast<size_t>(seleccion - 1);
    animarRecorrido(resultados[elegida]);
    mantenerMapaConResultados(origen, destino, resultados, elegida);
}

void reportarUbicacionIncorrecta(const Usuario& usuario, Cola<ReporteTrafico>& reportes) {
    if (!hayUbicaciones(1)) return;
    limpiarPantalla();
    imprimirTituloAmarillo("REPORTAR UBICACION INCORRECTA\n");
    string nombre = seleccionarUbicacion("UBICACION A REPORTAR");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string detalle;
    cout << "Describa el error: "; getline(cin, detalle);
    detalle = recortar(detalle);
    if (!textoMapaValido(detalle)) cout << "[!] Complete la descripcion sin usar |.\n";
    else {
        ReporteTrafico reporte("Ubicacion incorrecta - " + usuario.getUsuario() + ": " + detalle,
                              nombre, 1);
        reportes.enqueue(reporte);
        guardarReportesPendientes(reportes);
        registrarEnHistorial(reporte, "REGISTRADO");
        cout << "[+] Reporte enviado al centro de alertas para revision administrativa.\n";
    }
    pausaFormulario();
}

void menuMapaGeneral(const Usuario& usuario, Cola<ReporteTrafico>& reportes) {
    int opcion = 0;
    do {
        limpiarPantalla();
        imprimirTituloAmarillo("MAPA - USUARIO GENERAL\n");
        cout << "1. Ver mapa\n2. Reportar ubicacion incorrecta\n3. Volver\nOpcion: ";
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); opcion = 0;
        }
        if (opcion == 1) { mostrarMapaASCII(); pausar(); }
        else if (opcion == 2) reportarUbicacionIncorrecta(usuario, reportes);
        else if (opcion != 3) { cout << "[!] Opcion invalida.\n"; pausar(); }
    } while (opcion != 3);
}
void registrarRutaAlternativa(ListaSimple<Ruta>& rutas) {
    if (!hayUbicaciones(4)) return;
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("        REGISTRAR RUTA ALTERNATIVA           \n");
    cout << "=============================================\n";

    string nombre, origen, destino;
    double distancia;
    int tiempo;
    vector<string> puntosPaso;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nombre de la ruta : "; getline(cin, nombre);
    origen = seleccionarUbicacion("SEDE DE INICIO");
    do {
        destino = seleccionarUbicacion("SEDE DE DESTINO");
        if (textoIgual(origen, destino))
            cout << "\n[!] La sede de destino debe ser diferente de la sede de inicio.\n";
    } while (textoIgual(origen, destino));

    cout << "Distancia (km)       : "; cin >> distancia;
    cout << "Tiempo estimado (min): "; cin >> tiempo;

    if (nombre.empty() || nombre.find('|') != string::npos || distancia <= 0 || tiempo <= 0) {
        cout << "\n[!] Datos de ruta invalidos.\n";
        pausar();
        return;
    }

    int opcionPunto = 0;
    while (puntosPaso.size() < 3) {
        imprimirTituloAmarillo("\nPUNTOS DE PASADA DE LA RUTA\n");
        cout << "1. Agregar punto de pasada\n";
        cout << "2. Registrar ruta\n";
        cout << "Opcion: ";
        opcionPunto = leerOpcion();
        if (opcionPunto == 2) break;
        if (opcionPunto != 1) {
            cout << "[!] Opcion invalida.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string punto;
        cout << "Escriba el punto o ubicacion por donde pasa la ruta: ";
        getline(cin, punto);
        punto = recortar(punto);
        if (punto.empty() || punto.find('|') != string::npos || punto.find(';') != string::npos) {
            cout << "[!] Punto invalido. No use los caracteres | o ;.\n";
            continue;
        }
        puntosPaso.push_back(punto);
        cout << "[+] Punto agregado: " << punto << "\n";
    }
    if (puntosPaso.size() == 3)
        cout << "\n[+] Se alcanzo el maximo de 3 puntos de pasada.\n";

    Sede sedeOrigen(origen);
    Sede sedeDestino(destino);
    Avenida avenidaPrincipal("Via principal de " + nombre);
    Interseccion cruce(avenidaPrincipal, Avenida("Conexion de " + nombre), "Cruce principal");
    TramoRuta tramo(nombre, avenidaPrincipal, cruce, distancia, 1);
    EstadoRuta estado(nombre, 0, true);
    Ruta nuevaRuta(nombre, sedeOrigen, sedeDestino, distancia, tiempo, estado, tramo, puntosPaso);

    rutas.insertarFinal(nuevaRuta);
    guardarRutas(rutas);
    cout << "\n[+] Ruta alternativa registrada correctamente.\n";
    cout << "    Inicio : " << origen << "\n";
    cout << "    Destino: " << destino << "\n";
    if (!puntosPaso.empty()) {
        cout << "    Pasa por: ";
        for (size_t i = 0; i < puntosPaso.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << puntosPaso[i];
        }
        cout << "\n";
    }
    pausar();
}

void mostrarTodasLasRutas(const ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("            RUTAS REGISTRADAS                \n");
    cout << "=============================================\n\n";

    int contador = 0;

    // Mathias Raul Grovas Ormachea
    rutas.recorrerConLambda([&contador](const Ruta& r) {
        contador++;
        cout << contador << ".\n";
        r.mostrarInfo();
        cout << "---------------------------------------------\n";
    });

    if (contador == 0) cout << "[!] No hay rutas registradas.\n";
    pausar();
}

void registrarReporte(const Usuario& usuarioActivo, Cola<ReporteTrafico>& colaReportes) {
    if (!hayUbicaciones(1)) return;
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("          REGISTRAR REPORTE TRAFICO          \n");
    cout << "=============================================\n";

    string tipo, ubicacion;
    int gravedad;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Tipo de reporte (Accidente, Trafico, Obras...): "; getline(cin, tipo);
    ubicacion = seleccionarUbicacion("UBICACION DEL REPORTE");
    cout << "Nivel de congestion (1-5): "; cin >> gravedad;

    if (tipo.empty() || gravedad < 1 || gravedad > 5) {
        cout << "\n[!] Datos invalidos. La gravedad debe estar entre 1 y 5.\n";
    }
    else {
        Sede sedeReporte(ubicacion);
        ReporteTrafico nuevo(tipo, sedeReporte, gravedad);
        colaReportes.enqueue(nuevo);
        guardarReportesPendientes(colaReportes);
        registrarEnHistorial(nuevo, "REGISTRADO");


        Notificacion aviso(usuarioActivo, "Nuevo reporte de trafico registrado", nuevo);
        cout << "\n[+] Reporte agregado al final de la cola FIFO.\n";
        cout << "[+] Notificacion generada para " << aviso.getUsuario() << ".\n";
    }
    pausar();
}

void mostrarReportesPendientes(const Cola<ReporteTrafico>& colaReportes, bool soloGraves) {
    limpiarPantalla();
    cout << "=============================================\n";
    if (soloGraves) imprimirTituloAmarillo("       ALERTAS IMPORTANTES (GRAVEDAD >= 3)   \n");
    else imprimirTituloAmarillo("          COLA DE REPORTES PENDIENTES        \n");
    cout << "=============================================\n\n";

    int contador = 0;
    // Edgar Kevin Serna Poma
    colaReportes.recorrerConLambda([&contador, soloGraves](const ReporteTrafico& r) {
        if (!soloGraves || r.getGravedad() >= 3) {
            contador++;
            cout << contador << ". ";
            r.mostrarInfo();
        }
    });

    if (contador == 0) cout << "[!] No hay reportes que mostrar.\n";
    else if (!soloGraves) cout << "\nTotal en cola: " << colaReportes.size() << "\n";
    pausar();
}

void procesarReporteMasAntiguo(Cola<ReporteTrafico>& colaReportes) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("          PROCESAR REPORTE MAS ANTIGUO       \n");
    cout << "=============================================\n\n";

    ReporteTrafico reporte;
    if (colaReportes.dequeue(reporte)) {
        cout << "Reporte procesado siguiendo FIFO:\n";
        reporte.mostrarInfo();
        guardarReportesPendientes(colaReportes);
        registrarEnHistorial(reporte, "PROCESADO");
        cout << "\n[+] El reporte fue retirado del frente de la cola.\n";
    }
    else cout << "[!] La cola de reportes esta vacia.\n";
    pausar();
}

void menuCentroAlertas(const Usuario& usuarioActivo, Cola<ReporteTrafico>& colaReportes, bool administrador = true) {
    int opcion = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("           CENTRO DE ALERTAS DE TRAFICO      \n");
        cout << "=============================================\n";
        cout << "1. Registrar nuevo reporte\n";
        cout << "2. Ver cola de reportes pendientes (FIFO)\n";
        cout << "3. Ver alertas importantes con lambda\n";
        if (administrador) cout << "4. Procesar reporte mas antiguo\n";
        cout << "5. Volver\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) registrarReporte(usuarioActivo, colaReportes);
        else if (opcion == 2) mostrarReportesPendientes(colaReportes, false);
        else if (opcion == 3) mostrarReportesPendientes(colaReportes, true);
        else if (opcion == 4 && administrador) procesarReporteMasAntiguo(colaReportes);
    } while (opcion != 5);
}

bool esNombreAdministrativo(const string& nombre) {
    return textoIgual(nombre, "USEREDGAR") || textoIgual(nombre, "USERDYLAN") ||
           textoIgual(nombre, "USERMATHIAS");
}

int leerOpcion() {
    int opcion;
    if (!(cin >> opcion)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return opcion;
}

int seleccionarTipoUsuario() {
    const string admin[] = {
        "           #@@@@@@@@@@@*",
        "        %@%+...........*@@#",
        "      %@*.................#@*",
        "    +@#....................:@%",
        "    *@*.......:.........:.....%@",
        "   @%.......@@@-......@@@:...=@*",
        "  *@:.......:*=.......:*=.....@@",
        "  %@..........................%@",
        "  %@........:@+.......-@+.....@@",
        " +@*.........:%@*-:-+%@=.....-@*",
        "@@@@#=:..........-+*+=:.....:*@@",
        "#@@%%%%@@@%##**++===++**#@@@%@@+",
        " *@@%%%%%%@@%@=..+@@=.:@%@@%@@+",
        "  @@@%%%%%@@%@*.:@@..%%@@@@%",
        "    #@@@@@@@@@@%#@@%@@@@@%",
        "     +@@@@@@@@@@@@@@@@@@@",
        "      @@@@@@@*===*@@@@@@@",
        "       %@@@@+=====+@@@@%"
    };
    const string general[] = {
        "                  @@@@@@@@@@@@@@",
        "               @@@@#+=------=+*%@@@",
        "              @@#=--------------=*@@@ ",
        "            @@@=-------------------#@@",
        "           @@%------=++-------=++---+@@",
        "           @@%------=++-------=++---+@@",
        "          @@%-----=@@*#@#---=@@*#@%--*@@",
        "          @@=------=-----------------=%@",
        "          @@=-------------------------%@",
        "         @@%=-----*@@@@@@@@@@@@@@@@=--#@",
        "         @@%=-----*@%%%%%%%%%%%%%@@=--%@",
        "        @@@*-------@@%%@@@@@@@%%@@#--*@@",
        "        @@%=-----*@%%%%%%%%%%%%%@@=--%@",
        "       @@@*-------@@%%@@@@@@@%%@@#--*@@",
        "       @@#=----------+@@@%##%@@%=--+@@@",
        "        @@@*----=**------=++=----=@@@",
        "          @@@%#@@@@@@=--------=#@@@",
        "             @@@@@@@@@%%  %@@@@@@@",
        "              @@@@@@@@@@  @@@@@@@@@",
    };
    int opcion;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("             TIPO DE USUARIO\n");
        cout << "=============================================\n";
        const int filasAdmin = sizeof(admin) / sizeof(admin[0]);
        const int filasGeneral = sizeof(general) / sizeof(general[0]);
        const int filas = (std::max)(filasAdmin, filasGeneral);
        size_t anchoAdmin = 0;
        for (const string& linea : admin)
            anchoAdmin = (std::max)(anchoAdmin, linea.size());
        for (int i = 0; i < filas; ++i) {
            int ia = i - (filas - filasAdmin);
            int ig = i - (filas - filasGeneral);
            string izquierda = ia >= 0 ? admin[ia] : "";
            string derecha = ig >= 0 ? general[ig] : "";
            cout << izquierda << string(anchoAdmin - izquierda.size() + 4, ' ')
                 << derecha << '\n';
        }
        cout << "\n1. ADMINISTRATIVO" << string(20, ' ') << "2. USUARIO GENERAL\n";
        cout << "0. Volver\nSeleccione una opcion: ";
        opcion = leerOpcion();
        if (opcion < 0 || opcion > 2) {
            cout << "[!] Seleccione 1, 2 o 0.\n";
            pausar();
        }
    } while (opcion < 0 || opcion > 2);
    return opcion;
}

void guardarCombinadas(const ListaDoble<Ruta>& rutas) {
    ofstream archivo("rutas_combinadas.txt");
    // Dylan Jean Pierre Ybanez Mejia
    rutas.recorrerAdelante([&archivo](const Ruta& r) {
        archivo << r.getNombre() << '|' << r.getOrigen() << '|' << r.getSedeIntermedia()
                << '|' << r.getDestino() << '|' << r.getDistanciaKm() << '|' << r.getTiempoMin() << '|';
        const auto& puntos = r.getPuntosPaso();
        for (size_t i = 0; i < puntos.size(); ++i) {
            if (i > 0) archivo << ';';
            archivo << puntos[i];
        }
        archivo << '\n';
    });
}

void cargarCombinadas(ListaDoble<Ruta>& rutas) {
    ifstream archivo("rutas_combinadas.txt");
    string linea;
    while (getline(archivo, linea)) {
        vector<string> campos;
        string campo;
        stringstream datos(linea);
        while (getline(datos, campo, '|')) campos.push_back(campo);
        if (!linea.empty() && linea.back() == '|') campos.push_back("");

        try {
            // Formato final:
            // nombre|origen|sede_intermedia|destino|km|minutos|puntos_de_pasada
            if (campos.size() >= 7) {
                vector<string> puntos;
                string punto;
                stringstream listaPuntos(campos[6]);
                while (getline(listaPuntos, punto, ';'))
                    if (!punto.empty()) puntos.push_back(punto);

                double distancia = stod(campos[4]);
                int tiempo = stoi(campos[5]);
                if (!campos[0].empty() && distancia > 0 && tiempo > 0)
                    rutas.insertarFinal(Ruta(campos[0], campos[1], campos[3], distancia,
                        tiempo, puntos, campos[2]));
            }
            // Compatibilidad con rutas combinadas creadas en versiones anteriores.
            else if (campos.size() >= 6) {
                vector<string> puntos;
                string punto;
                stringstream listaPuntos(campos[5]);
                while (getline(listaPuntos, punto, ';'))
                    if (!punto.empty()) puntos.push_back(punto);

                double distancia = stod(campos[3]);
                int tiempo = stoi(campos[4]);
                if (!campos[0].empty() && distancia > 0 && tiempo > 0)
                    rutas.insertarFinal(Ruta(campos[0], campos[1], campos[2], distancia,
                        tiempo, puntos));
            }
        }
        catch (const exception&) { /* Ignora registros incompletos. */ }
    }
}

void explorarCombinadas(const ListaDoble<Ruta>& rutas, bool buscar) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("             RUTAS COMBINADAS\n");
    cout << "=============================================\n";
    string origen, destino;
    if (buscar) {
        if (!hayUbicaciones(2)) return;
        origen = seleccionarUbicacion("ORIGEN");
        destino = seleccionarUbicacion("DESTINO");
    }
    const NodoDoble<Ruta>* actual = rutas.getCabeza();
    // Mathias Raul Grovas Ormachea
    auto coincide = [&](const Ruta& r) {
        return !buscar || (textoIgual(r.getOrigen(), origen) &&
                           textoIgual(r.getDestino(), destino));
    };
    while (actual && !coincide(actual->dato)) actual = actual->siguiente;
    if (!actual) {
        cout << "[!] No hay rutas combinadas para mostrar.\n";
        pausar();
        return;
    }
    char opcion;
    do {
        limpiarPantalla();
        imprimirTituloAmarillo("RUTAS COMBINADAS - LISTA DOBLE\n\n");
        actual->dato.mostrarInfo();
        cout << "\n[A] Anterior | [S] Siguiente | [X] Volver\nOpcion: ";
        cin >> opcion;
        opcion = static_cast<char>(tolower(static_cast<unsigned char>(opcion)));
        if (opcion == 'a' || opcion == 's') {
            const NodoDoble<Ruta>* siguiente =
                opcion == 'a' ? actual->anterior : actual->siguiente;
            while (siguiente && !coincide(siguiente->dato))
                siguiente = opcion == 'a' ? siguiente->anterior : siguiente->siguiente;
            if (siguiente) actual = siguiente;
        }
    } while (opcion != 'x');
}

void registrarCombinada(const ListaSimple<Ruta>& alternativas, ListaDoble<Ruta>& combinadas) {
    limpiarPantalla();
    imprimirTituloAmarillo("REGISTRAR RUTA COMBINADA - DOS RUTAS CONECTADAS\n\n");
    for (int i = 0; i < alternativas.longitud(); ++i) {
        cout << i + 1 << ". ";
        alternativas.obtenerPos(i)->mostrarInfo();
    }
    cout << "\nPrimera ruta (0 para volver): ";
    int primera = leerOpcion();
    if (primera == 0) return;
    cout << "Segunda ruta (0 para volver): ";
    int segunda = leerOpcion();
    if (segunda == 0) return;
    const Ruta* a = alternativas.obtenerPos(primera - 1);
    const Ruta* b = alternativas.obtenerPos(segunda - 1);
    if (!a || !b || a == b || !textoIgual(a->getDestino(), b->getOrigen()) ||
        textoIgual(a->getOrigen(), b->getDestino())) {
        cout << "[!] El destino de la primera debe ser el origen de la segunda,\n"
                "    y la combinacion debe tener origen y destino distintos.\n";
        pausar();
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string nombre;
    cout << "Nombre de la ruta combinada: ";
    getline(cin, nombre);
    if (nombre.empty() || nombre.find('|') != string::npos ||
        // Edgar Kevin Serna Poma
        combinadas.existeSi([&](const Ruta& r) { return textoIgual(r.getNombre(), nombre); })) {
        cout << "[!] Nombre vacio, invalido o ya registrado.\n";
    } else {
        vector<string> puntos;
        // La sede que conecta ambas rutas se guarda por separado para mostrarla
        // claramente como sede intermedia de la ruta combinada.
        const string sedeIntermedia = a->getDestino();
        for (const string& p : a->getPuntosPaso())
            if (puntos.size() < 3) puntos.push_back(p);
        for (const string& p : b->getPuntosPaso())
            if (puntos.size() < 3) puntos.push_back(p);
        combinadas.insertarFinal(Ruta(nombre, a->getOrigen(), b->getDestino(),
            a->getDistanciaKm() + b->getDistanciaKm(), a->getTiempoMin() + b->getTiempoMin(),
            puntos, sedeIntermedia));
        guardarCombinadas(combinadas);
        cout << "[+] Ruta combinada registrada en ListaDoble<Ruta>.\n";
    }
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

void eliminarRuta(ListaSimple<Ruta>& alternativas, ListaDoble<Ruta>& combinadas) {
    limpiarPantalla();
    imprimirTituloAmarillo("ELIMINAR RUTA\n");
    cout << "1. Alternativa\n2. Combinada\n0. Volver\nOpcion: ";
    int tipo = leerOpcion();
    if (tipo == 0) return;
    if (tipo != 1 && tipo != 2) { cout << "[!] Opcion invalida.\n"; pausar(); return; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string nombre;
    cout << "Nombre exacto de la ruta: ";
    getline(cin, nombre);
    // Dylan Jean Pierre Ybanez Mejia
    auto criterio = [&](const Ruta& r) { return textoIgual(r.getNombre(), nombre); };
    bool existe = tipo == 1 ? alternativas.buscar(criterio) != nullptr :
                             combinadas.existeSi(criterio);
    if (!existe) { cout << "[!] Ruta no encontrada.\n"; pausar(); return; }
    char confirmar;
    cout << "Confirmar eliminacion (s/n): "; cin >> confirmar;
    if (confirmar == 's' || confirmar == 'S') {
        if (tipo == 1) { alternativas.eliminar(criterio); guardarRutas(alternativas); }
        else { combinadas.eliminarTodosSi(criterio); guardarCombinadas(combinadas); }
        cout << "[+] Ruta eliminada.\n";
    }
    pausar();
}

void mostrarCatalogo(const ListaSimple<Ruta>& alternativas, const ListaDoble<Ruta>& combinadas,
                     bool ordenar) {
    ListaSimple<Ruta> catalogo;
    // Mathias Raul Grovas Ormachea
    alternativas.recorrerConLambda([&](const Ruta& r) { catalogo.insertarFinal(r); });
    // Edgar Kevin Serna Poma
    combinadas.recorrerAdelante([&](const Ruta& r) { catalogo.insertarFinal(r); });
    if (ordenar) mostrarRutasOrdenadas(catalogo);
    else mostrarTodasLasRutas(catalogo);
}

void mostrarCatalogoPorDistancia(const ListaSimple<Ruta>& alternativas,
                                 const ListaDoble<Ruta>& combinadas) {
    ListaSimple<Ruta> catalogo;
    // Dylan Jean Pierre Ybanez Mejia
    alternativas.recorrerConLambda([&](const Ruta& r) { catalogo.insertarFinal(r); });
    // Mathias Raul Grovas Ormachea
    combinadas.recorrerAdelante([&](const Ruta& r) { catalogo.insertarFinal(r); });
    mostrarRutasOrdenadasPorDistancia(catalogo);
}

void menuAdministrador(Administrador& administrador, ListaSimple<Usuario>& listaUsuarios,
                       ListaSimple<Ruta>& alternativas, ListaDoble<Ruta>& combinadas,
                       Cola<ReporteTrafico>& reportes) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=========================================================\n";
        imprimirTituloAmarillo("       WAZE - NAVEGACION | USUARIO ADMINISTRATIVO\n");
        cout << "=========================================================\n";
        cout << " Bienvenido, " << administrador.getUsuario() << "\n";
        cout << "=========================================================\n";
        cout << "1. Registrar ruta alternativa\n";
        cout << "2. Registrar ruta combinada (ListaDoble<Ruta>)\n";
        cout << "3. Eliminar ruta\n";
        cout << "4. Ver todas las rutas\n";
        cout << "5. Ver rutas combinadas\n";
        cout << "6. Ordenar rutas por tiempo (QuickSort)\n";
        cout << "7. Ordenar usuarios por anio de nacimiento (Counting Sort)\n";
        cout << "8. Gestionar alertas de trafico\n";
        cout << "9. Historial de trafico\n";
        cout << "10. Mapa y sedes fijas\n";
        cout << "11. Cerrar sesion\nSeleccione una opcion: ";
        opcion = leerOpcion();
        switch (opcion) {
        case 1: registrarRutaAlternativa(alternativas); break;
        case 2: registrarCombinada(alternativas, combinadas); break;
        case 3: eliminarRuta(alternativas, combinadas); break;
        case 4: mostrarCatalogo(alternativas, combinadas, false); break;
        case 5: explorarCombinadas(combinadas, false); break;
        case 6: mostrarCatalogo(alternativas, combinadas, true); break;
        case 7: mostrarUsuariosOrdenadosPorAnio(listaUsuarios); break;
        case 8: {
            Usuario usuarioAdministrador("", administrador.getUsuario(), 0, "", "");
            menuCentroAlertas(usuarioAdministrador, reportes);
            break;
        }
        case 9: mostrarHistorialTrafico(); break;
        case 10: menuMapaAdministrativo(); break;
        case 11: break;
        default: cout << "[!] Opcion invalida.\n"; pausar();
        }
    } while (opcion != 11);
}
void menuSistemaWaze(Usuario& usuarioActivo,
                     ListaSimple<Usuario>& listaUsuarios,
                     ListaSimple<Ruta>& listaRutas,
                     ListaDoble<PuntoInteres>& listaPOI,
                     Cola<ReporteTrafico>& colaReportes, ListaDoble<Ruta>& combinadas) {
    int opcionWaze = 0;
    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("       WAZE - NAVEGACION | USUARIO GENERAL    \n");
        cout << "=============================================\n";
        cout << "  Bienvenido, " << usuarioActivo.getUsuario() << "!\n";
        cout << "=============================================\n";
        cout << "1. Buscar rutas alternativas (recursividad)\n";
        cout << "2. Buscar rutas combinadas (lista doble)\n";
        cout << "3. Ver todas las rutas\n";
        cout << "4. Ordenar rutas por tiempo (QuickSort)\n";
        cout << "5. Ordenar rutas por kilometros (Merge Sort)\n";
        cout << "6. Puntos de Interes Cercanos (lista doble)\n";
        cout << "7. Centro de Alertas de Trafico (cola FIFO)\n";
        cout << "8. Historial de Trafico (archivo)\n";
        cout << "9. Mi Perfil de Usuario\n";
        cout << "10. Mapa de sedes\n";
        cout << "11. Cerrar Sesion\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcionWaze)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcionWaze == 1) buscarRutasAlternativas(usuarioActivo, listaRutas);
        else if (opcionWaze == 2) explorarCombinadas(combinadas, true);
        else if (opcionWaze == 3) mostrarCatalogo(listaRutas, combinadas, false);
        else if (opcionWaze == 4) mostrarCatalogo(listaRutas, combinadas, true);
        else if (opcionWaze == 5) mostrarCatalogoPorDistancia(listaRutas, combinadas);
        else if (opcionWaze == 6) explorarPOI(listaPOI);
        else if (opcionWaze == 7) menuCentroAlertas(usuarioActivo, colaReportes, false);
        else if (opcionWaze == 8) mostrarHistorialTrafico();
        else if (opcionWaze == 9) {
            bool cuentaEliminada = menuPerfilUsuario(usuarioActivo, listaUsuarios);
            if (cuentaEliminada) return;
        }
        else if (opcionWaze == 10) menuMapaGeneral(usuarioActivo, colaReportes);
    } while (opcionWaze != 11);
}

} 

void ejecutarAplicacion() {
    ListaSimple<Usuario> listaUsuarios;
    ListaSimple<Administrador> listaAdministradores;
    ListaSimple<Ruta> listaRutas;
    ListaDoble<PuntoInteres> listaPOI;
    Cola<ReporteTrafico> colaReportes;

    ListaDoble<Ruta> combinadas;
    cargarCombinadas(combinadas);
    cargarUbicacionesMapa();
    cargarUsuarios(listaUsuarios);
    cargarAdministradores(listaAdministradores);
    cargarRutas(listaRutas);
    cargarPOI(listaPOI);
    cargarReportesPendientes(colaReportes);

    // Las nuevas rutas se registran entre ubicaciones del mapa.
    cargarPOIIniciales(listaPOI);
    cargarReportesIniciales(colaReportes);

    int opcion = 0;
    mostrarPantallaDeCarga();

    do {
        limpiarPantalla();
        cout << "=============================================\n";
        imprimirTituloAmarillo("       SISTEMA WAZE - VERSION FINAL           \n");
        cout << "=============================================\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Crear cuenta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opcion == 1) {
            int tipo = seleccionarTipoUsuario();
            if (tipo == 0) continue;
            limpiarPantalla();
            cout << "=============================================\n";
            imprimirTituloAmarillo(tipo == 1 ? "       INICIO SESION ADMINISTRADOR\n" :
                                             "       INICIO SESION USUARIO GENERAL\n");
            cout << "=============================================\n";
            string user, pass;
            cout << "Nombre de usuario: "; cin >> user;
            cout << "Contrasena: "; cin >> pass;
            if (tipo == 1) {
                // Edgar Kevin Serna Poma
                Administrador* administrador = listaAdministradores.buscar([&](const Administrador& a) {
                    return textoIgual(a.getUsuario(), user) && textoIgual(a.getContrasena(), pass);
                });
                if (administrador != nullptr) {
                    cout << "\n[+] Inicio de sesion exitoso.\n" << flush;
                    this_thread::sleep_for(chrono::seconds(1));
                    menuAdministrador(*administrador, listaUsuarios, listaRutas, combinadas, colaReportes);
                } else {
                    cout << "\n[!] Usuario o contrasena administrativos incorrectos.\n";
                    pausar();
                }
            } else {
                // Dylan Jean Pierre Ybanez Mejia
                Usuario* encontrado = listaUsuarios.buscar([&](const Usuario& u) {
                    return !esNombreAdministrativo(user) &&
                           u.getUsuario() == user && u.getContrasena() == pass;
                });
                if (encontrado) {
                    cout << "\n[+] Inicio de sesion exitoso.\n" << flush;
                    this_thread::sleep_for(chrono::seconds(1));
                    menuSistemaWaze(*encontrado, listaUsuarios, listaRutas, listaPOI,
                                    colaReportes, combinadas);
                } else {
                    cout << "\n[!] Usuario o contrasena incorrectos. Si no tiene cuenta,\n"
                            "    cree una desde el menu principal.\n";
                    pausar();
                }
            }
        }
        else if (opcion == 2) {
            limpiarPantalla();
            string correo, usuario, pass1, pass2, telefono;
            int anioNac = 0;
            cout << "=============================================\n";
            imprimirTituloAmarillo("                CREAR CUENTA                 \n");
            cout << "=============================================\n";
            cout << "Correo electronico: "; cin >> correo;
            cout << "Nombre de usuario: "; cin >> usuario;
            do {
                cout << "Anio de nacimiento (AAAA): ";
                if (!(cin >> anioNac)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    anioNac = 0;
                }
                if (anioNac < 1900 || anioNac > 2026)
                    cout << "[!] Ingrese un anio valido entre 1900 y 2026.\n";
            } while (anioNac < 1900 || anioNac > 2026);
            cout << "Contrasena: "; cin >> pass1;
            cout << "Confirme su contrasena: "; cin >> pass2;

            while (pass1 != pass2) {
                cout << "\n[!] Las contrasenas no coinciden. Intente de nuevo.\n";
                cout << "Contrasena: "; cin >> pass1;
                cout << "Confirme su contrasena: "; cin >> pass2;
            }

            cout << "Numero de celular: "; cin >> telefono;

            
            // Mathias Raul Grovas Ormachea
            Usuario* existente = listaUsuarios.buscar([&usuario](const Usuario& u) {
                return u.getUsuario() == usuario;
            });

            if (esNombreAdministrativo(usuario)) cout << "\n[!] Nombre reservado para administradores.\n";
            else if (existente != nullptr) cout << "\n[!] Ese nombre de usuario ya esta registrado.\n";
            else {
                listaUsuarios.insertarFinal(Usuario(correo, usuario, anioNac, pass1, telefono));
                guardarUsuarios(listaUsuarios);
                cout << "\n[+] Cuenta creada exitosamente. Ya puede iniciar sesion.\n";
            }
            pausar();
        }
        else if (opcion == 3) {
            limpiarPantalla();
            cout << "\nGracias por usar Waze. Buen viaje!\n\n";
        }
    } while (opcion != 3);
}
