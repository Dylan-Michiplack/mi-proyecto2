#pragma once
#include <string>
#include "ReporteTrafico.h"




class HistorialTrafico {
private:
    std::string fechaHora;
    std::string estado;
    ReporteTrafico reporte; 

public:
    HistorialTrafico(std::string fecha = "", std::string e = "", std::string tipo = "",
                     std::string u = "", int g = 0);
    HistorialTrafico(std::string fecha, std::string e, const ReporteTrafico& r);

    std::string getFechaHora() const;
    std::string getEstado() const;
    std::string getTipoReporte() const;
    std::string getUbicacion() const;
    int getGravedad() const;
    const ReporteTrafico& getReporte() const;
};
