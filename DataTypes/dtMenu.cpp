#include "dtMenu.h"

dtMenu::dtMenu(int codigo, string descripcion, float precio, int descuento, ICollection *productos) : dtProducto(codigo, descripcion, precio) {
    this->descuento = descuento;
    this->cantidadSimple = productos;
}

dtMenu::~dtMenu() {
    cout << "Destructor de dtMenu" << endl;
    delete cantidadSimple;
}

int dtMenu::getDescuento() {
    return this->descuento;
}

ICollection* dtMenu::getCantidadSimple(){
    return this->cantidadSimple;
}

