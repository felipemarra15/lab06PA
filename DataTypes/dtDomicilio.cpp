#include "dtDomicilio.h"
#include <iostream>

using namespace std;

dtDomicilio::dtDomicilio(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, bool retira, Cliente* cliente, Repartidor* repartidor) : dtVenta(idVenta, descuento, ventaProducto, factura){
    this->retira = retira;
    this->cliente = cliente;
    this->repartidor = repartidor;
}

dtDomicilio::dtDomicilio(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, bool retira, Cliente* cliente) : dtVenta(idVenta, descuento, ventaProducto, factura) {
    this->retira = retira;
    this->cliente = cliente;
    this->repartidor = NULL; // No hay repartidor en este caso
}

dtDomicilio::~dtDomicilio(){
    cout<<"destructor de dtDomicilio"<<endl;
}

bool dtDomicilio::getRetira(){
    return this->retira;
}