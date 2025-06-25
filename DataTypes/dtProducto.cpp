#include "dtProducto.h"

dtProducto::dtProducto(int codigo,string nombre,float precio){
    this->codigo = codigo;
    this->nombre = nombre;
    this->precio = precio;
}

dtProducto::~dtProducto(){
    // Destructor vacío, no hay recursos que liberar
    // Si hubiera recursos dinámicos, se liberarían aquí
}

int dtProducto::getCodigo(){
    return this->codigo;
}

string dtProducto::getNombre(){
    return this->nombre;
}

float dtProducto::getPrecio(){
    return this->precio;
}