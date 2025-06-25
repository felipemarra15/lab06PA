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
    // Liberar memoria de los productos de venta
    if (this->getVentaProductos() != NULL) {
        IIterator* it = this->getVentaProductos()->getIterator();
        while (it->hasCurrent()) {
            ICollectible* col = it->getCurrent();
            this->getVentaProductos()->remove(col); // Liberar memoria del producto de venta
            it->next();
        }
        delete it;
        delete this->getVentaProductos(); // Liberar la colección de productos de venta
    }
    if (this->getFactura() != NULL) {
        delete this->getFactura(); // Liberar la factura
    }
    // No es necesario liberar cliente y repartidor, ya que se asume que su ciclo de vida es gestionado por el sistema

    this->repartidor = NULL; // Asegurarse de que el repartidor no apunte a memoria liberada
    this->cliente = NULL; // Asegurarse de que el cliente no apunte
    delete this->cliente; // Liberar memoria del cliente
    delete this->repartidor; // Liberar memoria del repartidor
}

bool dtDomicilio::getRetira(){
    return this->retira;
}