#include "simple.h"

Simple::Simple(int codigo, string nombre, float precio): Producto(codigo, nombre, precio) {

}

Simple::~Simple() {
    cout << "Destructor de Simple" << endl;
}

dtSimple* Simple::getProducto() {
    return new dtSimple(this->getCodigo(), this->getNombre(), this->getPrecio());
}