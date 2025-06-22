#include "local.h"
#include "DataTypes/dtLocal.h"
#include "mesa.h"
#include "mozo.h"
#include "venta.h"

#include <iostream>

using namespace std;

//Constructor
Local::Local(int idVenta, int descuento, ICollection * ventaProducto, Factura* factura, IDictionary* mesa, Mozo* mozo) : Venta(idVenta, descuento, ventaProducto, factura){
    this->mesa = mesa;
    this->mozo = mozo;
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

Mozo* Local::getMozo() {
    return this->mozo;
}

//Setters
void Local::setMesa(IDictionary* mesa) {
    this->mesa = mesa;
}

void Local::setMozo(Mozo* mozo) {
    this->mozo = mozo;
}

//funciones
dtVenta* Local::mostrarFactura() {
    IIterator* it = this->getVentaProductos()->getIterator();
    ICollection* productos = new List();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        if (vp) {
            dtProducto* prod = dynamic_cast<dtProducto*>(vp->getProducto());
            productos->add( dynamic_cast<ICollectible*>(new dtVentaProducto(prod, vp->getCantidad())));
        }
        it->next();
    }
    return new dtLocal(this->getIdVenta(), this->getDescuento(), productos, this->getFactura(), this->mesa, this->mozo); // Asumiendo que se obtiene una mesa por defecto, ajustar según sea necesario
}

