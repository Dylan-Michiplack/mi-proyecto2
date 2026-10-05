#pragma once
#include "Nodo.h"
#include <functional>

//COLA FIFO
template <typename T>
class Cola {
private:
    Nodo<T>* frenteNodo;
    Nodo<T>* finalNodo;
    int cantidad;

public:
    Cola() : frenteNodo(nullptr), finalNodo(nullptr), cantidad(0) {}
    ~Cola() { vaciar(); }

    void vaciar() {
        while (frenteNodo != nullptr) {
            Nodo<T>* temp = frenteNodo;
            frenteNodo = frenteNodo->siguiente;
            delete temp;
        }
        finalNodo = nullptr;
        cantidad = 0;
    }

    bool esVacia() const { return frenteNodo == nullptr; }
    int size() const { return cantidad; }

    void enqueue(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (finalNodo == nullptr) {
            frenteNodo = finalNodo = nuevo;
        }
        else {
            finalNodo->siguiente = nuevo;
            finalNodo = nuevo;
        }
        cantidad++;
    }

    bool dequeue(T& salida) {
        if (frenteNodo == nullptr) return false;

        Nodo<T>* temp = frenteNodo;
        salida = frenteNodo->dato;
        frenteNodo = frenteNodo->siguiente;
        delete temp;
        cantidad--;

        if (frenteNodo == nullptr) finalNodo = nullptr;
        return true;
    }

    T* front() const {
        return (frenteNodo != nullptr) ? &(frenteNodo->dato) : nullptr;
    }

    void recorrerConLambda(std::function<void(const T&)> accion) const {
        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->siguiente;
        }
    }




    int contarSi(std::function<bool(const T&)> criterio) const {
        int total = 0;
        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            if (criterio(aux->dato)) total++;
            aux = aux->siguiente;
        }
        return total;
    }

    bool existeSi(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return true;
            aux = aux->siguiente;
        }
        return false;
    }

  
    T* buscarPrimeroSi(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return &(aux->dato);
            aux = aux->siguiente;
        }
        return nullptr;
    }



    T* obtenerPos(int pos) const {
        if (pos < 0 || pos >= cantidad) return nullptr;

        Nodo<T>* aux = frenteNodo;
        for (int i = 0; i < pos; i++) aux = aux->siguiente;
        return &(aux->dato);
    }

    int posicionPrimeraCoincidencia(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = frenteNodo;
        int posicion = 0;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return posicion;
            posicion++;
            aux = aux->siguiente;
        }
        return -1;
    }

 
    void recorrerDesde(int pos, std::function<void(const T&)> accion) const {
        if (pos < 0 || pos >= cantidad) return;

        Nodo<T>* aux = frenteNodo;
        for (int i = 0; i < pos; i++) aux = aux->siguiente;

        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->siguiente;
        }
    }


    bool moverFrenteAlFinal() {
        if (frenteNodo == nullptr || frenteNodo == finalNodo) return false;

        Nodo<T>* primero = frenteNodo;
        frenteNodo = frenteNodo->siguiente;
        primero->siguiente = nullptr;
        finalNodo->siguiente = primero;
        finalNodo = primero;
        return true;
    }

    bool reemplazarPrimeroSi(std::function<bool(const T&)> criterio, T nuevoValor) {
        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            if (criterio(aux->dato)) {
                aux->dato = nuevoValor;
                return true;
            }
            aux = aux->siguiente;
        }
        return false;
    }

    void copiarEn(Cola<T>& destino) const {
        if (&destino == this) return;

        Nodo<T>* aux = frenteNodo;
        while (aux != nullptr) {
            destino.enqueue(aux->dato);
            aux = aux->siguiente;
        }
    }
};
