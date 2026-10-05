#pragma once
#include <string>


class PerfilUsuario {
private:
    std::string nombreUsuario;
    std::string nombreVisible;
    std::string preferenciaRuta;

public:
    PerfilUsuario(std::string usuario = "", std::string nombre = "", std::string preferencia = "");

    std::string getNombreUsuario() const;
    std::string getNombreVisible() const;
    std::string getPreferenciaRuta() const;

    void setNombreUsuario(const std::string& usuario);
    void setNombreVisible(const std::string& nombre);
    void setPreferenciaRuta(const std::string& preferencia);
};
