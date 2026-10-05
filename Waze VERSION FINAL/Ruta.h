#pragma once
#include <string>
#include <vector>
#include "Sede.h"
#include "EstadoRuta.h"
#include "TramoRuta.h"



class Ruta {
private:
    std::string nombre;
    Sede origen;                
    Sede destino;               
    EstadoRuta estado;         
    TramoRuta tramoPrincipal;   
    double distanciaKm;
    int tiempoMin;
    std::vector<std::string> puntosPaso;
    std::string sedeIntermedia;

public:
    Ruta(std::string n = "", std::string o = "", std::string d = "",
         double distancia = 0.0, int tiempo = 0,
         const std::vector<std::string>& puntos = {},
         const std::string& intermedia = "");
    Ruta(std::string n, const Sede& o, const Sede& d,
         double distancia, int tiempo, const EstadoRuta& e,
         const TramoRuta& tramo, const std::vector<std::string>& puntos = {},
         const std::string& intermedia = "");

    std::string getNombre() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    double getDistanciaKm() const;
    int getTiempoMin() const;
    const std::vector<std::string>& getPuntosPaso() const;
    std::string getSedeIntermedia() const;

    const Sede& getSedeOrigen() const;
    const Sede& getSedeDestino() const;
    const EstadoRuta& getEstado() const;
    const TramoRuta& getTramoPrincipal() const;

    void mostrarInfo() const;
};
