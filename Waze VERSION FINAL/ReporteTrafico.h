#pragma once
#include <string>
#include "Sede.h"



class ReporteTrafico {
private:
    std::string tipo;
    Sede ubicacion; 
    int gravedad;

public:
    ReporteTrafico(std::string t = "", std::string u = "", int g = 1);
    ReporteTrafico(std::string t, const Sede& u, int g = 1);

    void mostrarInfo() const;
    std::string getTipo() const;
    std::string getUbicacion() const;
    int getGravedad() const;
    const Sede& getSede() const;
};
