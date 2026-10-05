#include "Administrador.h"

using namespace std;

Administrador::Administrador(string c, string u, string pass, string tel)
    : correo(c), usuario(u), contrasena(pass), telefono(tel) {}

string Administrador::getCorreo() const { return correo; }
string Administrador::getUsuario() const { return usuario; }
string Administrador::getContrasena() const { return contrasena; }
string Administrador::getTelefono() const { return telefono; }
