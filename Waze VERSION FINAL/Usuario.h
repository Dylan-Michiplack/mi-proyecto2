#pragma once
#include <string>
#include "PerfilUsuario.h"


class Usuario {
private:
    std::string correo;
    std::string usuario;
    int anioNacimiento;
    std::string contrasena;
    std::string telefono;
    PerfilUsuario perfil;

public:
    Usuario(std::string c = "", std::string u = "", int anio = 0,
            std::string pass = "", std::string tel = "");

    std::string getUsuario() const;
    std::string getContrasena() const;
    std::string getCorreo() const;
    std::string getTelefono() const;
    int getAnioNacimiento() const;

    const PerfilUsuario& getPerfil() const;
    PerfilUsuario& getPerfil();

    void setUsuario(const std::string& nuevoUser);
    void setContrasena(const std::string& nuevaPass);
};
