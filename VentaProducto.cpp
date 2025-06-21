#include "ventaProducto.h"

#include <iostream>

using namespace std;

//Constructor
ventaProducto::ventaProducto(int cant, Producto* prod){
    this -> cantidad = cant;
    this -> producto = prod;
}

//Destructor
ventaProducto::~ventaProducto(){
    cout << "destructor de ventaProducto" << endl;
}

//Getters
int ventaProducto::getCantidad(){
    return this->cantidad;
}

Producto* ventaProducto::getProducto(){
    return this->producto;
}

//Setters
void ventaProducto::setCantidad(int cantidad){
    this->cantidad = cantidad;
}

void ventaProducto::setProducto(Producto* producto){
    this->producto = producto;
}

//Funciones
bool ventaProducto::esProducto(int codigo){
    if(producto != NULL && producto->getCodigo() == codigo)
        return true;
    return false;

}

bool ventaProducto::ubicarProducto(int codigo){
    if(producto != NULL && producto->getCodigo() == codigo)
        return true;
    return false;
}