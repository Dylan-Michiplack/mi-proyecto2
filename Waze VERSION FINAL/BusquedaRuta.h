#pragma once
#include <string>
#include "Usuario.h"
#include "Sede.h"
#include "Ruta.h"


class BusquedaRuta {
private:
    const Usuario* usuarioRef;  
    std::string usuarioTexto;
    Sede origen;               
    Sede destino;               
    Ruta rutaSeleccionada;      
    bool tieneRuta;

public:
    BusquedaRuta(std::string u = "", std::string o = "", std::string d = "", std::string ruta = "");
    BusquedaRuta(const Usuario& u, const Sede& o, const Sede& d);
    BusquedaRuta(const Usuario& u, const Sede& o, const Sede& d, const Ruta& ruta);

    std::string getUsuario() const;
    std::string getOrigen() const;
    std::string getDestino() const;
    std::string getRutaSeleccionada() const;
    const Usuario* getUsuarioEntidad() const;
    const Sede& getSedeOrigen() const;
    const Sede& getSedeDestino() const;
    const Ruta* getRutaSeleccionadaEntidad() const;
};
