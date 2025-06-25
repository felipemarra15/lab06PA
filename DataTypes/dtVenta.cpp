#include "dtVenta.h"

//Cosntructor
dtVenta::dtVenta(int idV, int des, ICollection* ventaProductos, Factura* factura) {
    this->idVenta = idV;
    this->descuento = des;
    this->ventaProductos = ventaProductos;
    this->factura = factura;
}
        
dtVenta::~dtVenta(){
    // Liberar memoria de los productos de venta y la factura
    if (ventaProductos != NULL) {
        IIterator* it = ventaProductos->getIterator();
        while (it->hasCurrent()) {
            ICollectible* col = it->getCurrent();
            this->ventaProductos->remove(col); // Liberar memoria del producto de venta
            it->next();
        }
        delete it;
        delete ventaProductos; // Liberar la colección de productos de venta
    }
    if (factura != NULL) {
        delete factura; // Liberar la factura
    }
}

// Getters
int dtVenta::getIdVenta(){
    return this->idVenta;
}

int dtVenta::getDescuento(){
    return this->descuento;
}

ICollection* dtVenta::getVentaProductos(){
    return this->ventaProductos;
}

Factura* dtVenta::getFactura(){
    return this->factura;
}
