#include "dtVentaProducto.h"

// Constructor
dtVentaProducto::dtVentaProducto(dtProducto *producto, int cantidad){
    this->cantidad = cantidad;
    this->producto = producto;
}

// Destructor
dtVentaProducto::~dtVentaProducto(){
    std::cout << "Destructor de dtVentaProducto" << std::endl;
    delete producto;
}

// Getters

int dtVentaProducto::getCantidad(){
    return this->cantidad;
}

dtProducto* dtVentaProducto::getProducto(){
    return this->producto;
}