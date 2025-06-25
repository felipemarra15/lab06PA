#include "dtCantidadSimple.h"

// Constructor
dtCantidadSimple::dtCantidadSimple(Producto* producto, int cantidad) {
    this->producto = producto;
    this->cantidad = cantidad;
}

// Destructor
dtCantidadSimple::~dtCantidadSimple() {
    // Liberar memoria del producto si es necesario
    if (producto != NULL) {
        producto = NULL; // Asumimos que el producto fue creado dinámicamente y se debe liberar
        delete producto; // Asumiendo que el producto fue creado dinámicamente
    }
}

// Getters
Producto* dtCantidadSimple::getProducto() {
    return this->producto;
}

int dtCantidadSimple::getCantidad() {
    return this->cantidad;
}
