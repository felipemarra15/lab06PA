#include "dtCantidadSimple.h"

// Constructor
dtCantidadSimple::dtCantidadSimple(Producto* producto, int cantidad) {
    this->producto = producto;
    this->cantidad = cantidad;
}

// Destructor
dtCantidadSimple::~dtCantidadSimple() {
    cout << "Destrucor de dtCantidadSimple" << endl;
    delete producto; // Liberar memoria del producto
}

// Getters
Producto* dtCantidadSimple::getProducto() {
    return this->producto;
}

int dtCantidadSimple::getCantidad() {
    return this->cantidad;
}
