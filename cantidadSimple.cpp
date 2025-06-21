#include "cantidadSimple.h"

// Constructor
CantidadSimple::CantidadSimple(Producto* producto, int cantidad) {
    this->producto = producto;
    this->cantidad = cantidad;
}

// Destructor
CantidadSimple::~CantidadSimple() {
    cout << "Destructor de CantidadSimple" << endl;
    delete producto;
}

// Getters
Producto* CantidadSimple::getProducto() {
    return this->producto;
}

int CantidadSimple::getCantidad() {
    return this->cantidad;
}
