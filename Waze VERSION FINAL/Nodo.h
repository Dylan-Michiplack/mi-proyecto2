#pragma once

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(T val) : dato(val), siguiente(nullptr) {}
};

template <typename T>
struct NodoDoble {
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

    NodoDoble(T val) : dato(val), siguiente(nullptr), anterior(nullptr) {}
};
