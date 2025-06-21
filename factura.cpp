#include "factura.h"

// CONSTRUCTOR:
Factura::Factura(fecha* f, hora *h, int iva){
    this->f = f;
    this->h = h;
    this->iva = iva;
}

// DESTRUCTOR:
Factura::~Factura(){
    std::cout << "Factura destruida" << std::endl;
}

// GETTERS:
fecha* Factura::getFecha(){
    return this->f;
}

hora* Factura::getHora(){
    return this->h;
}

int Factura::getIva(){
    return this->iva;
}

// SETTERS:
void Factura::setFecha(fecha* f){
    this->f = f;
}

void Factura::setHora(hora* h){
    this->h = h;
}

void Factura::setIva(int iva){
    this->iva = iva;
}

