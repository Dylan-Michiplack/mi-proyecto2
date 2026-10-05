#pragma once
#include "Nodo.h"
#include <functional>


template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;
    int cantidad;

public:
    ListaDoble() : cabeza(nullptr), cola(nullptr), cantidad(0) {}
    ~ListaDoble() { vaciar(); }

    void vaciar() {
        while (cabeza != nullptr) {
            NodoDoble<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cola = nullptr;
        cantidad = 0;
    }

    bool esVacia() const { return cabeza == nullptr; }
    int longitud() const { return cantidad; }

    void insertarFinal(T valor) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        if (cabeza == nullptr) {
            cabeza = cola = nuevo;
        }
        else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        cantidad++;
    }

    NodoDoble<T>* getCabeza() const { return cabeza; }
    NodoDoble<T>* getCola() const { return cola; }

    void recorrerAdelante(std::function<void(const T&)> accion) const {
        NodoDoble<T>* aux = cabeza;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->siguiente;
        }
    }

    T* buscar(std::function<bool(const T&)> criterio) const {
        NodoDoble<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return &(aux->dato);
            aux = aux->siguiente;
        }
        return nullptr;
    }



    int contarSi(std::function<bool(const T&)> criterio) const {
        int total = 0;
        NodoDoble<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) total++;
            aux = aux->siguiente;
        }
        return total;
    }

    bool existeSi(std::function<bool(const T&)> criterio) const {
        NodoDoble<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return true;
            aux = aux->siguiente;
        }
        return false;
    }


    T* buscarUltimoSi(std::function<bool(const T&)> criterio) const {
        NodoDoble<T>* aux = cola;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return &(aux->dato);
            aux = aux->anterior;
        }
        return nullptr;
    }


    int eliminarTodosSi(std::function<bool(const T&)> criterio) {
        int eliminados = 0;
        NodoDoble<T>* actual = cabeza;

        while (actual != nullptr) {
            NodoDoble<T>* siguiente = actual->siguiente;

            if (criterio(actual->dato)) {
                if (actual->anterior != nullptr)
                    actual->anterior->siguiente = actual->siguiente;
                else
                    cabeza = actual->siguiente;

                if (actual->siguiente != nullptr)
                    actual->siguiente->anterior = actual->anterior;
                else
                    cola = actual->anterior;

                delete actual;
                cantidad--;
                eliminados++;
            }

            actual = siguiente;
        }
        return eliminados;
    }

    bool reemplazarPrimeroSi(std::function<bool(const T&)> criterio, T nuevoValor) {
        NodoDoble<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) {
                aux->dato = nuevoValor;
                return true;
            }
            aux = aux->siguiente;
        }
        return false;
    }


    bool insertarSiNoExiste(T valor, std::function<bool(const T&)> criterioExistencia) {
        if (existeSi(criterioExistencia)) return false;
        insertarFinal(valor);
        return true;
    }



    bool insertarAntesDe(std::function<bool(const T&)> criterio, T valor) {
        NodoDoble<T>* actual = cabeza;
        while (actual != nullptr && !criterio(actual->dato)) {
            actual = actual->siguiente;
        }
        if (actual == nullptr) return false;

        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        nuevo->siguiente = actual;
        nuevo->anterior = actual->anterior;

        if (actual->anterior != nullptr)
            actual->anterior->siguiente = nuevo;
        else
            cabeza = nuevo;

        actual->anterior = nuevo;
        cantidad++;
        return true;
    }

    bool insertarDespuesDe(std::function<bool(const T&)> criterio, T valor) {
        NodoDoble<T>* actual = cabeza;
        while (actual != nullptr && !criterio(actual->dato)) {
            actual = actual->siguiente;
        }
        if (actual == nullptr) return false;

        NodoDoble<T>* nuevo = new NodoDoble<T>(valor);
        nuevo->anterior = actual;
        nuevo->siguiente = actual->siguiente;

        if (actual->siguiente != nullptr)
            actual->siguiente->anterior = nuevo;
        else
            cola = nuevo;

        actual->siguiente = nuevo;
        cantidad++;
        return true;
    }

    
    void invertirEnlaces() {
        NodoDoble<T>* actual = cabeza;

        while (actual != nullptr) {
            NodoDoble<T>* temp = actual->anterior;
            actual->anterior = actual->siguiente;
            actual->siguiente = temp;
            actual = actual->anterior;
        }

        NodoDoble<T>* temp = cabeza;
        cabeza = cola;
        cola = temp;
    }
};
