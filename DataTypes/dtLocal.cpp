#include "dtLocal.h"

//Constructor
dtLocal::dtLocal(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, IDictionary* mesa, Mozo* mozo) : dtVenta(idVenta, descuento, ventaProducto, factura) {
    this->mesa = mesa;
    this->mozo = mozo; // Asignar el mozo
}

//Destructor
dtLocal::~dtLocal(){
    std::cout << "Destructor de dtLocal" << std::endl;
    delete mesa; // Liberar memoria de la mesa
}

IDictionary* dtLocal::getMesa() {
    return this->mesa;
}

dtLocal::dtLocal(int idVenta,
                 int descuento,
                 ICollection* ventaProductos,
                 Factura*    factura,
                 IDictionary* mesas)
  : dtVenta(idVenta, descuento, ventaProductos, factura){
    // Calculamos el total = sum(precio * cantidad)
    this->mesa = mesa;
    total = 0.0f;
    IIterator* it = ventaProductos->getIterator();
    while (it->hasCurrent()) {
        ventaProducto* vp = dynamic_cast<ventaProducto*>(it->getCurrent());
        if (vp && vp->getProducto()) {
            total += vp->getProducto()->getPrecio() * vp->getCantidad();
        }
        it->next();
    }
    delete it;
}

float dtLocal::getTotal() {
    return total;
}