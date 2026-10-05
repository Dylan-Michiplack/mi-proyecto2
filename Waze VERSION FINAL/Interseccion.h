#pragma once
#include <string>
#include "Avenida.h"



class Interseccion {
private:
    Avenida avenidaUno; 
    Avenida avenidaDos;
    std::string referencia;

public:
    Interseccion(std::string a1 = "", std::string a2 = "", std::string ref = "");
    Interseccion(const Avenida& a1, const Avenida& a2, std::string ref = "");

    std::string getAvenidaUno() const;
    std::string getAvenidaDos() const;
    std::string getReferencia() const;
    const Avenida& getAvenidaUnoEntidad() const;
    const Avenida& getAvenidaDosEntidad() const;
};
