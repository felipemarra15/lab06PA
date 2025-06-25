#include "producto.h"

// CONSTRUCTOR:
Producto::Producto(int codigo, string nombre, float precio) {
    this->codigo = codigo;
    this->nombre = nombre;
    this->precio = precio;
}

// DESTRUCTOR:
Producto::~Producto() {
    // Destructor vacío, no hay recursos que liberar
    // Si hubiera recursos dinámicos, se liberarían aquí
}

// GETTERS:
int Producto::getCodigo() {
    return this->codigo;
}

string Producto::getNombre() {
    return this->nombre;
}

float Producto::getPrecio() {
    return this->precio;
}

// SETTERS:

void Producto::setCodigo(int codigo) {
    this->codigo = codigo;
}

void Producto::setNombre(string nombre) {
    this->nombre = nombre;
}

void Producto::setPrecio(float precio) {
    this->precio = precio;
}

bool Producto::esProducto(string codigo) {
    return this->codigo == atoi(codigo.c_str());
}

dtProducto* Producto::mostrarFactura() {
    return new dtProducto(this->codigo, this->nombre, this->precio);
}