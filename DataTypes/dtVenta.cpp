#include "dtVenta.h"

//Cosntructor
dtVenta::dtVenta(int idV, int des, ICollection* ventaProductos, Factura* factura) {
    this->idVenta = idV;
    this->descuento = des;
    this->ventaProductos = ventaProductos;
    this->factura = factura;
}
        
dtVenta::~dtVenta(){
    cout << "destructor de DtVenta" << endl;
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
