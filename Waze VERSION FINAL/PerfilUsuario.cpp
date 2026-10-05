#include "PerfilUsuario.h"

using namespace std;

PerfilUsuario::PerfilUsuario(string usuario, string nombre, string preferencia)
    : nombreUsuario(usuario), nombreVisible(nombre), preferenciaRuta(preferencia) {}

string PerfilUsuario::getNombreUsuario() const { return nombreUsuario; }
string PerfilUsuario::getNombreVisible() const { return nombreVisible; }
string PerfilUsuario::getPreferenciaRuta() const { return preferenciaRuta; }
void PerfilUsuario::setNombreUsuario(const string& usuario) { nombreUsuario = usuario; }
void PerfilUsuario::setNombreVisible(const string& nombre) { nombreVisible = nombre; }
void PerfilUsuario::setPreferenciaRuta(const string& preferencia) { preferenciaRuta = preferencia; }
