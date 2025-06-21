#include "local.h"
#include "DataTypes/dtLocal.h"
#include "mesa.h"
#include "mozo.h"
#include "venta.h"

#include <iostream>

using namespace std;

//Constructor
Local::Local(int idVenta, int descuento, ICollection * ventaProducto, Factura* factura, IDictionary* mesa) : Venta(idVenta, descuento, ventaProducto, factura){
    this->mesa = mesa;
}

//Destructor
Local::~Local() {
    cout << "Destructor de Local" << endl;
    delete mesa;
}

//Getters
IDictionary* Local::getMesa() {
    return this->mesa;
}

//Setters
void Local::setMesa(IDictionary* mesa) {
    this->mesa = mesa;
}

//funciones
dtVenta* Local::mostrarFactura() {
    return new dtLocal(this->getIdVenta(), this->getDescuento(), this->getVentaProductos(), this->getFactura(), this->mesa); // Asumiendo que se obtiene una mesa por defecto, ajustar según sea necesario
}

