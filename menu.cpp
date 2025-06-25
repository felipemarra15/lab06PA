#include "menu.h"
#include "cantidadSimple.h"

//Constructor
Menu::Menu(int codigo, string descripcion, float precio, int descuento, IDictionary* cantidadSimple): Producto(codigo, descripcion, precio){
    this->descuento = descuento;
    this->cantidadSimple = cantidadSimple;
}

//Destructor
Menu::~Menu() {
    // Liberar memoria de los productos en cantidadSimple
    IIterator* it = this->cantidadSimple->getIterator();
    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        CantidadSimple* simple = dynamic_cast<CantidadSimple*>(item);
        if (simple) {
            delete simple; // Liberar memoria del objeto CantidadSimple
        }
        delete item; // Liberar memoria del item
        it->next();
    }
    delete it; // Liberar el iterador
    delete this->cantidadSimple; // Liberar la colección de cantidadSimple
}

//Getters
int Menu::getDescuento() {
    return this->descuento;
}

IDictionary* Menu::getCantidadSimple() {
    return this->cantidadSimple;
}

//Setters

void Menu::setDescuento(int descuento) {
    this->descuento = descuento;
}

void Menu::setCantidadSimple(IDictionary* cantidadSimple) {
    this->cantidadSimple = cantidadSimple;
}

// Funciones

bool Menu::verificarProductoEnMenu(string codigo) {
    IIterator* it = this->cantidadSimple->getIterator(); // Obtiene el iterador de la colección
    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        CantidadSimple* simple = dynamic_cast<CantidadSimple*>(item); // Intenta convertirlo a CantidadSimple*
        dtProducto* prod = dynamic_cast<dtProducto*>(simple->getProducto()); // Intenta convertirlo a Producto*
        if (prod && prod->getCodigo() == atoi(codigo.c_str())) { // Si es producto y el código coincide
            delete it;
            delete item;
            delete simple;
            delete prod;
            return true;
        }
    }
    delete it; // Libera el iterador si no lo encontró
    return false; // No lo encontró
}

bool Menu::esVacio() {
    if(this->cantidadSimple->isEmpty()) 
        return true;
    return false;
}

void Menu::agregarProducto(IDictionary* cantidadSimple) {
    if (cantidadSimple == NULL || cantidadSimple->isEmpty()) {
        cout << "No se puede agregar un producto vacío al menú." << endl;
        return;
    }

    IIterator* it = cantidadSimple->getIterator();
    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        CantidadSimple* simple = dynamic_cast<CantidadSimple*>(item);
        if (simple) {
            this->cantidadSimple->add(new Integer(simple->getProducto()->getCodigo()), item); // Agrega el producto al menú
        }
        delete item; // Liberar el item después de agregarlo
        delete simple; 
        it->next();
    }
    delete it; // Liberar el iterador

}

bool Menu::esProducto(string codigo){
    if(this->getCodigo() == atoi(codigo.c_str())){
        return true;
    }

    if(this->cantidadSimple->isEmpty()){
        return false;
    }

    IIterator* it = this->cantidadSimple->getIterator();
    bool encontrado = false;
    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        CantidadSimple* simple = dynamic_cast<CantidadSimple*>(item);
        dtProducto* producto = dynamic_cast<dtProducto*>(simple->getProducto());
        if (producto && producto->getCodigo() == atoi(codigo.c_str())) {
            encontrado = true;
            break;
        }
        delete item;
        delete simple;
        delete producto;
        it->next();
    }
    delete it;
    return encontrado;
}