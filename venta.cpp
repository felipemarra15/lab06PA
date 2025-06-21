#include "venta.h"
#include "ventaProducto.h"
#include "local.h"

#include <iostream>

using namespace std;

//Constructor
Venta::Venta(int idVenta, int descuento, ICollection* ventaProductos, Factura* factura){
    this->idVenta = idVenta;
    this->descuento = descuento;
    this->ventaProductos = ventaProductos;
    this->factura = factura;
}

// destructor

Venta::~Venta(){
    cout << "Destructor de Venta" << endl;
    delete ventaProductos;
    delete factura;
}

// getters
int Venta::getIdVenta(){
    return this->idVenta;
}

int Venta::getDescuento(){
    return this->descuento;
}

ICollection* Venta::getVentaProductos(){
    return this->ventaProductos;
}

Factura* Venta::getFactura(){
    return this->factura;
}

// setters
void Venta::setIdVenta(int idVent){
    this->idVenta = idVent;
}

void Venta::setDescuento(int desc){
    this->descuento = desc;
}

void Venta::setVentaProductos(ICollection* ventaProds){
    this->ventaProductos = ventaProds;
}

void Venta::setDescuento(float porcentaje){
    this->descuento = porcentaje;
}

void Venta::setFactura(Factura* factura){
    this->factura = factura;
}

// funciones

void Venta::aumentarCantProducto(int idProducto, int cantidad) {
    // Suponiendo que ICollection tiene un método para obtener un iterador o una colección de elementos
    IIterator* it = ventaProductos->getIterator();
    bool encontrado = false;
    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        ventaProducto* vp = dynamic_cast<ventaProducto*>(col);
        Producto *producto = vp->getProducto();
        if (producto != NULL && producto->getCodigo() == idProducto) {
            int nuevaCantidad = vp->getCantidad() + cantidad;
            vp->setCantidad( nuevaCantidad );
            encontrado = true;
            delete col;
            delete vp;
            break;
        }
        it->next();
    }
    delete it;

    if (!encontrado) {
        cout << "No se encontró el producto con ID: " << idProducto << endl;
    }
}

bool Venta::verificarVentasProducto(string verifiqueishon){
    IIterator* it = ventaProductos->getIterator();
    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        ventaProducto* vp = dynamic_cast<ventaProducto*>(col);
        if (vp && vp->getProducto()->getCodigo() == atoi(verifiqueishon.c_str())) {
            delete it;
            delete col;
            delete vp;
            return true;
        }
        it->next();
    }
    delete it;
    return false;
}

bool Venta::esMesa(int idMesa) {
    // Asumiendo que 'mesa' es un IDictionary que contiene las mesas
    Local* local = dynamic_cast<Local*>(this);
    if (local) {
        IDictionary* mesas = local->getMesa();
        if (mesas->member(new Integer(idMesa))) { // Asumiendo que Mesa es una clase que implementa IKey
            return true;
        }
    }
    return false;
}

void Venta::eliminarProducto(string producto,int cantidad){
    IIterator* it = ventaProductos->getIterator();
    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        ventaProducto* vp = dynamic_cast<ventaProducto*>(col);
        if (vp && vp->getProducto()->getNombre() == producto) { //estaria mejor comparar por codigo
            int nuevaCantidad = vp->getCantidad() - cantidad;
            if (nuevaCantidad <= 0)
                ventaProductos->remove(vp);
            else {
                vp->setCantidad(nuevaCantidad);
            }
            delete col;
            delete vp;
            break;
        }
        it->next();
    }
    delete it;
}

bool Venta::agregarProducto(ventaProducto* vp) {
    if (vp == NULL) return false;
    if (this->ventaProductos == NULL) {
        this->ventaProductos = new List();
    }
    this->ventaProductos->add(vp);
    return true;
}