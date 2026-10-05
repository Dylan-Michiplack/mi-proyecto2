#include "Usuario.h"

using namespace std;

Usuario::Usuario(string c, string u, int anio,
                 string pass, string tel)
    : correo(c), usuario(u), anioNacimiento(anio), contrasena(pass), telefono(tel),
      perfil(u, u, "Menor tiempo") {}

string Usuario::getUsuario() const { return usuario; }
string Usuario::getContrasena() const { return contrasena; }
string Usuario::getCorreo() const { return correo; }
string Usuario::getTelefono() const { return telefono; }
int Usuario::getAnioNacimiento() const { return anioNacimiento; }
const PerfilUsuario& Usuario::getPerfil() const { return perfil; }
PerfilUsuario& Usuario::getPerfil() { return perfil; }

void Usuario::setUsuario(const string& nuevoUser) {
    usuario = nuevoUser;
    perfil.setNombreUsuario(nuevoUser);
    perfil.setNombreVisible(nuevoUser);
}

void Usuario::setContrasena(const string& nuevaPass) { contrasena = nuevaPass; }
