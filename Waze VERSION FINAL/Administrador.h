#pragma once
#include <string>

class Administrador {
private:
    std::string correo;
    std::string usuario;
    std::string contrasena;
    std::string telefono;

public:
    Administrador(std::string c = "", std::string u = "",
                  std::string pass = "", std::string tel = "");

    std::string getCorreo() const;
    std::string getUsuario() const;
    std::string getContrasena() const;
    std::string getTelefono() const;
};
