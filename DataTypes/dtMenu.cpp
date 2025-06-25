#include "dtMenu.h"
#include "dtCantidadSimple.h"

dtMenu::dtMenu(int codigo, string descripcion, float precio, int descuento, ICollection *productos) : dtProducto(codigo, descripcion, precio) {
    this->descuento = descuento;
    this->cantidadSimple = productos;
}

dtMenu::~dtMenu() {
    // Liberar memoria de los productos del menú
    IIterator* it = this->cantidadSimple->getIterator();
    while (it->hasCurrent()) {
        ICollectible* col = it->getCurrent();
        dtCantidadSimple* cantSimple = dynamic_cast<dtCantidadSimple*>(col);
        if (cantSimple != NULL) {
            this->cantidadSimple->remove(col); // Liberar memoria del producto menu
        }
        it->next();
    }
    delete it;
    delete cantidadSimple; // Liberar la colección de productos simples
}

int dtMenu::getDescuento() {
    return this->descuento;
}

ICollection* dtMenu::getCantidadSimple(){
    return this->cantidadSimple;
}

