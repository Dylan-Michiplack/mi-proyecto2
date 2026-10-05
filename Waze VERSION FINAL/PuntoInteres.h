#pragma once
#include <string>
#include "Sede.h"

class PuntoInteres {
private:
    std::string nombre;
    std::string tipo;
    std::string distancia;
    Sede sedeAsociada; 

public:
    PuntoInteres(std::string n = "", std::string t = "", std::string d = "");
    PuntoInteres(std::string n, std::string t, std::string d, const Sede& sede);

    std::string getNombre() const;
    std::string getTipo() const;
    std::string getDistancia() const;
    const Sede& getSede() const;
    void mostrar() const;
};
