#pragma once
#include <string>
#include "BusquedaRuta.h"



class HistorialBusqueda {
private:
    BusquedaRuta busqueda; 
    std::string fechaHora;

public:
    HistorialBusqueda(std::string u = "", std::string o = "", std::string d = "", std::string fecha = "");
    HistorialBusqueda(const BusquedaRuta& b, std::string fecha = "");

    std::string getUsuario() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    std::string getFechaHora() const;
    const BusquedaRuta& getBusqueda() const;
};
