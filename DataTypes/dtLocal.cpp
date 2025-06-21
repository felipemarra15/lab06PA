#include "dtLocal.h"

//Constructor
dtLocal::dtLocal(int idVenta, int descuento, ICollection* ventaProducto, Factura* factura, IDictionary* mesa) : dtVenta(idVenta, descuento, ventaProducto, factura) {
    this->mesa = mesa;
}

//Destructor
dtLocal::~dtLocal(){
    std::cout << "Destructor de dtLocal" << std::endl;
    delete mesa; // Liberar memoria de la mesa
}

IDictionary* dtLocal::getMesa() {
    return this->mesa;
}