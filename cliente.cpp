#include "cliente.h"
#include <iostream>

// Constructor
Cliente::Cliente(string ci, string nombre, string telefono, direccion *direccion){
    this->ci = ci;
    this->nombre = nombre;
    this->telefono = telefono;
    this->dir = direccion; // Asignar la dirección
}

// Destructor
Cliente::~Cliente() {
    std::cout << "Destructor de Cliente" << std::endl;
    delete dir; // Liberar memoria de la dirección
}

// Getters
string Cliente::getCi() {
    return this->ci;
}

string Cliente::getNombre() {
    return this->nombre;
}

string Cliente::getTelefono() {
    return this->telefono;
}

direccion* Cliente::getDireccion() {
    return this->dir;
}

// Setters
void Cliente::setCi(string& ci) {
    this->ci = ci;
}

void Cliente::setNombre(string& nombre) {
    this->nombre = nombre;
}

void Cliente::setTelefono(string& telefono) {
    this->telefono = telefono;
}

void Cliente::setDireccion(direccion* direccion) {
    this->dir = direccion;
}
