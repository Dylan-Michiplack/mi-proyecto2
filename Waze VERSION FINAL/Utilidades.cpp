#include "Utilidades.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cin.get();
}

string aMinusculas(string texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        texto[i] = static_cast<char>(tolower(static_cast<unsigned char>(texto[i])));
    }
    return texto;
}

bool textoIgual(const string& a, const string& b) {
    return aMinusculas(a) == aMinusculas(b);
}

bool archivoExiste(const string& nombre) {
    ifstream archivo(nombre);
    bool existe = archivo.good();
    archivo.close();
    return existe;
}

string fechaHoraActual() {
    time_t ahora = time(nullptr);
    tm tiempoLocal;
#ifdef _WIN32
    localtime_s(&tiempoLocal, &ahora);
#else
    localtime_r(&ahora, &tiempoLocal);
#endif
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", &tiempoLocal);
    return string(buffer);
}


void imprimirTituloAmarillo(const std::string& texto) {
#ifdef _WIN32
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (GetConsoleScreenBufferInfo(consola, &info)) {
        WORD original = info.wAttributes;
        WORD amarillo = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(consola, amarillo);
        cout << texto;
        SetConsoleTextAttribute(consola, original);
        return;
    }
    cout << texto;
#else
    cout << "\033[93m" << texto << "\033[0m";
#endif
}
