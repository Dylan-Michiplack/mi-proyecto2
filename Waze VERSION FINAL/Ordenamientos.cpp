#include "Ordenamientos.h"
#include "Utilidades.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Edgar Kevin Serna Poma
int particionRutas(Ruta** arreglo, int low, int high) {
    Ruta* pivote = arreglo[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arreglo[j]->getTiempoMin() <= pivote->getTiempoMin()) {
            i++;
            Ruta* temp = arreglo[i];
            arreglo[i] = arreglo[j];
            arreglo[j] = temp;
        }
    }

    Ruta* temp = arreglo[i + 1];
    arreglo[i + 1] = arreglo[high];
    arreglo[high] = temp;
    return i + 1;
}

void quickSortRutas(Ruta** arreglo, int low, int high) {
    if (low < high) {
        int pi = particionRutas(arreglo, low, high);
        quickSortRutas(arreglo, low, pi - 1);
        quickSortRutas(arreglo, pi + 1, high);
    }
}

void mostrarRutasOrdenadas(ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("      RUTAS ORDENADAS POR TIEMPO - QSORT     \n");
    cout << "=============================================\n\n";

    int n = rutas.longitud();
    if (n == 0) {
        cout << "[!] No existen rutas registradas.\n";
        pausar();
        return;
    }

    Ruta** arreglo = new Ruta*[n];
    for (int i = 0; i < n; i++) arreglo[i] = rutas.obtenerPos(i);

    quickSortRutas(arreglo, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ".\n";
        arreglo[i]->mostrarInfo();
        cout << "---------------------------------------------\n";
    }

    delete[] arreglo;
    pausar();
}

// Mathias Raul Grovas Ormachea
void countingSortUsuariosPorAnio(Usuario** arreglo, int n) {
    if (n <= 1) return;

    const int ANIO_MINIMO = 1900;
    const int ANIO_MAXIMO = 2026;
    const int RANGO = ANIO_MAXIMO - ANIO_MINIMO + 1;
    const int SIN_ANIO = RANGO;

    vector<int> conteo(RANGO + 1, 0);
    vector<Usuario*> salida(n, nullptr);

    for (int i = 0; i < n; i++) {
        int anio = arreglo[i]->getAnioNacimiento();
        int indice = (anio >= ANIO_MINIMO && anio <= ANIO_MAXIMO)
            ? anio - ANIO_MINIMO : SIN_ANIO;
        conteo[indice]++;
    }

    for (int i = 1; i <= SIN_ANIO; i++)
        conteo[i] += conteo[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        int anio = arreglo[i]->getAnioNacimiento();
        int indice = (anio >= ANIO_MINIMO && anio <= ANIO_MAXIMO)
            ? anio - ANIO_MINIMO : SIN_ANIO;
        salida[conteo[indice] - 1] = arreglo[i];
        conteo[indice]--;
    }

    for (int i = 0; i < n; i++)
        arreglo[i] = salida[i];
}

void mostrarUsuariosOrdenadosPorAnio(ListaSimple<Usuario>& usuarios) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo(" USUARIOS POR ANIO NACIMIENTO - COUNTING SORT\n");
    cout << "=============================================\n\n";

    int n = usuarios.longitud();
    if (n == 0) {
        cout << "[!] No existen usuarios registrados.\n";
        pausar();
        return;
    }

    Usuario** arreglo = new Usuario*[n];
    for (int i = 0; i < n; i++) arreglo[i] = usuarios.obtenerPos(i);

    countingSortUsuariosPorAnio(arreglo, n);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". Usuario: " << arreglo[i]->getUsuario() << "\n";
        cout << "   Correo : " << arreglo[i]->getCorreo() << "\n";
        if (arreglo[i]->getAnioNacimiento() >= 1900)
            cout << "   Anio de nacimiento: " << arreglo[i]->getAnioNacimiento() << "\n";
        else
            cout << "   Anio de nacimiento: No registrado\n";
        cout << "---------------------------------------------\n";
    }

    delete[] arreglo;
    pausar();
}

// Dylan Jean Pierre Ybanez Mejia
void mergeRutasPorDistancia(Ruta** arreglo, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    Ruta** L = new Ruta*[n1];
    Ruta** R = new Ruta*[n2];

    for (int i = 0; i < n1; i++) L[i] = arreglo[izquierda + i];
    for (int j = 0; j < n2; j++) R[j] = arreglo[medio + 1 + j];

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < n1 && j < n2) {
        if (L[i]->getDistanciaKm() <= R[j]->getDistanciaKm()) {
            arreglo[k] = L[i];
            i++;
        }
        else {
            arreglo[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arreglo[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arreglo[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortRutasPorDistancia(Ruta** arreglo, int izquierda, int derecha) {
    if (izquierda >= derecha) return;

    int medio = izquierda + (derecha - izquierda) / 2;
    mergeSortRutasPorDistancia(arreglo, izquierda, medio);
    mergeSortRutasPorDistancia(arreglo, medio + 1, derecha);
    mergeRutasPorDistancia(arreglo, izquierda, medio, derecha);
}

void mostrarRutasOrdenadasPorDistancia(ListaSimple<Ruta>& rutas) {
    limpiarPantalla();
    cout << "=============================================\n";
    imprimirTituloAmarillo("     RUTAS POR KILOMETROS - MERGE SORT       \n");
    cout << "=============================================\n\n";

    int n = rutas.longitud();
    if (n == 0) {
        cout << "[!] No existen rutas registradas.\n";
        pausar();
        return;
    }

    Ruta** arreglo = new Ruta*[n];
    for (int i = 0; i < n; i++) arreglo[i] = rutas.obtenerPos(i);

    mergeSortRutasPorDistancia(arreglo, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arreglo[i]->getNombre() << "\n";
        cout << "   " << arreglo[i]->getOrigen();
        if (!arreglo[i]->getSedeIntermedia().empty())
            cout << " -> " << arreglo[i]->getSedeIntermedia();
        cout << " -> " << arreglo[i]->getDestino() << "\n";
        cout << "   Distancia: " << fixed << setprecision(1)
             << arreglo[i]->getDistanciaKm() << " km\n";
        cout << "   Tiempo   : " << arreglo[i]->getTiempoMin() << " min\n";
        cout << "---------------------------------------------\n";
    }

    delete[] arreglo;
    pausar();
}
