#pragma once
#include <string>
#include "Usuario.h"
#include "Ruta.h"


class RutaFavorita {
private:
    const Usuario* usuarioRef; 
    std::string usuarioTexto;
    Ruta ruta;                 

public:
    RutaFavorita(std::string u = "", std::string ruta = "");
    RutaFavorita(const Usuario& u, const Ruta& r);

    std::string getUsuario() const;
    std::string getNombreRuta() const;
    const Usuario* getUsuarioEntidad() const;
    const Ruta& getRutaEntidad() const;
};
