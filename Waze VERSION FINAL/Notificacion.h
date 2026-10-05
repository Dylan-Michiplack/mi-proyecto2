#pragma once
#include <string>
#include "Usuario.h"
#include "ReporteTrafico.h"


class Notificacion {
private:
    const Usuario* destinatario; 
    std::string usuarioTexto;
    std::string mensaje;
    ReporteTrafico reporte;     
    bool leida;

public:
    Notificacion(std::string u = "", std::string m = "", std::string ubic = "", bool estado = false);
    Notificacion(const Usuario& u, std::string m, const ReporteTrafico& r, bool estado = false);

    std::string getUsuario() const;
    std::string getMensaje() const;
    std::string getUbicacion() const;
    bool estaLeida() const;
    const Usuario* getDestinatario() const;
    const ReporteTrafico& getReporte() const;
    void marcarComoLeida();
};
