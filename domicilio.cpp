#include "domicilio.h"

#include <iostream>
#include <cstdlib>

using namespace std;

//Constructor
Domicilio::Domicilio(int idVenta, int descuento, bool retira, ICollection* ventaProducto, Factura* factura, Cliente* cliente, Repartidor* repartidor) : Venta(idVenta, descuento, ventaProducto, factura){
    this->retira = retira;
    this->repartidor = repartidor;
    this->cliente = cliente;
}

Domicilio::Domicilio(int idVenta, int descuento, bool retira, ICollection* ventaProducto, Factura* factura, Cliente* cliente) : Venta(idVenta, descuento, ventaProducto, factura){
    this->retira = retira;
    this->cliente = cliente;
}

//Destructor
Domicilio::~Domicilio(){
    // Liberar memoria de los productos de venta y la factura
    if (this->getVentaProductos() != NULL) {
        IIterator* it = this->getVentaProductos()->getIterator();
        while (it->hasCurrent()) {
            ICollectible* col = it->getCurrent();
            ventaProducto* vp = dynamic_cast<ventaProducto*>(col);
            this->getVentaProductos()->remove(new Integer(vp->getProducto()->getCodigo())); // Liberar memoria del producto de venta
            it->next();
        }
        delete it;
        delete this->getVentaProductos(); // Liberar la colección de productos de venta
    }
    if (this->getFactura() != NULL) {
        delete this->getFactura(); // Liberar la factura
    }
    this->repartidor = NULL; // Liberar el repartidor asociado
    this->cliente = NULL; // Liberar el cliente asociado
    delete this->cliente; // Liberar memoria del cliente
    delete this->repartidor; // Liberar memoria del repartidors
}

//Getters
bool Domicilio::getRetira() {
    return this->retira;
}

Repartidor* Domicilio::getRepartidor() {
    return this->repartidor;
}

Cliente* Domicilio::getCliente() {
    return this->cliente;
}

//Setters
void Domicilio::setRetira(bool retira) {
    this->retira = retira;
}

void Domicilio::setRepartidor(Repartidor* repartidor) {
    this->repartidor = repartidor;
}

void Domicilio::setCliente(Cliente* cliente) {
    this->cliente = cliente;
}

//Mostrar factura
dtVenta* Domicilio::mostrarFactura() {
    IIterator* it = this->getVentaProductos()->getIterator();
    ICollection* productos = new List();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        if (vp) {
            cout << "HOLA" << endl;
            cout << "Producto: " << vp->getProducto()->getNombre() 
                 << " | Cantidad: " << vp->getCantidad() << endl;
            dtProducto* prod = dynamic_cast<dtProducto*>(vp->getProducto());
            productos->add( dynamic_cast<ICollectible*>(new dtVentaProducto(prod, vp->getCantidad())));
        }
        it->next();
    }
    if (this->getRepartidor() != NULL) 
        return new dtDomicilio(this->getIdVenta(), this->getDescuento(), productos, this->getFactura(), this->getRetira(), this->getCliente(), this->getRepartidor());
    else 
        return new dtDomicilio(this->getIdVenta(), this->getDescuento(), productos, this->getFactura(), this->getRetira(), this->getCliente());
}

float Domicilio::calcularTotal() {
    float total = 0.0;
    IIterator* it = this->getVentaProductos()->getIterator();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        if (vp != NULL) {
            dtProducto* prod = dynamic_cast<dtProducto*>(vp->getProducto());
            // C++98: convierto el string a float con atof
            float qty = vp->getCantidad();
            total += prod->getPrecio() * qty;
        }
        it->next();
    }
    return total * (1 - (this->getDescuento() / 100.0)); // Aplicar descuento
}