#pragma once
#include <string>



class Sede {
private:
    std::string nombre;
    std::string distrito;
    std::string direccion;

public:
    Sede(std::string n = "", std::string d = "", std::string dir = "");

    std::string getNombre() const;
    std::string getDistrito() const;
    std::string getDireccion() const;
};
