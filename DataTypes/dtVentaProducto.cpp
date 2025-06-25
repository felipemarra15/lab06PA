#include "dtVentaProducto.h"
#include "../ICollection/interfaces/IIterator.h"

// Constructor
dtVentaProducto::dtVentaProducto(dtProducto *producto, int cantidad){
    this->cantidad = cantidad;
    this->producto = producto;
}

// Destructor
dtVentaProducto::~dtVentaProducto(){
    // Liberar memoria del producto si es necesario
    if (producto != NULL) {
        producto = NULL; // Asegurarse de que no apunte a memoria liberada
        delete producto; // Asumiendo que el producto fue creado dinámicamente
    }
}

// Getters

int dtVentaProducto::getCantidad(){
    return this->cantidad;
}

dtProducto* dtVentaProducto::getProducto(){
    return this->producto;
}