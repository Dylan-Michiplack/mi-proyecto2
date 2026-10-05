#pragma once
#include <string>
#include "Avenida.h"
#include "Interseccion.h"


class TramoRuta {
private:
    std::string nombreRuta;
    Avenida avenida;            
    Interseccion interseccion;  
    double distanciaKm;
    int orden;

public:
    TramoRuta(std::string ruta = "", std::string av = "", double distancia = 0.0, int pos = 0);
    TramoRuta(std::string ruta, const Avenida& av, const Interseccion& inter,
              double distancia = 0.0, int pos = 0);

    std::string getNombreRuta() const;
    std::string getAvenida() const;
    double getDistanciaKm() const;
    int getOrden() const;
    const Avenida& getAvenidaEntidad() const;
    const Interseccion& getInterseccion() const;
};
