#pragma once
#include "Nodo.h"
#include <functional>


template <typename T>
class ListaSimple {
private:
    Nodo<T>* cabeza;
    int cantidad;

    Nodo<T>* buscarRecursivo(Nodo<T>* actual,
                             std::function<bool(const T&)> criterio) const {
        if (actual == nullptr) return nullptr; 
        if (criterio(actual->dato)) return actual;
        return buscarRecursivo(actual->siguiente, criterio); 
    }

    bool eliminarRecursivo(Nodo<T>*& actual,
                           std::function<bool(const T&)> criterio) {
        if (actual == nullptr) return false; 
        if (criterio(actual->dato)) {
            Nodo<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
            cantidad--;
            return true;
        }
        return eliminarRecursivo(actual->siguiente, criterio); 
    }

    int buscarTodosRecursivoAux(Nodo<T>* actual,
                                std::function<bool(const T&)> criterio,
                                std::function<void(const T&)> accion) const {
        if (actual == nullptr) return 0; 

        int encontrado = 0;
        if (criterio(actual->dato)) {
            accion(actual->dato);
            encontrado = 1;
        }

        return encontrado + buscarTodosRecursivoAux(actual->siguiente, criterio, accion);
    }

public:
    ListaSimple() : cabeza(nullptr), cantidad(0) {}
    ~ListaSimple() { vaciar(); }

    void vaciar() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        cantidad = 0;
    }

    bool esVacia() const { return cabeza == nullptr; }
    int longitud() const { return cantidad; }

    void insertar(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
    }

    void insertarFinal(T valor) {
        Nodo<T>* nuevo = new Nodo<T>(valor);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            Nodo<T>* aux = cabeza;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
        cantidad++;
    }

    T* buscar(std::function<bool(const T&)> criterio) const {
        Nodo<T>* res = buscarRecursivo(cabeza, criterio);
        return (res != nullptr) ? &(res->dato) : nullptr;
    }

    bool eliminar(std::function<bool(const T&)> criterio) {
        return eliminarRecursivo(cabeza, criterio);
    }

    void recorrerConLambda(std::function<void(const T&)> accion) const {
        Nodo<T>* aux = cabeza;
        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->siguiente;
        }
    }

    int buscarTodosRecursivo(std::function<bool(const T&)> criterio,
                             std::function<void(const T&)> accion) const {
        return buscarTodosRecursivoAux(cabeza, criterio, accion);
    }

    T* obtenerPos(int pos) {
        if (pos < 0 || pos >= cantidad) return nullptr;
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < pos; i++) aux = aux->siguiente;
        return &(aux->dato);
    }

    const T* obtenerPos(int pos) const {
        if (pos < 0 || pos >= cantidad) return nullptr;
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < pos; i++) aux = aux->siguiente;
        return &(aux->dato);
    }




    int contarSi(std::function<bool(const T&)> criterio) const {
        int total = 0;
        Nodo<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) total++;
            aux = aux->siguiente;
        }
        return total;
    }

    bool existeSi(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = cabeza;
        while (aux != nullptr) {
            if (criterio(aux->dato)) return true;
            aux = aux->siguiente;
        }
        return false;
    }

    T* buscarUltimoSi(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = cabeza;
        Nodo<T>* ultimo = nullptr;
        while (aux != nullptr) {
            if (criterio(aux->dato)) ultimo = aux;
            aux = aux->siguiente;
        }
        return (ultimo != nullptr) ? &(ultimo->dato) : nullptr;
    }

 
    int eliminarTodosSi(std::function<bool(const T&)> criterio) {
        int eliminados = 0;
        Nodo<T>* actual = cabeza;
        Nodo<T>* anterior = nullptr;

        while (actual != nullptr) {
            if (criterio(actual->dato)) {
                Nodo<T>* temp = actual;
                actual = actual->siguiente;

                if (anterior == nullptr)
                    cabeza = actual;
                else
                    anterior->siguiente = actual;

                delete temp;
                cantidad--;
                eliminados++;
            }
            else {
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        return eliminados;
    }

    bool reemplazarPrimeroSi(std::function<bool(const T&)> criterio, T nuevoValor) {
        Nodo<T>* aux = cabeza;
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


    void invertir() {
        Nodo<T>* anterior = nullptr;
        Nodo<T>* actual = cabeza;

        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            actual->siguiente = anterior;
            anterior = actual;
            actual = siguiente;
        }
        cabeza = anterior;
    }

   
    int posicionPrimeraCoincidencia(std::function<bool(const T&)> criterio) const {
        Nodo<T>* aux = cabeza;
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

        Nodo<T>* aux = cabeza;
        for (int i = 0; i < pos; i++) aux = aux->siguiente;

        while (aux != nullptr) {
            accion(aux->dato);
            aux = aux->siguiente;
        }
    }
};
